import numpy as np
import matplotlib.pyplot as plt
import time


class ACO:
    def __init__(self, coordinates=np.zeros((0)), distMatrix=np.zeros((0)), numAnt=30, alpha=1, beta=8, rho=0.1, iterMax=50):
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
        self.Q = 1  # 重要程度常数
        self.method = 1  # 1为蚁量，2为蚁密

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

    def getBest_Path_Length_Time(self):
        '''获取最好的路径和长度'''
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
        return self.pathBest[-1], self.lengthBest[-1], t_end-t_start

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
        axes[0].plot(self.lengthAver, 'k', marker=u'')
        axes[0].set_title('Average Length')
        axes[0].set_xlabel(u'iteration')
        # 最短路径长度
        axes[1].plot(self.lengthBest, 'k', marker=u'')
        axes[1].set_title('Best Length')
        axes[1].set_xlabel(u'iteration')
        plt.show()

    def drawBestRoute(self):
        '''画出最优路径图'''
        if not self.coordinates.any():
            return False
        bestpath = self.pathBest[-1]
        plt.plot(self.coordinates[:, 0],
                 self.coordinates[:, 1], 'r.', marker=u'$\cdot$')
        plt.xlim([np.min(self.coordinates[:, 0])-10,
                  np.max(self.coordinates[:, 0])+10])
        plt.ylim([np.min(self.coordinates[:, 1])-10,
                  np.max(self.coordinates[:, 1])+10])

        for i in range(self.numCity - 1):
            m = int(bestpath[i])
            n = int(bestpath[i + 1])
            plt.plot([self.coordinates[m][0], self.coordinates[n][0]], [
                     self.coordinates[m][1], self.coordinates[n][1]], 'k')
        plt.plot([self.coordinates[int(bestpath[0])][0], self.coordinates[int(n)][0]],
                 [self.coordinates[int(bestpath[0])][1], self.coordinates[int(n)][1]], 'b')
        ax = plt.gca()
        ax.set_title("Best Path, length is % s" % self.lengthBest[-1])
        ax.set_xlabel('X axis')
        ax.set_ylabel('Y_axis')
        plt.show()


if __name__ == '__main__':
    testCoordinates = np.array([[565, 575], [25, 185], [345, 750], [945, 685], [845, 655], [880, 660], [25, 230], [525, 1000], [580, 1175], [650, 1130], [1605, 620], [1220, 580], [1465, 200], [1530, 5], [845, 680], [725, 370], [145, 665], [415, 635], [510, 875], [560, 365], [300, 465], [520, 585], [480, 415], [835, 625], [975, 580], [
        1215, 245], [1320, 315], [1250, 400], [660, 180], [410, 250], [420, 555], [575, 665], [1150, 1160], [700, 580], [685, 595], [685, 610], [770, 610], [795, 645], [720, 635], [760, 650], [475, 960], [95, 260], [875, 920], [700, 500], [555, 815], [830, 485], [1170, 65], [830, 610], [605, 625], [595, 360], [1340, 725], [1740, 245]])

    testDistMat = np.array([[1, 1, 1], [2, 2, 2], [3, 3, 3]])

    x = ACO(coordinates=testCoordinates)
    # x = ACO(distMatrix=testDistMat)
    print(x.getBest_Path_Length_Time())
    x.drawLengthIter()
    x.drawBestRoute()
