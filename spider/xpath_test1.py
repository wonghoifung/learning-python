#-*-coding:utf8-*-
from lxml import etree

htmlsrc = '''
<!DOCTYPE html>
<html>
	<head>
	</head>

	<body>
		<div id="content">
			<ul id="useful">
				<li>abc1</li>
				<li>abc2</li>
			</ul>

			<ul id="useless">
				<li>没用1</li>
				<li>没用2</li>
			</ul>

			<div id="url">
				<a href="http://www.douban.com">douban</a>
				<a href="http://www.baidu.com" title="baidu">百度</a>
			</div>
		</div>

	</body>
</html>
'''

selector = etree.HTML(htmlsrc)

content = selector.xpath('//ul[@id="useful"]/li/text()')
for item in content:
	print item

print ''

link = selector.xpath('//a/@href')
for item in link:
	print item

print ''

title = selector.xpath('//a/@title')
print title[0]

print ''

cn = selector.xpath('//a/text()')
for item in cn:
	print item.encode('utf-8')

