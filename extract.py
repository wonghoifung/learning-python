prices = {
	'IBM':205.55,
	'HPQ':37.22
}

print {k:v for k,v in prices.items() if v > 200}

names = ['HPQ']

print {k:v for k,v in prices.items() if k in names}

print dict((k,v) for k,v in prices.items() if v > 200) # slower

#ns = {'HPQ'}
#print { k:prices[k] for k in prices.keys() & ns }