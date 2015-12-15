from collections import namedtuple

XTYPE = namedtuple('XTYPE',['name','age'])

x1 = XTYPE('wong',30)

print x1.name
print x1.age
print len(x1)
x1=x1._replace(age=31)
print x1[0]
print x1[1]