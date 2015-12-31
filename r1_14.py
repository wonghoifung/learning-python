parts = ['ls','chicago','not','chicago?']
print ' '.join(parts)

a='is chicago'
b='not chicago?'
print '{} {}'.format(a,b)
print a+' '+b

c='hello' 'hi'
print c

data=['aa',60,1.1]

# slow choice
s=''
for p in data:
	s+=str(p)
print s

# better choice
print ' '.join(str(d) for d in data)

#print(a,b,c,sep=' ')

def sample():
	yield 'A'
	yield 'B'
	yield 'C'
	yield 'D'

print ''.join(sample())

s=''
for p in sample():
	s+=p
print s

def combine(source, maxsize):
	parts=[]
	size=0
	for part in source:
		parts.append(part)
		size+=len(part)
		if size>maxsize:
			yield ''.join(parts)
			parts=[]
			size=0
	yield ''.join(parts)

s=''
for p in combine(sample(),32768):
	s+=p
print s
