import numpy as np
import copy
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class GA:
    def __init__(self, nP, MaxIt, lb, ub, nV, fobj, lenchrom=10, pc=0.8, pm=0.02):
        self.MaxIt = MaxIt  # Maximum number of iterations
        self.nP = nP  # Number of Population
        self.nV = nV  # Number f Variables
        self.lb = lb  # lower boundary
        self.ub = ub  # upper boundary
        self.lenchrom = lenchrom  # 染色体长度
        self.pc = pc  # 交叉概率
        self.pm = pm  # 变异概率
        self.fobj = fobj

    def run(self):
        '''Run the Genetic Algorithm'''
        pop = self.InitPop()  # 种群
        fitness = np.empty(self.nP)  # 适应度
        errolist = np.empty(self.MaxIt)  # 每代的最优

        best_fitness = -1
        best_pop = np.zeros(self.nV)
        # main loop
        for Current_iter in range(self.MaxIt):
            # test
            pop_v = self.Convert(pop)
            self.drawPopPoint(pop_v, self.lb, self.ub, self.fobj)

            # print("Iter = " + str(Current_iter))
            pop1 = self.Crossover(pop)
            # test
            pop_v = self.Convert(pop1)
            self.drawPopPoint(pop_v, self.lb, self.ub, self.fobj)

            pop2 = self.Mutation(pop1)
            # test
            pop_v = self.Convert(pop2)
            self.drawPopPoint(pop_v, self.lb, self.ub, self.fobj)

            pop_v = self.Convert(pop2)

            fitness_list = []
            for j in range(pop_v.shape[0]):
                # 原函数求最小值，所以这里适应值改为相反数 not
                fitness_list.append(1 / self.fobj(pop_v[j, :]))
            fitness = np.array(fitness_list)
            pop_v = self.Convert(pop2)

            # 自然选择 轮盘赌
            newpop, newfitness = self.Roulette(pop2, fitness)
            best_arg = newfitness.argmax()
            if best_fitness < (newfitness[best_arg]):
                best_fitness = (newfitness[best_arg])
                best_pop_gene = np.empty((1, self.nV, self.lenchrom))
                best_pop_gene[0] = newpop[best_arg]
                best_pop = self.Convert(best_pop_gene)[0]
            errolist[Current_iter] = 1 / best_fitness
            pop = copy.deepcopy(newpop)

        return 1 / best_fitness, best_pop, errolist

    def InitPop(self):
        '''初始化种群：返回一个三维数组，第一维是种子，第二维是变量维度，第三维是编码基因'''
        # 每个基因都由lenchrom个[0, 1]范围的浮点数表示
        pop = np.random.rand(self.nP, self.nV, self.lenchrom)
        # pop = np.random.randint(0, 2, (self.nP, self.nV, self.lenchrom))
        return pop

    def Crossover(self, pop):
        '''交叉繁殖：针对每一个种子，随机选取另一个种子与之交叉。
        随机取种子基因上的两个位置点，然后互换两点之间的部分'''
        newpop = []
        for i in range(pop.shape[0]):
            if np.random.rand() < self.pc:
                # 选择另一个种子
                j = i
                while j == i:
                    j = np.random.randint(0, pop.shape[0] - 1)

                # 每个基因分别选择交叉点杂交
                newpop1, newpop2 = [], []
                # 选择交叉点
                cpoint1 = np.random.randint(1, self.lenchrom - 1)
                cpoint2 = cpoint1
                while cpoint2 == cpoint1:
                    cpoint2 = np.random.randint(1, self.lenchrom - 1)
                cpoint1, cpoint2 = min(cpoint1, cpoint2), max(cpoint1, cpoint2)
                for k in range(self.nV):
                    temp1, temp2 = [], []
                    temp1.extend(pop[i, k, 0:cpoint1])
                    temp1.extend(pop[j, k, cpoint1:cpoint2])
                    temp1.extend(pop[i, k, cpoint2:])

                    temp2.extend(pop[j, k, 0:cpoint1])
                    temp2.extend(pop[i, k, cpoint1:cpoint2])
                    temp2.extend(pop[j, k, cpoint2:])
                    newpop1.append(temp1)
                    newpop2.append(temp2)
                newpop.extend([newpop1, newpop2])
        newpop = np.array(newpop)
        return newpop

    def Mutation(self, pop):
        '''变异：针对每一个种子的每一个维度，进行概率变异，变异基因为一位'''
        newpop = copy.deepcopy(pop)
        for i in range(pop.shape[0]):
            for j in range(self.nV):
                if np.random.rand() < self.pm:
                    mpoint = np.random.randint(0, self.lenchrom - 1)
                    newpop[i, j, mpoint] = np.random.rand()
                    # newpop[i, j, mpoint] = 1 - newpop[i, j, mpoint]
        return newpop

    def Convert(self, pop):
        '''将基因转化为解'''
        pop_v = np.zeros((pop.shape[0], self.nV), dtype=float)
        for i in range(pop.shape[0]):
            for j in range(self.nV):
                for k in range(self.lenchrom):
                    pop_v[i, j] += pop[i, j, k] * pow(2, k)
                # 映射到范围内
                pop_v[i, j] = pop_v[i, j] * (self.ub[j] - self.lb[j]) / \
                    (pow(2, self.lenchrom) - 1) + self.lb[j]
        return pop_v

    def Roulette(self, pop, fitness):
        '''轮盘赌模型选择适应值较高的种子'''
        # 生成适应值累加序列
        fitness_sum = fitness.sum()
        accumulation = [None for col in range(fitness.shape[0])]
        accumulation[0] = fitness[0] / fitness_sum
        for i in range(1, fitness.shape[0]):
            accumulation[i] = accumulation[i - 1] + \
                fitness[i] / fitness_sum

        # 轮盘赌
        newpop, newfitness = [], []
        for j in range(self.nP):
            # for j in range(pop.shape[0]):
            p = np.random.randn()
            for k in range(len(accumulation)):
                if accumulation[k] >= p:
                    newpop.append(pop[k, :])
                    newfitness.append(fitness[k])
                    break
        newpop = np.array(newpop)
        newfitness = np.array(newfitness)

        # sorted_pop = np.empty((self.nP, self.nV, self.lenchrom))
        # sorted_fitness = np.empty(self.nP)
        # sorted_arg = np.argsort(-newfitness)
        # for i in range(self.nP):   # 恢复初始种群数量
        #     sorted_pop[i, :] = newpop[sorted_arg[i], :]
        #     sorted_fitness[i] = newfitness[sorted_arg[i]]
        # return sorted_pop, sorted_fitness
        return newpop, newfitness

    def drawPopPoint(self, pop_v, lb, ub, fobj):
        # fobj
        figure = plt.figure()
        axes = Axes3D(figure)
        X = np.arange(lb[0], ub[0], 0.2)
        Y = np.arange(lb[1], ub[1], 0.2)
        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)
        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        axes.plot_surface(X, Y, Z, cmap='rainbow', alpha=.3)

        # pop
        z = np.empty(pop_v.shape[0])
        for i in range(pop_v.shape[0]):
            z[i] = fobj(pop_v[i, :])
        pop_t = pop_v.T
        x = pop_t[0, :]
        y = pop_t[1, :]
        z = z.T
        axes.scatter(x, y, z, c='r', marker='.')
        plt.show()


if __name__ == '__main__':
    nP = 50
    MaxIt = 200

    import sys
    sys.path.append("..")
    from BenchmarkFunctions import BenchmarkFunctions
    bmf = BenchmarkFunctions()
    lb, ub, nV, fobj = bmf.get(1)

    ga = GA(nP=nP, MaxIt=MaxIt, lb=lb, ub=ub, nV=nV, fobj=fobj)
    Best_Cost, Best_X, Convergence_curve = ga.run()
    print(Best_Cost, Best_X, Convergence_curve)
    ga.Ploterro(Convergence_curve)
    # pop = ga.InitPop()
    # pop1 = ga.Convert(pop)
    # fitness = np.empty(nP)
    # for j in range(nP):
    #     fitness[j] = 1 / f1(pop1[j, :])
    # pop0, fitness0 = ga.Roulette(pop, fitness)
    # pop1 = ga.Crossover(pop)
    # print(pop1)
