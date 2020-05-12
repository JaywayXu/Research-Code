import os

G = []

with open('x.txt', 'r') as of:
    for line in of:
        line = line.replace('\n', '')
        linestr = line.split('\t')
        G.append(linestr)


def get_QinYuanZhi(a, b):  # a,b 为相同长度的一维数组
    '''获取两个材料的亲缘值'''
    x = 0
    for i in range(len(a)):
        if a[i] == b[i]:
            x += 1
    return x


def get_pack_QYZ(a):  # a 为二维数组
    '''获取混合的亲缘值'''
    lis = [[0]*len(a) for i in range(len(a))]
    qyz = 0  # 亲缘值
    count = 0  # 计数
    if len(a) == 1:  # 只有一种
        return 10
    for i in range(len(a)):
        for j in range(i, len(a)):
            if i == j:
                continue
            q = get_QinYuanZhi(a[i], a[j])
            lis[i][j] = lis[j][i] = q
            qyz += q
            count += 1
    qyz /= count
    for i in lis:
        print(i)
    return qyz


if __name__ == '__main__':
    print("整个种群亲缘值："+str(get_pack_QYZ(G)))
