"""
@author: zll
description：
模拟退火算法求解TSP
"""

import random
import time
import math


T0 = 50000.0  # 初始温度
T_min = 1e-8
q = 0.98  # 退火系数
K = 1  # 公式中的常数K
L = 1000  # 每个温度时的迭代次数，即链长
N = 52  # 城市数量

# 柏林52城算例
city = [
    [565, 575], [25, 185], [345, 750], [945, 685], [845, 655],
    [880, 660], [25, 230], [525, 1000], [580, 1175], [650, 1130],
    [1605, 620], [1220, 580], [1465, 200], [1530, 5],
    [845, 680], [725, 370], [145, 665],
    [415, 635], [510, 875], [560, 365], [300, 465], [520, 585], [480, 415],
    [835, 625], [975, 580], [1215, 245], [1320, 315], [1250, 400], [660, 180],
    [410, 250], [420, 555], [575, 665], [1150, 1160], [700, 580], [685, 595],
    [685, 610], [770, 610], [795, 645], [720, 635], [760, 650], [475, 960],
    [95, 260], [875, 920], [700, 500], [555, 815], [830, 485], [1170, 65],
    [830, 610], [605, 625], [595, 360], [1340, 725], [1740, 245]
]


def cal_distance(id1, id2):
    distance = math.sqrt((city[id1][0] - city[id2][0])
                         ** 2 + (city[id1][1] - city[id2][1])**2)
    return distance


def path_len(city_list):
    path = 0
    for i in range(N):
        path += cal_distance(city_list[i], city_list[i + 1])
    return path


def SA():

    def creat_new(city_list):
        new_list = city_list[:]
        i = random.randint(1, N - 1)
        j = random.randint(1, N - 1)
        while j == i:
            j = random.randint(1, N - 1)
        temp = new_list[i]
        new_list[i] = new_list[j]
        new_list[j] = temp
        return new_list

    count = 0
    best_route = []  # 全局最优解
    for i in range(N):
        best_route.append(i)
    best_route.append(0)
    best = path_len(best_route)
    T = T0
    while T > T_min:
        for i in range(N):
            new_route = creat_new(best_route)
            new = path_len(new_route)
            delta = new - best
            if delta < 0:
                best_route = new_route[:]
                best = new
            else:
                r = random.random()
                if delta / (K * T) < 500 and math.exp(delta / (K * T)) < r:
                    best_route = new_route[:]
                    best = new
        T *= q
        count += 1
        print("共降温", count, "次，当前满意解为", best)
    result = dict()
    result['cost'] = best
    result['route'] = best_route
    return result


def main():
    start = time.time()
    result = SA()
    end = time.time()
    duration = end - start
    result['time'] = duration
    print("初始温度T0=", T0, ",降温系数q=", q, ",每个温度迭代", L, "次")
    print(result)


if __name__ == '__main__':
    main()
