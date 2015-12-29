s = ' hello\n'

print s

s1 = s.strip()

print s1

s2 = s.lstrip()

print s2

s3 = s.rstrip()

print s3

t = '-----hello====='

t1 = t.lstrip('-')

print t1

t2 = t.rstrip('=')

print t2

print t.strip('-=')

with open('./r1_19.py') as f:
	lines = (line.strip() for line in f)
	for line in lines:
		print line