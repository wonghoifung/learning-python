s='{name} has {n} messages'
print s.format(name='guido',n=37)


name = 'wong'
n = 88

#print vars()

#print s.format_map(vars())

class Info:
	def __init__(self, name, n):
		self.name = name
		self.n = n

a = Info('aaa', 888)
print vars(a)

class safesub(dict):
	def __missing__(self, key):
		return '{' + key + '}'

#print s.format_map(safesub(vars()))

import sys

def sub(text):
	return text.format_map(safesub(sys._getframe(1).f_locals))


#################

#print '%(name) has %(n) messages' % vars()

import string

s = string.Template('$name has $n message')
print s.substitute(vars())

