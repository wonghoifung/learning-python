#-*-coding:utf8-*-

import sys
import urllib
import urllib2
import urlparse
import re
import string
import logging
from lxml import etree

logger = logging.getLogger(__name__)

class my_urlopener(urllib.FancyURLopener):
    version = 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36'

def process():
	url = 'http://movie.douban.com/tag/?view=cloud'
	logger.debug('process: %s', url)
	opener = my_urlopener()
	page = opener.open(url)
	text = page.read()
	page.close()

	if string.find(text, '<head><title>403 Forbidden</title></head>') != -1:
		# banned!!
		return None
		
	tags = []
	selector = etree.HTML(text) 
	tagspans = selector.xpath('//*[@id="content"]/div/div[@class="article"]/div[@class="indent tag_cloud"]/span')
	for span in tagspans:
		tag = span.xpath('a/text()')[0]
		tags.append(tag)

	return tags


