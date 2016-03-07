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

def print_info(info):
	for key in info:
		value = info[key]
		if isinstance(value, list):
			value = ', '.join(value)
		logger.debug("%s : %s", key, value)

def big_poster(smallposter):
	tag = smallposter[smallposter.rindex("/") + 1 : smallposter.rindex(".jpg")]
	return "http://img3.douban.com/view/photo/photo/public/" + tag + ".jpg"

def process(url):
	mre=re.match('^https?://movie.douban.com/subject/([^/]*)',url,re.IGNORECASE)
	if not mre:
		logger.debug("url: %s is not valid...", url)
		return
	url = mre.group(0)
	logger.debug('process: %s', url)
	movienum = mre.group(1)

	# opener = my_urlopener()
	# page = opener.open(url)
	# text = page.read()
	# page.close()

	req = urllib2.Request(url)
	req.add_header('User-Agent', 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36')
	req.add_header('cookie', 'bid=damn')
	page = urllib2.urlopen(req, timeout=10)
	text = page.read()
	page.close()

	if string.find(text, '<head><title>403 Forbidden</title></head>') != -1:
		# banned!!
		return None
	info = {}
	info['movienum'] = movienum
	info['url'] = url
	info['source'] = 'douban'
	selector = etree.HTML(text)
	moviename = selector.xpath('//div[@id="wrapper"]/div[@id="content"]/h1/span[@property="v:itemreviewed"]/text()')
	year = selector.xpath('//div[@id="wrapper"]/div[@id="content"]/h1/span[@class="year"]/text()')
	
	try:
		info['moviename'] = moviename[0]
	except Exception as e:
		logger.debug('moviename %s, %s', e, url)
		info['moviename'] = ''
	
	try:
		info['year'] = year[0][1:-1]
	except Exception as e:
		logger.debug('year %s, %s', e, url)
		info['year'] = ''
	
	rawinfo = selector.xpath('//div[@class="subject clearfix"]/div[@id="info"]/span')

	try:
		info['director'] = rawinfo[0].xpath('span[@class="attrs"]/a/text()')
	except Exception as e:
		logger.debug('director %s, %s', e, url)
		info['director'] = ''
	 
	try:
		info['scriptwriter'] = rawinfo[1].xpath('span[@class="attrs"]/a/text()') 
	except Exception as e:
		logger.debug('scriptwriter %s, %s', e, url)
		info['scriptwriter'] = ''

	try:
		info['actor'] = rawinfo[2].xpath('span[@class="attrs"]/a/text()')
	except Exception as e:
		logger.debug('actor %s, %s', e, url)
		info['actor'] = ''

	info['genre'] = selector.xpath('//*[@id="info"]/span[@property="v:genre"]/text()')
	info['initial_release_date'] = selector.xpath('//*[@id="info"]/span[@property="v:initialReleaseDate"]/text()') 
	info['runtime'] = selector.xpath('//*[@id="info"]/span[@property="v:runtime"]/text()')
	info['imdb'] = selector.xpath('//*[@id="info"]/a/@href') 
	
	try:
		info['small_poster'] = selector.xpath('//*[@id="mainpic"]/a/img/@src')[0]
	except Exception as e:
		logger.debug('small_poster %s, %s', e, url)
		info['small_poster'] = ''

	try:
		info['big_poster'] = big_poster(info['small_poster'])
	except Exception as e:
		logger.debug('big_poster %s, %s', e, url)
		info['big_poster'] = ''

	plaintext = []
	outer = selector.xpath('//*[@id="info"]/text()')
	for item in outer:
		item = item.lstrip()
		item = item.rstrip()
		if len(item) > 0 and item != '/':
			plaintext.append(item)
	if (len(plaintext) > 0): 
		info['area'] = plaintext[0]
	else:
		info['area'] = ''
	if (len(plaintext) > 1): 
		info['language'] = plaintext[1]
	else:
		info['language'] = ''
	if (len(plaintext) > 2): 
		info['otherName'] = plaintext[2]
	else:
		info['otherName'] = ''

	#print_info(info)
	return info
