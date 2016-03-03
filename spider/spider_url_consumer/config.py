#-*-coding:utf8-*-

from gevent.monkey import patch_all
patch_all()

import sys
import logging
from logging.handlers import RotatingFileHandler

def init_logger(isconsole):
	root = logging.getLogger()
	root.setLevel(logging.DEBUG)
	formatter = logging.Formatter('%(asctime)s [%(levelname)s][%(filename)s:%(lineno)d] %(message)s')
	if isconsole:
		hdlr = logging.StreamHandler(sys.stdout)
		hdlr.setLevel(logging.DEBUG)
		hdlr.setFormatter(formatter)
		root.addHandler(hdlr)
	else:
		rthdlr = RotatingFileHandler('s_consumer.log', maxBytes=512*1024*1024, backupCount=6)
		rthdlr.setLevel(logging.DEBUG)
		rthdlr.setFormatter(formatter)
		root.addHandler(rthdlr)

ID = 1
DISPATCHER_ADDR = ("127.0.0.1", 8080)
STORE_SERVER_PORT = 9090
