import numpy as np

num = 32
dismat = np.zeros((num, num))
with open('data.txt', 'r') as of:
    i = 1
    for line in of:
        line = line.replace('\n', '')
        linestr = line.split(' ')
        print(linestr, i)
        for j in range(i):
            if j == i:
                continue
            dismat[i][j] = dismat[j][i] = linestr[j]
        i += 1
print(dismat)