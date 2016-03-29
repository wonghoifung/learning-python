#-*-coding:utf8-*-

import requests
import json
import mysqlop

url0 = 'http://iwan.baidu.com/YeyouAjax/selectGame2?psquery=&dlfrom=&yeyouquery=%E6%B8%B8%E6%88%8F&mobilebannerquery=&mobilequery=&wangyouquery=&tn=baidu&query=%E6%B8%B8%E6%88%8F&pvid=1459236312394330141&qid=18085386854233155806&sid=18880_18286_1453_18240_17945_18205_17000_15470_12289_10633&zt=ps&from=29132&fenlei=&hcQuery=&isid=ui%3A3%26as%3A2%26bs%3A0%26ui_sample%3A2&pid=342&f=sug&time=2016-03-29+15%3A25%3A12&oq=%E6%B8%B8%E6%88%8F&q=%E6%B8%B8%E6%88%8F&psid=0&rqid=1459236312394330141&cookie=9A8A681FEFC36AD6CCB81D91904FC04F&baiduid=9A8A681FEFC36AD6CCB81D91904FC04F&fr=ps&passid=14713618&bdstoken=6f4922f45568161a8cdf4ad2299f6d23&action_from=4&type=0&subject=0&page='

params = {
	
}

headers = {
	'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.108 Safari/537.36',
	'X-Requested-With': 'XMLHttpRequest',
	'Connection': 'keep-alive',
	'Referer': 'http://iwan.baidu.com/yeyou?query=%E6%B8%B8%E6%88%8F&ordertype=&gametype=yeyou&qid=18085386854233155806&sid=18880_18286_1453_18240_17945_18205_17000_15470_12289_10633&from=29132&zt=ps&type=0&subject=0&tn=baidu&fenlei=&wd=%E6%B8%B8%E6%88%8F'
}

def tostr(item):
	if type(item) == unicode:
		return str(item.encode('utf8'))
	else:
		return str(item)

def concatsql(title_,type_,platform_,gameid_,info_,allinfo_,trueurl_,shorttitle_,photo_):
	sql = "insert into test.baidu_webgame_info(`title`,`type`,`platform`,`gameid`,`info`,`allinfo`,`trueurl`,`shorttitle`,`photo`) values('%s','%s','%s','%s','%s','%s','%s','%s','%s')" % \
				(title_,type_,platform_,gameid_,info_,allinfo_,trueurl_,shorttitle_,photo_)
	return sql

for page in range(1,97):
	url = url0 + str(page)

	response = requests.get(url, params=params, headers=headers)

	jsoncontent = response.json()

	data_ = jsoncontent['data']
	list_ = data_['list']

	for item in list_:
		title_ = tostr(item['title'])
		type_ = tostr(item['type'])
		platform_ = tostr(item['platform'])
		gameid_ = tostr(item['gameid'])
		info_ = tostr(item['info'])
		allinfo_ = tostr(item['allinfo'])
		trueurl_ = tostr(item['trueurl'])
		shorttitle_ = tostr(item['shorttitle'])
		photo_ = tostr(item['photo'])

		sql = concatsql(title_, type_, platform_, gameid_, info_, allinfo_, trueurl_, shorttitle_, photo_)
		mysqlop.exec_sql(sql)

		print 'title: ' + title_
		print 'type: ' + type_
		print 'platform: ' + platform_
		print 'gameid: ' + gameid_
		print 'info: ' + info_
		print 'allinfo: ' + allinfo_
		print 'trueurl: ' + trueurl_
		print 'shorttitle: ' + shorttitle_
		print 'photo: ' + photo_
		print ''


