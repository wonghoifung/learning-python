import re

line = 'asdf fff; ddd, fffc,baba,            zz'

print re.split(r'[;,\s]\s*', line)

arr = [1,2,3,4]

print arr[1::2]

print arr[::1]

print arr[1::]

print arr[::3] # start::step

arr2 = [5,6,7,8,9]

print zip(arr,arr2)

print re.split(r'(;|,|\s)\s*', line)

print re.split(r'(?:;|,|\s)\s*', line)
