def f(a):
	a = list(str(a))
	min = int(''.join(i for i in sorted(a)))
	max = int(''.join(i for i in sorted(a ,reverse = True)))
	print(max,'-',min)
	return max-min

if __name__ == '__main__':
	a = int(input())
	while True:
		a = f(a)
		if a<1000:
			a *= 10
		if a == 6174:
			print('success')
			break
