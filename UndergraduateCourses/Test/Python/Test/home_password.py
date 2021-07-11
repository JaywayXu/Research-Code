import re

def checkio(data):
	if len(data)>=10:
		if re.search(r'\d',data) and re.search('[a-z]',data) and re.search('[A-Z]',data):
			return True
	return False

pw = input()
print(checkio(pw))
