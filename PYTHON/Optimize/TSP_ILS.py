"""
@author: zll
description：
迭代局部搜索算法求解TSP
"""

import random
import time
import math
import copy

max_iterations = 10
max_no_improve = 10
CITY_SIZE = 52  # 城市数量

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

# 优化值
Delta = [[0 for i in range(CITY_SIZE)] for j in range(CITY_SIZE)]


class Solution:
    def __init__(self):
        self.cost = 0
        self.route = []

    def copy(self):
        solution = Solution()
        solution.cost = self.cost
        solution.route = copy.deepcopy(self.route)
        return solution


def ILS():

    # 计算路径总长度
    def cost_total(city_list):
        cost = 0
        for i in range(CITY_SIZE - 1):
            cost += distance_2city(city_list[i], city_list[i + 1])
        cost += distance_2city(city_list[CITY_SIZE - 1], city_list[0])
        return cost

    # 计算两个城市间距离

    def distance_2city(c1, c2):
        dis = math.sqrt((city[c1][0] - city[c2][0]) **
                        2 + (city[c1][1] - city[c2][1]) ** 2)
        return dis

    # 本地局部搜索，找出局部最优解，边界条件 max_no_improve
    def local_search(best_solution):

        # 颠倒数组中下标begin到end的元素位置
        def swap_element(city_list, begin, end):
            while begin < end:
                temp = city_list[begin]
                city_list[begin] = city_list[end]
                city_list[end] = temp
                begin += 1
                end -= 1

        # 邻域动作 反转index_i <-> index_j 间的元素
        def two_opt_swap(cities_route, index_i, index_j):
            new_cities_route = copy.deepcopy(cities_route)
            swap_element(new_cities_route, index_i, index_j)
            return new_cities_route

        # 计算邻域操作优化值
        def calc_delta(i, k, city_list):
            '''
    以下计算说明：
    对于每个方案，翻转以后没必要再次重新计算总距离
    只需要在翻转的头尾做个小小处理

    比如：
    有城市序列   1-2-3-4-5 总距离 = d12 + d23 + d34 + d45 + d51 = A
    翻转后的序列 1-4-3-2-5 总距离 = d14 + d43 + d32 + d25 + d51 = B
    由于 dij 与 dji是一样的，所以B也可以表示成 B = A - d12 - d45 + d14 + d25
    下面的优化就是基于这种原理
            '''

            delta = 0

            if i == 0 and k == CITY_SIZE - 1:
                delta = 0
            else:
                i2 = (i - 1 + CITY_SIZE) % CITY_SIZE
                k2 = (k + 1) % CITY_SIZE
                delta = 0
                - distance_2city(city_list[i2], city_list[i])
                + distance_2city(city_list[i2], city_list[k])
                - distance_2city(city_list[k], city_list[k2])
                + distance_2city(city_list[i], city_list[k2])

            return delta

        # 更新Delta
        def Update(i, k, route):
            '''
    小编注：这是一个计算每次领域动作后路径长度改变值的小优化，在测试中我们暂时忽略这个优化。 
    去重处理，对于Delta数组来说，对于城市序列1-2-3-4-5-6-7-8-9-10，如果对3-5应用了邻域操作2-opt ， 事实上对于
    7-10之间的距离是不需要重复计算的,即后半部分是不变的。 所以用Delta提前预处理一下。
    当然由于这里的计算本身是O（1） 的，事实上并没有带来时间复杂度的减少（更新操作反而增加了复杂度） 
    如果delta计算 是O（n）的，这种去重操作效果是明显的。 
            '''
            if i != 0 and k != (CITY_SIZE - 1):
                # 如果不是边界，更新(i-1, k + 1)之间的

                i -= 1
                k += 1

                for j in range(i, k + 1):
                    for l in range(j + 1, CITY_SIZE):
                        Delta[j][l] = calc_delta(j, l, route)

                for j in range(0, k):
                    for l in range(i, k + 1):
                        if j >= l:
                            continue
                        Delta[j][l] = calc_delta(j, l, route)
            else:

                for i in range(CITY_SIZE - 1):
                    for k in range(i + 1, CITY_SIZE):
                        Delta[i][k] = calc_delta(i, k, route)

        count = 0
        inital_cost = best_solution.cost  # 初始花费
        new_solution = Solution()

        for i in range(CITY_SIZE - 1):
            for k in range(i + 1, CITY_SIZE):  # 注意Delta数组中行的数字必定大于列的数字
                Delta[i][k] = calc_delta(i, k, best_solution.route)

        deadprotect = 0
        while count < max_no_improve and deadprotect < 3 * max_no_improve:
            # 枚举排列

            for i in range(CITY_SIZE - 1):
                for k in range(i + 1, CITY_SIZE):
                    # 邻域动作
                    new_solution.route = two_opt_swap(
                        best_solution.route, i, k)
                    new_solution.cost = inital_cost + Delta[i][k]
                    if new_solution.cost < best_solution.cost:
                        count = 0  # 找到了更好的解，重新搜索这个解所在的邻域
                        best_solution = new_solution.copy()
                        inital_cost = best_solution.cost
                        Update(i, k, best_solution.route)
            count += 1
            deadprotect += 1

    # 判断接受准则

    def AcceptanceCriterion(cities_route, new_cities_route):
        AcceptLimite = 500
        c1 = cost_total(cities_route)
        c2 = cost_total(new_cities_route) - 500
        if c1 < c2:
            return False
        else:
            return True

    # 将城市序列分成4块，然后按块重新打乱顺序。用于扰动函数
    def double_bridge_move(cities_route, new_cities_route):
        pos1 = random.randint(1, int(CITY_SIZE / 3))
        pos2 = random.randint(int(CITY_SIZE / 3), 2 * int(CITY_SIZE / 3))
        pos3 = random.randint(2 * int(CITY_SIZE / 3), 3 * int(CITY_SIZE / 3))

        deadprotect = 0
        while True:

            i = 0
            for j in range(pos3, CITY_SIZE):
                new_cities_route[i] = cities_route[j]
                i += 1

            for j in range(pos2, pos3):
                new_cities_route[i] = cities_route[j]
                i += 1

            for j in range(pos1, pos2):
                new_cities_route[i] = cities_route[j]
                i += 1

            for j in range(0, pos1):
                new_cities_route[i] = cities_route[j]
                i += 1

            deadprotect += 1
            if deadprotect == 5:
                break

            if AcceptanceCriterion(cities_route, new_cities_route):
                break

    # 扰动

    def perturbation(best_solution, current_solution):
        double_bridge_move(best_solution.route, current_solution.route)
        current_solution.cost = cost_total(current_solution.route)

    best_solution = Solution()  # 全局最优解

    # 产生初始解
    for i in range(CITY_SIZE):
        best_solution.route.append(i)
    random.shuffle(best_solution.route)
    best_solution.cost = cost_total(best_solution.route)

    current_solution = best_solution.copy()  # 局部最优解

    # 开始搜索
    local_search(best_solution)
    for i in range(max_iterations):

        perturbation(best_solution, current_solution)
        local_search(current_solution)

        if current_solution.cost < best_solution.cost:
            best_solution = current_solution.copy()
        print("迭代搜索 ", i, " 次   ", "最优解 = ", best_solution.cost,
              " 当前解 = ", current_solution.cost)

    result = dict()
    result['cost'] = best_solution.cost
    result['route'] = best_solution.route
    result['test cost'] = cost_total(best_solution.route)

    return result


def main():
    start = time.time()
    result = ILS()
    end = time.time()
    duration = end - start
    result['time'] = duration

    print(result)


if __name__ == '__main__':
    main()
