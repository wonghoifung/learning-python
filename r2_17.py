s = 'Elements are written as "<tag>text</tag>".'

import html

print s

#print html.escape(s)
s = 'Spicy &quot;Jalape&#241;o&quot.'
#import HTMLParser
#p = HTMLParser()
#print p.unescape(s)

t = 'The prompt is &gt;&gt;&gt;'
from xml.sax.saxutils import unescape
print unescape(t)

