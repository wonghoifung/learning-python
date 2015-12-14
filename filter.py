values = ['1', '2', '-3', '-', 'N/A']

def is_int(val):
	try:
		x = int(val)
		return True
	except ValueError:
		return False

ival = list(filter(is_int, values))

print ival

for n in filter(is_int, values):
	print("   " + n)

vv = [n if n<0 else 0 for n in map(int, filter(is_int, values))]
print vv

addresses = ['abc', 'efg', 'wong', 'hoifung']
counts = [3, 4, 10, 12]
from itertools import compress
more9 = [n > 9 for n in counts]
print more9
print list(compress(addresses, more9))