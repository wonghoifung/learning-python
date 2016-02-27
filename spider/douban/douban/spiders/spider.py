# -*- coding: utf-8 -*-
from scrapy.contrib.spiders import CrawlSpider
from scrapy.http import Request
from scrapy.selector import Selector
from douban.items import DoubanItem

class Douban(CrawlSpider):
	name = "douban"
	redis_key = 'douban:start_urls'
	start_urls = ['http://movie.douban.com/top250']
	url = 'http://movie.douban.com/top250'

	def parse(self, response):
		#print response.body
		#print response.url 
		item = DoubanItem()
		selector = Selector(response)
		Movies = selector.xpath('//div[@class="info"]')
		for eachMovie in Movies:
			title = eachMovie.xpath('div[@class="hd"]/a/span/text()').extract()
			fullTitle = ''
			for each in title:
				fullTitle += each 
			movieInfo = eachMovie.xpath('div[@class="bd"]/p/text()').extract()
			star = eachMovie.xpath('div[@class="bd"]/div[@class="star"]/span[4]/text()').extract()
			quote = eachMovie.xpath('div[@class="bd"]/p[@class="quote"]/span/text()').extract()
			if quote:
				quote = quote[0]
			else:
				quote = ''
			# print fullTitle
			# print movieInfo
			# print star
			# print quote
			item['title'] = fullTitle
			item['movieInfo'] = ';'.join(movieInfo)
			item['star'] = star
			item['quote'] = quote
			yield item
		nextLink = selector.xpath('//span[@class="next"]/link/@href').extract()
		if nextLink:
			nextLink = nextLink[0]
			print nextLink
			yield Request(self.url + nextLink, callback=self.parse)

