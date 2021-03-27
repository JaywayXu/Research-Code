import numpy as np
import matplotlib.pyplot as plt
import time
import random
from TSP_ACO import ACO

plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号


f = open("./ACO_Print.txt", 'w+')


class ACOManage:
    '''ACO算法模拟测试类'''

    def __init__(self):
        '''初始化函数'''
        self.Coordinates = []  # TSP坐标图列表
        self.testTimes = 10  # 每个用例测试的次数
        self.testCorNum = 6  # 测试用例的数量
        self.randGraph(20, 4, self.testCorNum)  # 生成测试用例
        self.iterMax = 60  # 迭代最大次数

    def randGraph(self, start, step, nums):
        '''随机生成坐标图'''
        nowNum = start
        for cornum in range(nums):
            cor = []
            for pnum in range(nowNum):
                x = random.randint(0, 1000)
                y = random.randint(0, 1000)
                cor.append([x, y])
            #print("第 %d 个用例，节点个数 %d ：" % (cornum+1, nowNum), file=f)
            print(cor, file=f)
            self.Coordinates.append(np.array(cor))
            nowNum = nowNum + step

    def testAntNum(self):
        '''蚂蚁数量影响测试'''
        start = 10  # 蚂蚁数量开始
        step = 10  # 蚂蚁数量增加步长
        nums = 5  # 蚂蚁数量总测试个数
        print("-蚂蚁数量影响测试", file=f)
        for cornum in range(self.testCorNum):  # 对每个用例
            print("---第%2d 个用例: 坐标点数%d个" %
                  (cornum+1, self.Coordinates[cornum].shape[0]), file=f)
            timeIter = []  # 运行时间迭代列表
            lengthNpIter = []  # 最短路径长度迭代列表
            numant = start  # 最初蚂蚁数量
            labelList = []  # 用于画图例的标签
            labelList.append(numant)
            for n in range(nums):  # 对于每个蚂蚁数量参数
                sumLengthNp = np.zeros(self.iterMax)  # 最短路径迭代记录

                sumTimeList = []  # 总时间记录
                sumLengthList = []  # 最短路径记录
                for t in range(self.testTimes):  # 每个参数下运行测试次数
                    acoTest = ACO(
                        coordinates=self.Coordinates[cornum], numAnt=numant, iterMax=self.iterMax)
                    tLengthNp, tTime = acoTest.getBest_LengthNp_Time()  # 获取最短路径长度迭代列表、运行时间
                    sumTimeList.append(tTime)
                    sumLengthList.append(tLengthNp[-1])
                    sumLengthNp = sumLengthNp + tLengthNp

                aveTime = np.mean(sumTimeList)  # 平均时间均值
                varTime = np.var(sumTimeList)  # 平均时间方差
                aveLength = np.mean(sumLengthList)  # 平均最短路径方差
                varLength = np.var(sumLengthList)  # 平均最短路径方差

                print("-----蚂蚁数量：%3d  时间平均值：%8.8f  时间方差：%8.8f  最短路径平均值：%8.8f  最短路径方差：%8.8f" %
                      (numant, aveTime, varTime, aveLength, varLength), file=f)

                timeIter.append(aveTime)
                lengthNpIter.append(sumLengthNp/self.testTimes)
                numant = numant + step  # 蚂蚁数量增加
                labelList.append(numant)
            # 画最短路径迭代图
            title = u"蚂蚁数量-最短路径收敛图-TSP节点数量：%s" % (
                self.Coordinates[cornum].shape[0])
            xLabel = u"迭代次数"
            yLabel = u"最短路径长度"
            self.drawLengthIter(lengthNpIter, title, xLabel, yLabel, labelList)
            # 画时间参数设置图
            title = u"蚂蚁数量-时间参数图-TSP节点数量：%s" % (
                self.Coordinates[cornum].shape[0])
            xLabel = u"蚂蚁数量参数"
            yLabel = u"平均时间"
            self.drawTimeIter(timeIter, title, xLabel, yLabel, labelList[1:])

    def testAlphaBeta(self):
        '''信息素和启发函数比重影响测试'''
        alphaList = [1, 1, 1, 1, 4, 8, 16]
        betaList = [16, 8, 4, 1, 1, 1, 1]
        nums = 7
        print("-信息素和启发函数比重影响测试", file=f)
        for cornum in range(self.testCorNum):  # 对每个用例
            print("---第%2d 个用例: 坐标点数%d个" %
                  (cornum+1, self.Coordinates[cornum].shape[0]), file=f)
            timeIter = []  # 运行时间迭代列表
            lengthNpIter = []  # 最短路径长度迭代列表
            labelList = []  # 用于画图例的标签
            for n in range(nums):  # 对于每个蚂蚁数量参数
                alpha = alphaList[n]  # 最初信息素重要程度
                beta = betaList[n]  # 最初启发函数重要程度
                labelList.append("%s:%s" % (alpha, beta))
                sumTime = 0  # 总时间记录
                sumLengthNp = np.zeros(self.iterMax)  # 最短路径迭代记录

                sumTimeList = []  # 总时间记录
                sumLengthList = []  # 最短路径记录
                for t in range(self.testTimes):  # 每个参数下运行测试次数
                    acoTest = ACO(
                        coordinates=self.Coordinates[cornum], alpha=alpha, beta=beta, iterMax=self.iterMax)
                    tLengthNp, tTime = acoTest.getBest_LengthNp_Time()  # 获取最短路径长度迭代列表、运行时间
                    sumTimeList.append(tTime)
                    sumLengthList.append(tLengthNp[-1])
                    sumLengthNp = sumLengthNp + tLengthNp

                aveTime = np.mean(sumTimeList)  # 平均时间均值
                varTime = np.var(sumTimeList)  # 平均时间方差
                aveLength = np.mean(sumLengthList)  # 平均最短路径方差
                varLength = np.var(sumLengthList)  # 平均最短路径方差

                print("-----比重：%2d:%2d  时间平均值：%8.8f  时间方差：%8.8f  最短路径平均值：%8.8f  最短路径方差：%8.8f" %
                      (alpha, beta, aveTime, varTime, aveLength, varLength), file=f)

                timeIter.append(aveTime)
                lengthNpIter.append(sumLengthNp/self.testTimes)
            # 画最短路径迭代图
            title = u"信息素和启发函数比重-最短路径收敛图-TSP节点数量：%s" % (
                self.Coordinates[cornum].shape[0])
            xLabel = u"迭代次数"
            yLabel = u"最短路径长度"
            self.drawLengthIter(lengthNpIter, title, xLabel, yLabel, labelList)
            # 画时间参数设置图
            title = u"信息素和启发函数比重-时间参数图-TSP节点数量：%s" % (
                self.Coordinates[cornum].shape[0])
            xLabel = u"信息素和启发函数比重参数"
            yLabel = u"平均时间"
            self.drawTimeIter(timeIter, title, xLabel, yLabel, range(nums))

    def testMethod(self):
        '''信息素计算方式影响测试'''
        methodList = [1, 2]
        methodNameList = ["蚁量算法", "蚁密算法"]
        nums = 2
        print("-信息素计算方式影响测试", file=f)
        for cornum in range(self.testCorNum):  # 对每个用例
            print("---第%2d 个用例: 坐标点数%d个" %
                  (cornum+1, self.Coordinates[cornum].shape[0]), file=f)
            timeIter = []  # 运行时间迭代列表
            lengthNpIter = []  # 最短路径长度迭代列表
            labelList = []  # 用于画图例的标签
            for n in range(nums):  # 对于每个蚂蚁数量参数
                method = methodList[n]  # 方法选择
                labelList.append(methodNameList[n])
                sumTime = 0  # 总时间记录
                sumLengthNp = np.zeros(self.iterMax)  # 最短路径迭代记录

                sumTimeList = []  # 总时间记录
                sumLengthList = []  # 最短路径记录
                for t in range(self.testTimes):  # 每个参数下运行测试次数
                    acoTest = ACO(
                        coordinates=self.Coordinates[cornum], method=method, iterMax=self.iterMax)
                    tLengthNp, tTime = acoTest.getBest_LengthNp_Time()  # 获取最短路径长度迭代列表、运行时间
                    sumTimeList.append(tTime)
                    sumLengthList.append(tLengthNp[-1])
                    sumLengthNp = sumLengthNp + tLengthNp

                aveTime = np.mean(sumTimeList)  # 平均时间均值
                varTime = np.var(sumTimeList)  # 平均时间方差
                aveLength = np.mean(sumLengthList)  # 平均最短路径方差
                varLength = np.var(sumLengthList)  # 平均最短路径方差

                print("-----方法：%s  时间平均值：%8.8f  时间方差：%8.8f  最短路径平均值：%8.8f  最短路径方差：%8.8f" %
                      (methodNameList[n], aveTime, varTime, aveLength, varLength), file=f)

                timeIter.append(aveTime)
                lengthNpIter.append(sumLengthNp/self.testTimes)
            # 画最短路径迭代图
            title = u"信息素计算方式-最短路径收敛图-TSP节点数量：%s" % (
                self.Coordinates[cornum].shape[0])
            xLabel = u"迭代次数"
            yLabel = u"最短路径长度"
            self.drawLengthIter(lengthNpIter, title, xLabel, yLabel, labelList)
            # 画时间参数设置图
            title = u"信息素计算方式-时间参数图-TSP节点数量：%s" % (
                self.Coordinates[cornum].shape[0])
            xLabel = u"信息素计算方式： 蚁量、蚁密"
            yLabel = u"平均时间"
            self.drawTimeIter(timeIter, title, xLabel, yLabel, range(nums))

    def testVolat(self):
        '''信息素挥发速度影响测试'''
        start = 0  # 信息素挥发速度开始
        step = 0.1  # 信息素挥发速度增加步长
        nums = 7  # 信息素挥发速度总测试个数
        print("-信息素挥发速度影响测试", file=f)
        for cornum in range(self.testCorNum):  # 对每个用例
            print("---第%2d 个用例: 坐标点数%d个" %
                  (cornum+1, self.Coordinates[cornum].shape[0]), file=f)
            timeIter = []  # 运行时间迭代列表
            lengthNpIter = []  # 最短路径长度迭代列表
            rho = start  # 最初信息素浓度
            labelList = []  # 用于画图例的标签
            labelList.append("%3.3s" % rho)
            for n in range(nums):  # 对于每个信息素挥发速度参数
                sumLengthNp = np.zeros(self.iterMax)  # 最短路径迭代记录

                sumTimeList = []  # 总时间记录
                sumLengthList = []  # 最短路径记录
                for t in range(self.testTimes):  # 每个参数下运行测试次数
                    acoTest = ACO(
                        coordinates=self.Coordinates[cornum], rho=rho, iterMax=self.iterMax)
                    tLengthNp, tTime = acoTest.getBest_LengthNp_Time()  # 获取最短路径长度迭代列表、运行时间
                    sumTimeList.append(tTime)
                    sumLengthList.append(tLengthNp[-1])
                    sumLengthNp = sumLengthNp + tLengthNp

                aveTime = np.mean(sumTimeList)  # 平均时间均值
                varTime = np.var(sumTimeList)  # 平均时间方差
                aveLength = np.mean(sumLengthList)  # 平均最短路径方差
                varLength = np.var(sumLengthList)  # 平均最短路径方差

                print("-----信息素挥发速度：%3.3f  时间平均值：%8.8f  时间方差：%8.8f  最短路径平均值：%8.8f  最短路径方差：%8.8f" %
                      (rho, aveTime, varTime, aveLength, varLength), file=f)

                timeIter.append(aveTime)
                lengthNpIter.append(sumLengthNp/self.testTimes)
                rho = rho + step  # 信息素挥发速度
                labelList.append("%3.3s" % rho)
            # 画最短路径迭代图
            title = u"信息素挥发速度-最短路径收敛图-TSP节点数量：%s" % (
                self.Coordinates[cornum].shape[0])
            xLabel = u"迭代次数"
            yLabel = u"最短路径长度"
            self.drawLengthIter(lengthNpIter, title, xLabel, yLabel, labelList)
            # 画时间参数设置图
            title = u"信息素挥发速度-时间参数图-TSP节点数量：%s" % (
                self.Coordinates[cornum].shape[0])
            xLabel = u"信息素挥发速度参数"
            yLabel = u"平均时间"
            self.drawTimeIter(timeIter, title, xLabel, yLabel, labelList[1:])

    def drawLengthIter(self, lengthNpIter, title, xLabel, yLabel, labelList):
        '''画出最短路径迭代收敛图'''
        plt.figure(title)
        handleList = []
        for i in range(len(lengthNpIter)):
            l, = plt.plot(lengthNpIter[i], label=labelList[i])
            handleList.append(l)
        plt.title(title)
        plt.xlabel(xLabel)
        plt.ylabel(yLabel)
        plt.legend(handles=handleList, labels=labelList)
        plt.savefig('./TSP_ACO_IMG/%s.jpg' % (title))
        # plt.show()
        plt.close()

    def drawTimeIter(self, timeIter, title, xLabel, yLabel, x):
        '''画出时间参数迭代图'''
        plt.figure(title)
        plt.plot(x, timeIter)
        plt.title(title)
        plt.xlabel(xLabel)
        plt.ylabel(yLabel)
        plt.savefig('./TSP_ACO_IMG/%s.jpg' % (title))
        # plt.show()
        plt.close()


if __name__ == '__main__':
    acomng = ACOManage()
    t_start = time.time()  # 开始计时
    timeList = []

    t_ts = time.time()
    acomng.testAntNum()  # 测试蚂蚁数量影响
    t_te = time.time()
    timeList.append((t_te-t_ts)/60)

    t_ts = time.time()
    acomng.testAlphaBeta()  # 测试信息素和启发函数比重影响
    t_te = time.time()
    timeList.append((t_te-t_ts)/60)

    t_ts = time.time()
    acomng.testMethod()  # 测试信息素计算方式影响
    t_te = time.time()
    timeList.append((t_te-t_ts)/60)

    t_ts = time.time()
    acomng.testVolat()  # 测试信息素挥发速度影响
    t_te = time.time()
    timeList.append((t_te-t_ts)/60)

    t_end = time.time()  # 结束计时
    print("各部分测试时间(分钟)：", timeList, file=f)
    print("测试总时间(分钟)：%s" % float(t_end-t_start)/60, file=f)

    f.close()
