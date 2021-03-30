import numpy as np
import pandas as pd
from BenchmarkFunctions import BenchmarkFunctions
from Optimizer.GBO import GBO
from Optimizer.GA import GA
from Optimizer.DE import DE
from Optimizer.PSO import PSO
from Draw import Draw


class Manage:
    def __init__(self, nP, nV, MaxIt, testNum):
        self.nP = nP
        self.nV = nV
        self.MaxIt = MaxIt
        self.testNum = testNum
        self.bmf = BenchmarkFunctions(D=self.nV)
        self.every_fun_list = []
        self.name_list = ['GBO', 'GA', 'DE', 'PSO']
        self.best_cost_name = "BestCost_%dD_%dT" % (
            self.nV, self.testNum)
        self.ave_cost_name = "AverageCost_%dD_%dT" % (
            self.nV, self.testNum)
        self.var_cost_name = "VarianceCost_%dD_%dT" % (
            self.nV, self.testNum)
        self.ave_cc_name = "ConvergenceCurve_%dD_%dT" % (
            self.nV, self.testNum)

    def initData(self, fname):
        '''初始化数据'''
        self.np_best_cost = np.empty([self.testNum])
        self.np_best_x = np.empty([self.testNum, self.nV])
        self.np_cc = np.empty([self.testNum, self.MaxIt])
        self.lb, self.ub, nV, self.fobj = self.bmf.get(fname)

    def initResult(self):
        '''初始化最终结果，第一维是每个函数，第二维是每个算法'''
        self.best_cost_list = []
        self.ave_cost_list = []
        self.var_cost_list = []
        self.ave_cc_list = []
        self.best_cost_np = None
        self.ave_cost_np = None
        self.var_cost_np = None
        self.ave_cc_np = None

    def getRun(self):
        '''返回当前数据的最优解，平均解，方差，平均收敛曲线'''
        best_cost = self.np_best_cost.min()
        ave_cost = self.np_best_cost.mean()
        var_cost = self.np_best_cost.var()
        ave_cc = np.empty((self.MaxIt))
        for i in range(self.MaxIt):
            ave_cc[i] = self.np_cc[:, i].mean()
        return best_cost, ave_cost, var_cost, ave_cc

    def runGBO(self, fname):
        '''测试GBO，返回最优解，平均解，方差，平均收敛曲线'''
        print("GBO")
        self.initData(fname)
        for i in range(self.testNum):
            gbo = GBO(self.nP, self.MaxIt, self.lb,
                      self.ub, self.nV, self.fobj)
            self.np_best_cost[i], self.np_best_x[i], self.np_cc[i] = gbo.run()
            print("%d test: " % (i + 1), self.np_best_cost[i])
        return self.getRun()

    def runGA(self, fname):
        '''测试GA，返回最优解，平均解，方差，平均收敛曲线'''
        print("GA")
        self.initData(fname)
        for i in range(self.testNum):
            ga = GA(self.nP, self.MaxIt, self.lb,
                    self.ub, self.nV, self.fobj)
            self.np_best_cost[i], self.np_best_x[i], self.np_cc[i] = ga.run()
            print("%d test: " % (i + 1), self.np_best_cost[i])
        return self.getRun()

    def runDE(self, fname):
        '''测试DE，返回最优解，平均解，方差，平均收敛曲线'''
        print("DE")
        self.initData(fname)
        for i in range(self.testNum):
            de = DE(self.nP, self.MaxIt, self.lb,
                    self.ub, self.nV, self.fobj)
            self.np_best_cost[i], self.np_best_x[i], self.np_cc[i] = de.run()
            print("%d test: " % (i + 1), self.np_best_cost[i])
        return self.getRun()

    def runPSO(self, fname):
        '''测试PSO，返回最优解，平均解，方差，平均收敛曲线'''
        print("PSO")
        self.initData(fname)
        for i in range(self.testNum):
            pso = PSO(self.nP, self.MaxIt, self.lb,
                      self.ub, self.nV, self.fobj)
            self.np_best_cost[i], self.np_best_x[i], self.np_cc[i] = pso.run()
            print("%d test: " % (i + 1), self.np_best_cost[i])
        return self.getRun()

    def savePloterro(self):
        '''保存迭代收敛图'''
        for fname in range(1, self.bmf.size+1):
            _, _, _, fobj = self.bmf.get(fname)
            cc_np = self.ave_cc_np[fname-1]
            title = "%dD_%dT_" % (self.nV, self.testNum) + fobj.__doc__
            name = "./PloterroFigure/Ploterro_%dD_%dT_F%d.png" % (
                self.nV, self.testNum, fname)
            draw = Draw(isShow=False)
            isDrawSub = True
            if fname in [7, 11]:  # 不绘制局部放大图的函数
                isDrawSub = False
            draw.drawPloterro(cc_np, self.name_list,
                              title, True, name, isDrawSub)

    def saveExcel(self):
        '''保存到excel文件'''
        best_cost_data = pd.DataFrame(self.best_cost_np.T)
        ave_cost_data = pd.DataFrame(self.ave_cost_np.T)
        var_cost_data = pd.DataFrame(self.var_cost_np.T)
        best_cost_writer = pd.ExcelWriter(
            "./Excel/" + self.best_cost_name + ".xlsx")  # 写入Excel文件
        ave_cost_writer = pd.ExcelWriter(
            "./Excel/" + self.ave_cost_name + ".xlsx")  # 写入Excel文件
        var_cost_writer = pd.ExcelWriter(
            "./Excel/" + self.var_cost_name + ".xlsx")  # 写入Excel文件
        # 'page1'是写入excel的sheet名
        best_cost_data.to_excel(best_cost_writer, 'page1', float_format='%.3f')
        ave_cost_data.to_excel(ave_cost_writer, 'page1', float_format='%.3f')
        var_cost_data.to_excel(var_cost_writer, 'page1', float_format='%.3f')
        best_cost_writer.save()
        ave_cost_writer.save()
        var_cost_writer.save()
        best_cost_writer.close()
        ave_cost_writer.close()
        var_cost_writer.close()

    def saveData(self):
        '''保存numpy数组'''
        np.save("./Data/" + self.best_cost_name, self.best_cost_np)
        np.save("./Data/" + self.ave_cost_name, self.ave_cost_np)
        np.save("./Data/" + self.var_cost_name, self.var_cost_np)
        np.save("./Data/" + self.ave_cc_name, self.ave_cc_np)

    def loadData(self):
        '''读取numpy数组并保存Ploterro'''
        self.initResult()
        self.best_cost_np = np.load("./Data/" + self.best_cost_name + ".npy")
        self.ave_cost_np = np.load("./Data/" + self.ave_cost_name + ".npy")
        self.var_cost_np = np.load("./Data/" + self.var_cost_name + ".npy")
        self.ave_cc_np = np.load("./Data/" + self.ave_cc_name + ".npy")
        self.savePloterro()
        self.saveExcel()

    def run(self):
        '''运行并保存Data、Ploterro'''
        self.initResult()
        for fname in range(1, self.bmf.size+1):
            self.initData(fname)
            print("F%d" % (fname))
            cost_gbo, ave_gbo, var_gbo, cc_gbo = self.runGBO(fname)
            cost_ga, ave_ga, var_ga, cc_ga = self.runGA(fname)
            cost_de, ave_de, var_de, cc_de = self.runDE(fname)
            cost_pso, ave_pso, var_pso, cc_pso = self.runPSO(fname)

            self.best_cost_list.append([cost_gbo, cost_ga, cost_de, cost_pso])
            self.ave_cost_list.append([ave_gbo, ave_ga, ave_de, ave_pso])
            self.var_cost_list.append([var_gbo, var_ga, var_de, var_pso])
            self.ave_cc_list.append([cc_gbo, cc_ga, cc_de, cc_pso])
            self.best_cost_np = np.array(self.best_cost_list)
            self.ave_cost_np = np.array(self.ave_cost_list)
            self.var_cost_np = np.array(self.var_cost_list)
            self.ave_cc_np = np.array(self.ave_cc_list)
        self.saveData()
        # self.savePloterro()
        # self.saveExcel()


if __name__ == "__main__":
    nP = 50
    nV = 30
    MaxIt = 400
    testNum = 30

    mng = Manage(nP, nV, MaxIt, testNum)
    # mng.run()
    mng.loadData()
