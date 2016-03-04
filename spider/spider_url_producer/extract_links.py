#-*-coding:utf8-*-

import sys
import urllib
import urllib2
import urlparse
import re
from lxml import etree

def tag_link(tag, startpage):
	return 'http://www.douban.com/tag/' + tag + '/movie?start=' + str(startpage)

def trim_link(url):
	mre=re.match('^https?://movie.douban.com/subject/([^/]*)',url,re.IGNORECASE)
	if not mre:
		print 'url:' + url + ' is not valid...'
		return ''
	url = mre.group(0)
	return url

class my_urlopener(urllib.FancyURLopener):
	version = 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36'

def process(tag):
	startpage = 0
	# links = []
	badcount = 0
	while True:
		url = tag_link(tag.encode('utf-8'), startpage)
		startpage += 15
		opener = my_urlopener()
		page = opener.open(url)
		text = page.read()
		page.close()
		selector = etree.HTML(text) 
		movielist = selector.xpath('//*[@id="content"]/div/div[@class="article"]/div[@class="mod movie-list"]/dl')
		if len(movielist) == 0:
			break
		for movie in movielist:
			movielink = movie.xpath('dd/a/@href')[0]
			link = trim_link(movielink)
			if len(link) > 0: 
				yield link
				# links.append(link)
				# print link
			else:
				badcount += 1
	# return links


