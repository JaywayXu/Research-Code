text = input()
allwords = text.split(" ")
dic = []
for each in allwords:
	num = 0
	for x in list(each):
		num += ord(x)
	dic.append((each,num))
dic.sort(key = lambda k:k[1],reverse = True)
print(dic[0][0])

'''最佳答案
list1 = text.split(' ')
list1.sort(key = lambda x: - sum([ord(i) - 96 for i in x]))
print(list1[0])
'''