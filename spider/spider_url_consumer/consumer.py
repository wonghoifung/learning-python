#-*-coding:utf8-*-

from gevent.monkey import patch_all
patch_all()

import sys 
import os
import extract_info
import store_client
import command
import config
import socket
import time
import Queue
import threading
import logging
import string
import stream as ss
from multiprocessing.pool import ThreadPool
from stream import stream, pack
from pb.pingpong_req_pb2 import pingpong_req
from pb.pingpong_resp_pb2 import pingpong_resp 
from pb.consume_url_req_pb2 import consume_url_req
from pb.consume_url_resp_pb2 import consume_url_resp
from pb.consumer_register_req_pb2 import consumer_register_req
from pb.consumer_register_resp_pb2 import consumer_register_resp

config.init_logger(False)

logger = logging.getLogger(__name__)

class consumer(object):
    def __init__(self, pid, dispatcher_addr):
        self.id = pid
        self.dispatcher_addr = dispatcher_addr 
        self.wqueue_to_dispatcher = Queue.Queue(10)
        self.wqueue_to_store_client = Queue.Queue(10)

        self.dispatcher_stream = None
        self.dispatcher_socket = None
        self.connect()

        self.write_to_dispatcher_thread = threading.Thread(target=self.write_to_dispatcher_thread_run)
        self.write_to_dispatcher_thread.setDaemon(True)
        self.write_to_dispatcher_thread.start()

        self.write_to_store_server_thread = threading.Thread(target=store_client.write_to_store_server_thread_run, args=(self.wqueue_to_store_client,))
        self.write_to_store_server_thread.setDaemon(True)
        self.write_to_store_server_thread.start()

        self.pingpong_req_num = 0
        self.pingpong_resp_num = 0

        self.thread_pool = ThreadPool(10)

    def connect(self):
        self.close()
        self.dispatcher_socket = socket.create_connection(self.dispatcher_addr)
        self.register()
        self.dispatcher_stream = stream(self.dispatcher_socket, 10)

    def register(self):
        req = consumer_register_req()
        req.id = self.id
        p = pack(command.consumer_register, req.SerializeToString())
        self.dispatcher_socket.sendall(p.serialize())
        respack = ss.read_pack(self.dispatcher_socket)
        if respack is None:
            logger.error("no register resp")
            sys.exit(1)
        if respack.command != command.consumer_register:
            logger.info("register failed 1")
            sys.exit(1)
        resp = consumer_register_resp()
        resp.ParseFromString(respack.data)
        if resp.id != self.id or resp.res != 0:
            logger.info("register failed 2")

    def close(self):
        if self.dispatcher_stream:
            self.dispatcher_stream.close()
            self.dispatcher_stream = None

    def push(self, cmd, msg):
        p = pack(cmd, msg.SerializeToString())
        return self.dispatcher_stream.write(p)

    def mkpack(self, cmd, msg):
        p = pack(cmd, msg.SerializeToString())
        return p

    def extract_info_thread_run(self, url):
        try:
            info = extract_info.process(url)
        except Exception as e:
            logger.debug("extract error: %s", e)
            s = str(e)
            if string.find(s, 'HTTP Error 404') != -1:
                logger.debug('see this url as success, %s', url)
                resp = consume_url_resp()
                resp.res = 0
                resp.success_urls.append(url)
                self.wqueue_to_dispatcher.put(self.mkpack(command.consume_url, resp))
                return
            info = None

        if info is None:
            resp = consume_url_resp()
            resp.res = 1
            resp.failed_urls.append(url)
            self.wqueue_to_dispatcher.put(self.mkpack(command.consume_url, resp))
        else:
            self.wqueue_to_store_client.put(info)
            resp = consume_url_resp()
            resp.res = 0
            resp.success_urls.append(url)
            self.wqueue_to_dispatcher.put(self.mkpack(command.consume_url, resp))

    def write_to_dispatcher_thread_run(self):
        while 1:
            try:
                p = self.wqueue_to_dispatcher.get(timeout=30)
            except Queue.Empty:
                # timeout, send pingpong
                if self.pingpong_req_num != self.pingpong_resp_num:
                    # TODO
                    logger.info("pingpong num not match")
                req = pingpong_req()
                self.pingpong_req_num += 1
                req.num = self.pingpong_req_num
                self.push(command.pingpong, req)
                continue
            if not p:
                break
            self.dispatcher_stream.write(p)

    def read_from_dispatcher_thread_run(self):
        while 1:
            p, res = self.dispatcher_stream.read()
            if res == 1:
                continue # timeout
            if res:
                logger.error("read dispatcher error")
                break

            if p.command == command.consume_url:
                req = consume_url_req()
                req.ParseFromString(p.data)
                for url in req.urls:
                    args = (url,)
                    self.thread_pool.apply_async(self.extract_info_thread_run, args=args)
                continue

            if p.command != command.pingpong:
                logger.error("read unexpected cmd:%d", p.command)
                continue
            
            resp = pingpong_resp()
            resp.ParseFromString(p.data)
            self.pingpong_resp_num = resp.num

    def start(self):
        try:
            self.read_from_dispatcher_thread_run()
        except Exception as e:
            logger.debug("consumer error: %s", e)
        finally:
            self.wqueue_to_dispatcher.put(0) # make write_to_dispatcher_thread exit
            self.write_to_dispatcher_thread.join()
            self.wqueue_to_store_client.put(0)
            self.write_to_store_server_thread.join()
            self.thread_pool.join()

    def start_no_block(self):
        t = threading.Thread(target=self.start)
        t.setDaemon(True)
        t.start()
        return t

def main():
    cm = consumer(config.ID, config.DISPATCHER_ADDR)
    thd = cm.start_no_block()
    thd.join()

if __name__ == '__main__':
    with open('./server.pid', "w") as f:
        f.write('%s %d'%(sys.argv[0], os.getpid()))
    main()

