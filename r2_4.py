s='123456'
print s.find('34')

import re

txt1='11/11/1111'
txt2='aa 11 bb'

if re.match(r'\d+/\d+/\d+',txt1):
	print 'yes'
else:
	print 'no'

if re.match(r'\d+/\d+/\d+',txt2):
	print 'yes'
else:
	print 'no'

pat=re.compile(r'\d+/\d+/\d+')

if pat.match(txt1):
	print 'yes again'
else:
	print 'no again'

if pat.match(txt2):
	print 'yes again'
else:
	print 'no again'

txt3='11/11/1111 22/22/3333 asdlfkajsdl;fkjs 66/2/343'

print pat.findall(txt3)

pat2=re.compile(r'(\d+)/(\d+)/(\d+)')

mg = pat2.match(txt1)
print mg.group(0)
print mg.group(1)
print mg.group(2)
print mg.group(3)
print mg.groups()

allm = pat2.findall(txt3)
print allm
print allm[0]

for m in allm:
	print m

txt4='99/999/9999abc'
print re.match(r'(\d+)/(\d+)/(\d+)$', txt4)
print re.match(r'(\d+)/(\d+)/(\d+)', txt4).group(0)

