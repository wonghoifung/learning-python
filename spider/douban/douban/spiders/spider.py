# -*- coding: utf-8 -*-
from scrapy.contrib.spiders import CrawlSpider

class Douban(CrawlSpider):
	name = "douban"
	start_urls = ['http://movie.douban.com/top250']
	def parse(self, response):
		print response.body
		print response.url 

