#-*-coding:utf8-*-

import sys
import urllib
import urllib2
import urlparse
import re
from lxml import etree

class MyURLOpener(urllib.FancyURLopener):
    version = 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36'

def print_info(info):
	for key in info:
		value = info[key]
		if isinstance(value, list):
			value = ', '.join(value)
		print key + ' : ' + value

def big_poster(smallposter):
	tag = smallposter[smallposter.rindex("/") + 1 : smallposter.rindex(".jpg")]
	return "http://img3.douban.com/view/photo/photo/public/" + tag + ".jpg"

def process(url):
	mre=re.match('^https?://movie.douban.com/subject/([^/]*)',url,re.IGNORECASE)
	if not mre:
		print 'url:' + url + ' is not valid...'
		return
	url = mre.group(0)
	print 'process: ' + url
	movienum = mre.group(1)
	myopener = MyURLOpener()
	page = myopener.open(url)
	text = page.read()
	page.close()
	info = {}
	info['movienum'] = movienum
	info['url'] = url
	info['source'] = 'douban'
	selector = etree.HTML(text)
	moviename = selector.xpath('//div[@id="wrapper"]/div[@id="content"]/h1/span[@property="v:itemreviewed"]/text()')
	year = selector.xpath('//div[@id="wrapper"]/div[@id="content"]/h1/span[@class="year"]/text()')
	info['moviename'] = moviename[0]
	info['year'] = year[0][1:-1]
	rawinfo = selector.xpath('//div[@class="subject clearfix"]/div[@id="info"]/span')
	info['director'] = rawinfo[0].xpath('span[@class="attrs"]/a/text()') 
	info['scriptwriter'] = rawinfo[1].xpath('span[@class="attrs"]/a/text()') 
	info['actor'] = rawinfo[2].xpath('span[@class="attrs"]/a/text()') 
	info['genre'] = selector.xpath('//*[@id="info"]/span[@property="v:genre"]/text()')
	info['initial_release_date'] = selector.xpath('//*[@id="info"]/span[@property="v:initialReleaseDate"]/text()') 
	info['runtime'] = selector.xpath('//*[@id="info"]/span[@property="v:runtime"]/text()')
	info['imdb'] = selector.xpath('//*[@id="info"]/a/@href') 
	info['small_poster'] = selector.xpath('//*[@id="mainpic"]/a/img/@src')[0]
	info['big_poster'] = big_poster(info['small_poster'])

	plaintext = []
	outer = selector.xpath('//*[@id="info"]/text()')
	for item in outer:
		item = item.lstrip()
		item = item.rstrip()
		if len(item) > 0 and item != '/':
			plaintext.append(item)
	if (len(plaintext) > 0): info['area'] = plaintext[0]
	if (len(plaintext) > 1): info['language'] = plaintext[1]
	if (len(plaintext) > 2): info['otherName'] = plaintext[2]

	print_info(info)

def main():
	url = sys.argv[1:]
	info = process(url[0])

if __name__ == "__main__":
    main()
