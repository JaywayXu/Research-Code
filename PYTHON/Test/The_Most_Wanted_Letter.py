import re

def checkio(text):
	a = "".join([i for i in list(text) if re.search('[a-zA-Z]',i)])
	a = a.lower()
	l = ([(x,a.count(x)) for x in list(a)])
	l.sort(key = lambda k:k[1],reverse = True)
	x = [i for i in l if i[1]==l[0][1]]
	x.sort(key = lambda k:ord(k[0]))
	return x[0][0]
	
if __name__ == '__main__':
	while True:
		text = input()
		print(checkio(text))