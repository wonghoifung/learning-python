#-*-coding:utf8-*-

from gevent.monkey import patch_all
patch_all()

import time
import random
import struct
import threading
import logging
import traceback
import socket

taG = 71
defaultVerion = 1
logger = logging.getLogger(__name__)

class my_exception(Exception):
	def __init__(self, value):
		self.value=value
	def __str__(self):
		return repr(self.value)

def recv_n(sock, n):
    if not n:
        return ''
    data_buffer = []
    while n:
        data = sock.recv(n)
        if not data:
            #sock.close() # close when the below exception is captured
            raise my_exception('sockect disconnected')
            break
        data_buffer.append(data)
        n -= len(data)
    data = ''.join(data_buffer)
    if 0 != n:
        return None
    return data

be_mapper = {
    1: '>B',
    2: '>H',
    4: '>I',
    8: '>Q',
}

def read_be_int(s, n):
    data = recv_n(s, n)
    if not data:
        return None
    return struct.unpack(be_mapper[n], data)[0]

def serialize_pack(p):
    assert isinstance(p, pack)
    header = struct.pack('>BBHI', p.G, p.version, p.command, p.bodylength, )
    if p.data:
        return header + p.data
    return header

# header: | G_1 | version_1 | command_2 | bodylength_4 | 
class pack(object):
    __slots__ = ("G", 'version', 'command', 'bodylength', 'data')
    def __init__(self, command, data):
        self.G = taG
        self.version = defaultVerion
        self.command = command
        self.bodylength = len(data)
        self.data = data
    def __repr__(self):
        return "pack(version:%d,command:%d,bodylength:%d)" % (self.version,self.command,self.bodylength,)
    def set_version(self, v):
        self.version = v
    def set_command(self, cmd):
        self.command = cmd
    def set_data(self, data):
        self.bodylength = len(data)
        self.data = data
    def serialize(self):
        return serialize_pack(self)

# header: | G_1 | version_1 | command_2 | bodylength_4 | 
def read_pack(sock):
    G = read_be_int(sock, 1)
    if G is None or G != taG:
        return None
    version = read_be_int(sock, 1)
    if version is None or version != defaultVerion:
        return None
    command = read_be_int(sock, 2)
    if command is None:
        return None
    bodylength = read_be_int(sock, 4)
    if bodylength is None:
        return None
    if bodylength:
        data = recv_n(sock, bodylength)
    else:
        data = ''
    p = pack(command, data)
    return p

class stream(object):
    def __init__(self, sock, timeout=10):
        self.sock = sock
        self.read_lock = threading.Lock()
        self.write_lock = threading.Lock()
        self.is_close = False
        self.timeout = timeout

    # 1 timeout; 2 read return 0; 3 others
    def read(self):
        with self.read_lock:
            self.sock.settimeout(self.timeout)
            try:
                p = read_pack(self.sock)
            except socket.timeout:
                return None, 1
            except my_exception:
                self.close()
                return None, 2
            except Exception as e:
                logger.debug("error when read pack: %s, %s", type(e), e)
                self.close()
                return None, 3
            return p, 0

    def write(self, p):
        sdata = p.serialize()
        with self.write_lock:
            self.sock.settimeout(self.timeout)
            try:
                self.sock.sendall(sdata)
            except Exception as e:
                logger.debug("error when write pack: %s, %s", type(e), e)
                self.close()
                return None
        return 1

    def close(self):
        if self.is_close == True:
            return
        self.is_close = True
        self.sock.close()
