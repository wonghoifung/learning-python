#-*-coding:utf8-*-

from multiprocessing.dummy import Pool as ThreadPool
from lxml import etree
import requests
import json
import sys

reload(sys)
sys.setdefaultencoding('utf-8')

def towrite(contentdict):
	f.writelines('time: ' + str(contentdict['topic_reply_time']) + '\n')
	f.writelines('content: ' + unicode(contentdict['topic_reply_content']) + '\n')
	f.writelines('replier: ' + contentdict['user_name'] + '\n\n')

def spider(url):
	html = requests.get(url)
	selector = etree.HTML(html.text) 
	content_field = selector.xpath('//div[@class="l_post j_l_post l_post_bright  "]')
	print len(content_field)
	item = {}
	for each in content_field:
		reply_info = json.loads(each.xpath('@data-field')[0].replace('&quot',''))
		author = reply_info['author']['user_name'] 
		content = each.xpath('div[@class="d_post_content_main"]/div/cc/div[@class="d_post_content j_d_post_content  clearfix"]/text()')[0]
		reply_time = reply_info['content']['date']
		print content
		print reply_time
		print author
		item['user_name'] = author
		item['topic_reply_content'] = content
		item['topic_reply_time'] = reply_time
		towrite(item)

if __name__=='__main__':
	pool = ThreadPool(4)
	f = open('content.txt','a')
	page = []
	for i in range(1,15):
		newpage = 'http://tieba.baidu.com/p/4374801783?pn=' + str(i)
		page.append(newpage)
	results = pool.map(spider, page)
	pool.close()
	pool.join()
	f.close()
