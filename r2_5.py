text = 'yes,no,yes,no'

text = text.replace('yes','yep')

print text

text = '11/1/2015, 12/30/2014'

import re

print re.sub(r'(\d+)/(\d+)/(\d+)', r'\3-\1-\2', text)

pat = re.compile(r'(\d+)/(\d+)/(\d+)')

print pat.sub(r'\3:\1:\2', text)

from calendar import month_abbr

def change_date(m):
	mon_name = month_abbr[int(m.group(1))]
	return '{} {} {}'.format(m.group(2), mon_name, m.group(3))

print pat.sub(change_date, text)

print pat.subn(change_date, text)