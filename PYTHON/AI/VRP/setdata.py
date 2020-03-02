import math

Nation_point = [[637, 159], [465, 683], [199, 671], [455, 1213], [1135, 461],
                [1015, 1009], [919, 1189], [1231, 613]]

def get_(a, b):
    x2 = pow(a[0]-b[0], 2)
    y2 = pow(a[1]-b[1], 2)
    edge = math.sqrt(x2+y2)
    return int(edge)

N = 8
matrix = [[0]*N for _ in range(N)]
for i in range(N):
    for j in range(N):
        matrix[i][j] = get_(Nation_point[i], Nation_point[j])

for i in matrix:
    print(i)
