import numpy as np
import matplotlib.pyplot as plt
import time

plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号


class ACO:
    def __init__(self, coordinates=np.zeros((0)), distMatrix=np.zeros((0)), numAnt=20, alpha=1, beta=8, rho=0.3, method=1, iterMax=60):
        '''蚁群优化算法初始化'''
        # 获取城市的距离矩阵
        self.coordinates = coordinates  # 城市坐标矩阵
        if self.coordinates.any():
            self.distMatrix = self.getDistMatrix(coordinates)
        else:
            self.distMatrix = distMatrix

        # 基本参数
        self.numCity = self.distMatrix.shape[0]  # 城市个数
        self.numAnt = numAnt  # 蚂蚁数量
        self.alpha = alpha  # 信息素重要程度因子
        self.beta = beta  # 启发函数重要程度因子
        self.rho = rho  # 信息素的挥发速度
        self.iterMax = iterMax  # 迭代最大次数
        self.method = method  # 1为蚁量，2为蚁密
        self.Q = 1  # 重要程度常数

        # 统计参数
        self.lengthAver = np.zeros(self.iterMax)  # 各代路径的平均长度
        self.lengthBest = np.zeros(self.iterMax)  # 各代及其之前遇到的最佳路径长度
        self.pathBest = np.zeros(
            (self.iterMax, self.numCity))  # 各代及其之前遇到的最佳路径长度

        # 临时参数
        # 启发函数矩阵，表示蚂蚁从城市i转移到矩阵j的期望程度
        self.etaTable = 1.0 / \
            (self.distMatrix + np.diag([1e10] * self.numCity))
        self.pheromoneTable = np.ones((self.numCity, self.numCity))  # 信息素矩阵
        self.pathTable = np.zeros(
            (self.numAnt, self.numCity)).astype(int)  # 路径记录表
        self.length = np.zeros(self.numAnt)  # 各个蚂蚁的路径距离

    def getDistMatrix(self, coordinates):
        '''根据坐标点求距离矩阵'''
        num = coordinates.shape[0]
        distMatrix = np.zeros((num, num))
        for i in range(num):
            for j in range(i, num):
                distMatrix[i][j] = distMatrix[j][i] = np.linalg.norm(
                    coordinates[i] - coordinates[j])
        return distMatrix

    def getBest_LengthNp_Time(self):
        '''开始运行，获取最短长度集合、运行时间'''
        t_start = time.time()  # 开始计时
        # 进入迭代
        iter = 0
        while iter < self.iterMax:
            self.putAnts()  # 产生蚂蚁起点城市
            self.length = np.zeros(self.numAnt)  # 各个蚂蚁的路径距离
            for antIter in range(self.numAnt):  # 对每只蚂蚁求路径
                self.antState(antIter)  # 每只蚂蚁求路径
            self.changePheromone(iter)  # 更新信息素
            iter += 1
        t_end = time.time()  # 结束计时
        return self.lengthBest, t_end-t_start

    def putAnts(self):
        '''随机产生各个蚂蚁的起点城市'''
        if self.numAnt <= self.numCity:  # 城市数比蚂蚁数多
            self.pathTable[:, 0] = np.random.permutation(
                range(0, self.numCity))[:self.numAnt]  # 随机分布城市并截取蚂蚁数量个
        else:  # 蚂蚁数比城市数多
            splitTimes = self.numAnt//self.numCity
            for i in range(splitTimes):
                self.pathTable[self.numCity*i:self.numCity*(i+1), 0] = np.random.permutation(
                    range(0, self.numCity))[:]
            self.pathTable[self.numCity*splitTimes:, 0] = np.random.permutation(range(0, self.numCity))[
                :self.numAnt - self.numCity*splitTimes]

    def antState(self, antIter):
        '''一只蚂蚁求路径'''
        i = antIter
        visiting = self.pathTable[i, 0]  # 当前所在的城市
        unvisited = set(range(self.numCity))  # 未访问的城市
        unvisited.remove(visiting)  # 删除当前城市
        for j in range(1, self.numCity):  # 访问剩余的numCity-1个城市
            # 每次用轮盘赌的方法选择下一个要访问的城市
            listUnvisited = list(unvisited)
            probTrans = np.zeros(len(listUnvisited))  # 选择每条路径的概率
            for k in range(len(listUnvisited)):  # 按照信息素alpha和启发函数beta的比重求到每条路径的概率
                probTrans[k] = np.power(self.pheromoneTable[visiting][listUnvisited[k]], self.alpha) \
                    * np.power(self.etaTable[visiting][listUnvisited[k]], self.beta)
            cumsumProbTrans = (probTrans / sum(probTrans)
                               ).cumsum()  # 累加：[0.1, 0.6, 0.3]->[0.1, 0.7, 1.0]
            rand = np.random.rand()  # 0-1之间的均匀分布
            # 求第一个大于rand元素的下标：rand=0.3->[0.1, 0.2, 0.4, 1.0] -> [[2, 3]] -> 2
            # print(cumsumProbTrans)
            k = listUnvisited[(np.where(cumsumProbTrans > rand)[0])[0]]
            self.pathTable[i, j] = k  # 蚂蚁走过的路径添加到路径表中
            unvisited.remove(k)  # 在访问城市set中删除该城市
            self.length[i] += self.distMatrix[visiting][k]
            visiting = k
        # 加上最后一个城市和第一个城市的距离
        self.length[i] += self.distMatrix[visiting][self.pathTable[i, 0]]

    def changePheromone(self, iter):
        '''更新信息素'''
        # 包含所有蚂蚁的一个迭代结束后，统计本次迭代的参数
        self.lengthAver[iter] = self.length.mean()  # 求均值
        if iter == 0:
            self.lengthBest[iter] = self.length.min()
            self.pathBest[iter] = self.pathTable[self.length.argmin()].copy()
        else:
            if self.length.min() > self.lengthBest[iter - 1]:  # 本次结果比上一次差
                self.lengthBest[iter] = self.lengthBest[iter - 1]
                self.pathBest[iter] = self.pathBest[iter - 1].copy()
            else:
                self.lengthBest[iter] = self.length.min()
                self.pathBest[iter] = self.pathTable[self.length.argmin()
                                                     ].copy()
        # 更新信息素
        changePheromoneTable = np.zeros((self.numCity, self.numCity))
        for i in range(self.numAnt):
            for j in range(self.numCity - 1):
                changePheromoneTable[self.pathTable[i, j]][self.pathTable[i, j + 1]] += self.antMethod(
                    self.distMatrix[self.pathTable[i, j]][self.pathTable[i, j + 1]])
            changePheromoneTable[self.pathTable[i, j + 1]][self.pathTable[i, 0]] += self.antMethod(
                self.distMatrix[self.pathTable[i, j + 1]][self.pathTable[i, 0]])
        # 信息素挥发
        self.pheromoneTable = (1 - self.rho) * self.pheromoneTable + \
            changePheromoneTable  # 计算信息素公式

    def antMethod(self, dist):
        '''计算信息素的方法'''
        if self.method == 1:  # 蚁量模型
            return self.Q / dist
        elif self.method == 2:  # 蚁密模型
            return self.Q

    def drawLengthIter(self):
        '''画出路径长度迭代图'''
        # 平均路径长度
        fig, axes = plt.subplots(nrows=2, ncols=1, figsize=(12, 10))
        axes[0].plot(self.lengthAver, 'b', marker=u'')
        axes[0].set_title(u'平均路径长度')
        axes[0].set_xlabel(u'迭代')
        # 最短路径长度
        axes[1].plot(self.lengthBest, 'b', marker=u'')
        axes[1].set_title(u'最短路径长度')
        axes[1].set_xlabel(u'迭代')
        plt.show()
        plt.close()

    def drawBestRoute(self):
        '''画出最优路径图'''
        if not self.coordinates.any():
            return False
        bestpath = self.pathBest[-1]

        title = u"最短路径图-TSP节点数量：%s" % (self.numCity)
        plt.figure(title)

        # 设置坐标轴范围
        # plt.xlim([np.min(self.coordinates[:, 0])-20,
        #           np.max(self.coordinates[:, 0])+20])
        # plt.ylim([np.min(self.coordinates[:, 1])-20,
        #           np.max(self.coordinates[:, 1])+20])

        # 画连线
        for i in range(self.numCity - 1):
            m = int(bestpath[i])
            n = int(bestpath[i + 1])
            plt.plot([self.coordinates[m][0], self.coordinates[n][0]], [
                     self.coordinates[m][1], self.coordinates[n][1]], 'b', zorder=1)
        plt.plot([self.coordinates[int(bestpath[0])][0], self.coordinates[int(n)][0]],
                 [self.coordinates[int(bestpath[0])][1], self.coordinates[int(n)][1]], 'b', zorder=1)

        # 画点
        plt.scatter(
            self.coordinates[:, 0], self.coordinates[:, 1], c='k', marker='.', zorder=2)

        plt.title(title)
        plt.xlabel(u"最短路径长度：%8.8s" % self.lengthBest[-1])
        plt.savefig('./TSP_ACO_IMG/%s.jpg' % (title))
        #plt.show()
        plt.close()


