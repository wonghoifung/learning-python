from fnmatch import fnmatch, fnmatchcase

print fnmatch('foo.txt', '*.txt')

print fnmatch('foo.txt', '?oo.txt')

print fnmatch('dd44.txt', 'dd[0-9]*')

names = ['dat1.txt','dat2.txt','config.xml']

print [name for name in names if fnmatch(name,'dat*.txt')]

print fnmatchcase('dd.txt', '*.TXT')