import re

pat = re.compile(r'\"(.*)\"')

text1 = 'aba "xyz"'

print pat.findall(text1)

text2 = 'aba "xyz" asdsadfsadfsadfsdf "123" ddd'

print pat.findall(text2)

pat2 = re.compile(r'\"(.*?)\"')

print pat2.findall(text2)
