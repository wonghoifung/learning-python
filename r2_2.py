fn = 'spam.txt'

print fn.endswith('.txt')

print fn.startswith("spa")

import os 
fns = os.listdir('.')
print fns
print [n for n in fns if n.endswith(('.py', '.md'))]
print any(n.endswith('.md') for n in fns)