#-*-coding:utf8-*-

from gevent.monkey import patch_all
patch_all()

import sys
sys.path.append('gen-py')
import config
import logging
from store import constants, store_service, ttypes
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

logger = logging.getLogger(__name__)

def change_to_string_if_list(val):
    if type(val)==list:
        res = u', '.join(val)
    else:
        res = val
    return res.encode('utf-8')

def write_to_store_server_thread_run(queue):
    transport = TSocket.TSocket('127.0.0.1', config.STORE_SERVER_PORT)
    transport = TTransport.TFramedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = store_service.Client(protocol)
    transport.open()

    while 1:
        try:
            info = queue.get(timeout=30)
        except Queue.Empty:
            continue
        if not info:
            break # quit
        #print info
        rec = ttypes.movie_info()
        rec.url = change_to_string_if_list(info['url'])
        rec.movienum = change_to_string_if_list(info['movienum'])
        rec.initial_release_date = change_to_string_if_list(info['initial_release_date'])
        rec.big_poster = change_to_string_if_list(info['big_poster'])
        rec.small_poster = change_to_string_if_list(info['small_poster'])
        rec.language = change_to_string_if_list(info['language'])
        rec.area = change_to_string_if_list(info['area'])
        rec.scriptwriter = change_to_string_if_list(info['scriptwriter'])
        rec.actor = change_to_string_if_list(info['actor'])
        rec.director = change_to_string_if_list(info['director'])
        rec.source = change_to_string_if_list(info['source'])
        rec.imdb = change_to_string_if_list(info['imdb'])
        rec.year = change_to_string_if_list(info['year'])
        rec.genre = change_to_string_if_list(info['genre'])
        rec.runtime = change_to_string_if_list(info['runtime'])
        rec.moviename = change_to_string_if_list(info['moviename'])
        rec.otherName = change_to_string_if_list(info['otherName'])
        res = client.put(rec)
        if not res:
            logger.error('store failed, url:%s',rec.url)

    transport.close()

