nums = [1,2,3,4,5]
s = sum(x*x for x in nums)
print s

import os 
files = os.listdir('.')
if any(name.endswith('.py') for name in files):
	print "python script found"
else:
	print "no python script"

s = ('a',1)
print ','.join(str(x) for x in s)

pf = [
{'name':'wong','shares':50},
{'name':'hoifung','shares':100}
]
print min(ss['shares'] for ss in pf)
print min(pf,key=lambda ss:ss['shares'])