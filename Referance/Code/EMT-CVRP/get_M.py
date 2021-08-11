import l1ls as L
import math
import numpy as np
from cvxopt import matrix, solvers
from random import shuffle
import os
problem_dir = 'benchmark\\select\\'
EPS = 1e-5

inputs_select = [
    problem_dir+'A-n54-k7-h-v1.txt',
    problem_dir+'A-n54-k7-h-v2.txt',
    problem_dir+'A-n62-k8-h-v1.txt',
    problem_dir+'A-n62-k8-h-v2.txt',
    problem_dir+'A-n80-k10-h-v1.txt',
    problem_dir+'A-n80-k10-h-v2.txt',
    problem_dir+'B-n50-k7-h-v1.txt',
    problem_dir+'B-n50-k7-h-v2.txt',
    problem_dir+'B-n64-k9-h-v1.txt',
    problem_dir+'B-n64-k9-h-v2.txt',
    problem_dir+'B-n78-k10-h-v1.txt',
    problem_dir+'B-n78-k10-h-v2.txt',
    problem_dir+'P-n50-k8-h-v1.txt',
    problem_dir+'P-n50-k8-h-v2.txt',
    problem_dir+'P-n60-k10-h-v1.txt',
    problem_dir+'P-n60-k10-h-v2.txt',
    problem_dir+'P-n76-k5-h-v1.txt',
    problem_dir+'P-n76-k5-h-v2.txt',

    problem_dir+'A-n54-k7-m-v1.txt',
    problem_dir+'A-n54-k7-m-v2.txt',
    problem_dir+'A-n62-k8-m-v1.txt',
    problem_dir+'A-n62-k8-m-v2.txt',
    problem_dir+'A-n80-k10-m-v1.txt',
    problem_dir+'A-n80-k10-m-v2.txt',
    problem_dir+'B-n50-k7-m-v1.txt',
    problem_dir+'B-n50-k7-m-v2.txt',
    problem_dir+'B-n64-k9-m-v1.txt',
    problem_dir+'B-n64-k9-m-v2.txt',
    problem_dir+'B-n78-k10-m-v1.txt',
    problem_dir+'B-n78-k10-m-v2.txt',
    problem_dir+'P-n50-k8-m-v1.txt',
    problem_dir+'P-n50-k8-m-v2.txt',
    problem_dir+'P-n60-k10-m-v1.txt',
    problem_dir+'P-n60-k10-m-v2.txt',
    problem_dir+'P-n76-k5-m-v1.txt',
    problem_dir+'P-n76-k5-m-v2.txt',

    problem_dir+'A-n54-k7-l-v1.txt',
    problem_dir+'A-n54-k7-l-v2.txt',
    problem_dir+'A-n62-k8-l-v1.txt',
    problem_dir+'A-n62-k8-l-v2.txt',
    problem_dir+'A-n80-k10-l-v1.txt',
    problem_dir+'A-n80-k10-l-v2.txt',
    problem_dir+'B-n50-k7-l-v1.txt',
    problem_dir+'B-n50-k7-l-v2.txt',
    problem_dir+'B-n64-k9-l-v1.txt',
    problem_dir+'B-n64-k9-l-v2.txt',
    problem_dir+'B-n78-k10-l-v1.txt',
    problem_dir+'B-n78-k10-l-v2.txt',
    problem_dir+'P-n50-k8-l-v1.txt',
    problem_dir+'P-n50-k8-l-v2.txt',
    problem_dir+'P-n60-k10-l-v1.txt',
    problem_dir+'P-n60-k10-l-v2.txt',
    problem_dir+'P-n76-k5-l-v1.txt',
    problem_dir+'P-n76-k5-l-v2.txt',
]


inputs = inputs_select
file_len = len(inputs)

def get_a(x, y, x1, y1):
    return (x1*x+y1*y) / (x1*x1+y1*y1)
