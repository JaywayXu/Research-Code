zimu = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ'*50)
fan = list(reversed(zimu))

def fun(x):
	for i in range(x):
		if i == 0:
			print(" "*(x-1),'A')
			x -= 1
		else:
			st = ''.join(j for j in zimu[:i+1]) + ''.join(j for j in fan[-i:])
			print(" "*(x-1),st)
			x -= 1

if __name__ == '__main__':
	fun(28)
