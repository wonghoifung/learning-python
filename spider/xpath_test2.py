#-*-coding:utf8-*-
from lxml import etree

htmlsrc1 = '''
<!DOCTYPE html>
<html>
	<head>
	</head>

	<body>
		<div id="test-1">111</div>
		<div id="test-2">222</div>
		<div id="testfault">333</div>
	</body>
</html>
'''

htmlsrc2 = '''
<!DOCTYPE html>
<html>
	<head>
	</head>

	<body>
		<div id="test">
			a
			<span id="tiger">
				b
				<ul>c
					<li>d</li>
				</ul>
				y
			</span>
			z
		</div>
	</body>
</html>
'''

selector = etree.HTML(htmlsrc1)

content = selector.xpath('//div[starts-with(@id,"test")]/text()')
for item in content:
	print item

print ''

selector = etree.HTML(htmlsrc2)
content = selector.xpath('//div[@id="test"]/text()')
for item in content:
	print item

print ''

data = selector.xpath('//div[@id="test"]')[0]
info = data.xpath('string(.)')
content = info.replace('\n','').replace(' ','').replace('\t','')
print content