def get_data(file_name):
    data = []
    with open(file_name) as f:
        lines = f.readlines()
        for i in range(1, lines.__len__()):
            line = lines[i].split()
            data.append([int(var) for var in line])
    n = 2
    m = data.__len__() - 1
    res = []
    for i in range(data.__len__()):
        res.append(data[i][:-1])

    # centralization
    for i in range(1, res.__len__()):
        for j in range(n):
            res[i][j] = res[i][j] - res[0][j]
    res = res[1:]

    # normalization
    var_x = 0
    var_y = 0
    for i in range(len(res)):
        var_x = var_x + (res[i][0]) * (res[i][0])
        var_y = var_y + (res[i][1]) * (res[i][1])
    var_x = math.sqrt(var_x/m)
    var_y = math.sqrt(var_y/m)

    for i in range(len(res)):
        res[i][0] = (res[i][0]) / var_x
        res[i][1] = (res[i][1]) / var_y

    res = np.array(res).transpose()
    # print(res)
    return res

eps = 0.001

def get_distance(x1, y1, x2, y2):
    return math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
def repair_1(X, y, res):
    distances = []
    n, m = X.shape
    means_distance = 0.0
    choices = []
    for col in range(m):
        means_distance = means_distance + get_distance(X[0][col], X[1][col], y[0], y[1])
        if(abs(res[col]) > eps):
            choices.append(col)
        distances.append(get_distance(X[0][col], X[1][col], y[0], y[1]))
    means_distance = means_distance / col

    count = 0
    for col in choices:
        if(distances[col] > means_distance):
            count = count + 1

    min_idx = np.argmin(np.array(distances))
    if(distances[min_idx] < eps or count * 2 > len(choices)):
        for i in range(res.shape[0]):
            res[i] = 0
        res[min_idx] = get_a(y[0], y[1], X[0][min_idx], X[1][min_idx])

    return res


def SQR(x):
    return x*x
def get_W(x, y):
    col = x.shape[1]
    W = np.zeros([col, col])
    dist = []
    for i in range(col):
        dist.append(math.sqrt(SQR(x[0][i]-y[0])) + SQR(x[1][i]-y[1]))
    min_dist = min(dist)
    for i in range(col):
        W[i][i] = math.exp(dist[i] - min_dist) * dist[i]
    return W
def get_M(A, B):
    M = []
    for i in range(B.shape[1]):
        y = []
        y.append(B[0][i])
        y.append(B[1][i])
        y = np.array(y, dtype='f8')

        x = np.array(A)
        W = get_W(x, y) + EPS * np.diag(np.ones([A.shape[1]]))
        inv_W = np.mat(W).I
        rel_tol = 0.01
        tx = np.array(np.matmul(x, inv_W))
        [res, status, hist] = L.l1ls_nonneg(tx, y, lmbda=1, tar_gap=rel_tol, quiet=True)
        res = np.array(np.matmul(inv_W, res))
        # res = repair_1(A, y, res)
        temp = []
        for j in range(res.shape[1]):
            if(math.fabs(res[0][j]) < eps):
                temp.append(0)
            else:
                temp.append(round(res[0][j], 2))

        M.append(temp)
    M = np.array(M).transpose()
    return M
def print_M(M):
    row, col = M.shape
    M = M.tolist()
    msg = ''
    for i in range(row):
        for j in range(col):
            M[i][j] = round(M[i][j], 3)
            msg = msg + '{}'.format(M[i][j]).ljust(6)
        msg = msg + '\n'
    # print(msg)
    return msg

def solver_1():
    for l in range(0, file_len, 2):
        r = l + 2
        for file_1 in range(l, r, 1):
            for file_2 in range(l, r, 1):
                output_file = 'M_' + str(file_1) + '_' + str(file_2)

                # print(file_1, file_2)
                A = get_data(inputs[file_1])
                B = get_data(inputs[file_2])
                # print(A)
                # print(B)

                M = get_M(A, B)
                print(output_file)
                msg = print_M(M)
                os.system("pause")

                # with open(problem_dir + output_file, 'w+', encoding='utf-8') as f:
                #     f.write(msg)

if __name__ == '__main__':
    solver_1()