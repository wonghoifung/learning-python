import re

comment = re.compile(r'/\*(.*?)\*/')

text1 = '/* abcsdfasdfasdf */'

text2 = '''/* abcsdfasdfasdf
			ddddz;z;z;z;z;z;z */'''

print comment.findall(text1)

print '--------------'

print comment.findall(text2)

comment = re.compile(r'/\*((?:.|\n)*?)\*/')

print '--------------'

print comment.findall(text1)

print '--------------'

print comment.findall(text2)

comment = re.compile(r'/\*(.*?)\*/', re.DOTALL)

print '--------------'

print comment.findall(text1)

print '--------------'

print comment.findall(text2)