def jiecheng(x):
	a = 1
	for i in range(1,x+1):
		a *= i
	return a

for i in range(100,1000):
	x = [int(z) for z in list(str(i))]
	if jiecheng(x[0])+jiecheng(x[1])+jiecheng(x[2]) == i:
		print(i)