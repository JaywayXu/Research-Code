def f():
	a,b = 2,3
	while True:
		if a<b:
			yield a
			a *= 2
		else:
			yield b
			b *= 3
			
if __name__ == '__main__':
	for i in f():
		print(i)
		input()