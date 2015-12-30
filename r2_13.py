text = 'hello world'

print text.ljust(20)

print text.rjust(20)

print text.center(20)

print text.rjust(20,'=')

print text.center(20,'*')

print format(text,'>20')

print format(text,'-^20')

print format(text,'=<20s')
print format(text,'=<20')

print '{:>10}{:>10}'.format('hello','world')

f = 1.234567

print format(f,'>10')

print format(f,'^10.2f')

print '%-20s' % text
print '%20s' % text
