a = [0,0,0,0,0,0,0,0,0]

for i in range(9):
	a[0]=i
	for i in range(9):
		a[1]=i
		for i in range(9):
			a[2]=i
			for i in range(9):
				a[3]=i
				for i in range(9):
					a[4]=i
					for i in range(9):
						a[5]=i
						for i in range(9):
							a[6]=i
							for i in range(9):
								a[7]=i
								for i in range(9):
									a[8]=i
									if len(a)==len(set(a)):
											if a[0]<a[1]<a[2] and a[3]<a[4]<a[5] and a[6]<a[7]<a[8]:
												if a[0]<a[3]<a[6] and a[1]<a[4]<a[7] and a[2]<a[5]<a[8]:
													if a[0]<a[4]<a[8] and a[1]<a[5] and a[3]<a[7]:
														if a[2]<a[4]<a[6] and a[1]<a[3] and a[5]<a[7]:
															print(a[0],a[1],a[2])
															print(a[3],a[4],a[5])
															print(a[6],a[7],a[8],"\n")