if __name__ == '__main__':
    # testCoordinates = np.array([[565, 575], [25, 185], [345, 750], [945, 685], [845, 655], [880, 660], [25, 230], [525, 1000], [580, 1175], [650, 1130], [1605, 620], [1220, 580], [1465, 200], [1530, 5], [845, 680], [725, 370], [145, 665], [415, 635], [510, 875], [560, 365], [300, 465], [520, 585], [480, 415], [835, 625], [975, 580], [
    #     1215, 245], [1320, 315], [1250, 400], [660, 180], [410, 250], [420, 555], [575, 665], [1150, 1160], [700, 580], [685, 595], [685, 610], [770, 610], [795, 645], [720, 635], [760, 650], [475, 960], [95, 260], [875, 920], [700, 500], [555, 815], [830, 485], [1170, 65], [830, 610], [605, 625], [595, 360], [1340, 725], [1740, 245]])
    # testDistMat = np.array([[1, 1, 1], [2, 2, 2], [3, 3, 3]])
    # x = ACO(coordinates=testCoordinates)
    # x = ACO(distMatrix=testDistMat)
    # bestLengthNp, bestTime = x.getBest_LengthNp_Time()
    # print(bestLengthNp[-1], bestTime)
    # x.drawLengthIter()
    # x.drawBestRoute()

    testCoordinatesList = [[[128, 839], [329, 127], [192, 405], [127, 252], [737, 227], [562, 597], [965, 537], [685, 889], [586, 512], [11, 264], [
        580, 595], [216, 187], [477, 144], [882, 8], [359, 346], [912, 205], [758, 396], [331, 211], [73, 628], [816, 530]],
        [[509, 921], [553, 203], [528, 916], [846, 251], [306, 499], [861, 953], [372, 485], [840, 285], [232, 358], [499, 772], [314, 843], [515, 198], [
            507, 415], [379, 317], [624, 967], [409, 230], [443, 838], [932, 919], [672, 244], [326, 487], [614, 692], [368, 73], [329, 314], [243, 160]],
        [[105, 484], [367, 837], [434, 802], [42, 426], [652, 803], [394, 352], [673, 624], [598, 851], [453, 54], [999, 520], [505, 146], [715, 752], [428, 648], [897, 140], [
            388, 385], [581, 278], [109, 663], [301, 616], [932, 445], [301, 498], [405, 363], [266, 352], [83, 289], [553, 362], [43, 113], [725, 710], [563, 754], [810, 54]],
        [[212, 647], [439, 919], [848, 116], [354, 583], [512, 550], [992, 714], [647, 368], [618, 280], [750, 407], [84, 988], [224, 880], [413, 603], [987, 632], [266, 501], [249, 128], [613, 413], [
            704, 626], [487, 577], [42, 362], [699, 391], [443, 68], [101, 40], [621, 514], [452, 251], [988, 825], [264, 537], [690, 79], [279, 588], [727, 928], [906, 591], [39, 268], [615, 139]],
        [[696, 619], [473, 903], [36, 181], [255, 341], [241, 433], [152, 183], [881, 907], [37, 188], [421, 416], [465, 357], [541, 899], [368, 205], [496, 449], [98, 553], [828, 182], [104, 656], [465, 56], [486, 559], [
            547, 438], [717, 766], [671, 675], [844, 399], [549, 90], [265, 619], [958, 905], [762, 713], [610, 589], [129, 679], [846, 778], [915, 396], [291, 798], [205, 12], [647, 624], [665, 88], [107, 417], [488, 770]],
        [[121, 72], [798, 687], [618, 450], [203, 937], [894, 871], [541, 10], [801, 172], [963, 283], [87, 173], [588, 444], [266, 68], [56, 157], [220, 407], [281, 13], [31, 887], [526, 223], [957, 15], [769, 506], [940, 494], [733, 954], [
            124, 176], [866, 181], [381, 945], [676, 899], [526, 520], [275, 811], [307, 673], [582, 174], [523, 664], [506, 812], [89, 124], [990, 651], [949, 412], [337, 327], [186, 623], [912, 211], [243, 537], [871, 623], [256, 364], [260, 654]]]

    for i in testCoordinatesList:
        aco = ACO(coordinates=np.array(i))
        bestLengthNp, bestTime = aco.getBest_LengthNp_Time()
        print(bestLengthNp[-1], bestTime)
        aco.drawBestRoute()
