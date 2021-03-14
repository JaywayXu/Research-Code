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
        convergence_curve = np.empty(self.MaxIt)  # 每代的最优
        best_fitness = -1  # 最优适应度
        best_x = np.zeros(self.nV)  # 最优个体表现型

        pop = self.initPop()  # 初始化种群
        for Current_iter in range(self.MaxIt):
            # self.drawPopPoint3D(self.g2p(pop), self.lb, self.ub, self.fobj)  # test

            pop_c = self.Crossover(pop)
            # self.drawPopPoint3D(self.g2p(pop_c), self.lb, self.ub, self.fobj)  # test

            pop_m = self.Mutation(pop_c)
            # self.drawPopPoint3D(self.g2p(pop_m), self.lb, self.ub, self.fobj)  # test

            pop_s = self.Selection(pop_m)
            pop = pop_s

            best_p = pop_s[0].reshape(1, self.nV, self.lenchrom)
            current_best_fitness = self.getFitness(best_p)[0]
            current_best_x = self.g2p(best_p)[0]
            if best_fitness < current_best_fitness:
                best_fitness = current_best_fitness
                best_x = current_best_x
            convergence_curve[Current_iter] = 1 / best_fitness

            # print("Iter: ", Current_iter+1, "best cost: ", 1 / best_fitness)

        return (1 / best_fitness), best_x, convergence_curve

    def initPop(self):
        '''初始化种群：返回一个三维数组，第一维是种子，第二维是变量维度，第三维是编码基因'''
        # 每个基因都由lenchrom个[0, 1]范围的浮点数表示
        pop = np.random.rand(self.nP, self.nV, self.lenchrom)
        # pop = np.random.randint(0, 2, (self.nP, self.nV, self.lenchrom))
        return pop

    def Crossover(self, pop):
        '''交叉繁殖'''
        # 使用轮盘赌算法选择nP个个体，随机选取另一个个体与之两点交叉，生成(2*nP)个子代
        # 如果没有进行交叉则将原基因型留到子代
        child_pop = []
        arg_pop = self.argRoulette(pop, self.nP)
        for i in arg_pop:
            i = int(i)
            # 选择另一个个体
            j = i
            while j == i:
                j = np.random.randint(0, pop.shape[0] - 1)

            child1 = np.empty((self.nV, self.lenchrom))
            child2 = np.empty((self.nV, self.lenchrom))
            for k in range(self.nV):  # 对每个变量
                if np.random.rand() > self.pc:  # 没有交叉
                    child1[k] = pop[i, k]
                    child2[k] = pop[j, k]
                else:  # 交叉
                    # 选择交叉点
                    point1 = np.random.randint(1, self.lenchrom - 1)
                    point2 = point1
                    while point2 == point1:
                        point2 = np.random.randint(1, self.lenchrom - 1)
                    point1, point2 = min(
                        point1, point2), max(point1, point2)

                    # 交叉
                    temp1, temp2 = [], []
                    temp1.extend(pop[i, k, 0:point1])
                    temp1.extend(pop[j, k, point1:point2])
                    temp1.extend(pop[i, k, point2:])
                    temp2.extend(pop[j, k, 0:point1])
                    temp2.extend(pop[i, k, point1:point2])
                    temp2.extend(pop[j, k, point2:])
                    child1[k] = np.array(temp1)
                    child2[k] = np.array(temp2)
            child_pop.append(child1)
            child_pop.append(child2)
        child_pop = np.array(child_pop)
        return child_pop

    def Mutation(self, pop):
        '''变异：针对每一个种子的每一个维度，进行概率变异，变异基因为一位'''
        new_pop = copy.deepcopy(pop)
        for i in range(pop.shape[0]):
            for j in range(self.nV):
                if np.random.rand() < self.pm:
                    mpoint = np.random.randint(0, self.lenchrom - 1)
                    new_pop[i, j, mpoint] = np.random.rand()
                    # new_pop[i, j, mpoint] = 1 - new_pop[i, j, mpoint]
        return new_pop

    def Selection(self, pop):
        # 根据种群适应度排序
        fitness = self.getFitness(pop)
        arg = np.argsort(-fitness)  # 从大到小

        # 选择nP个适应度高的个体
        new_pop = np.empty((self.nP, self.nV, self.lenchrom))
        for i in range(self.nP):
            new_pop[i] = pop[arg[i]]
        return new_pop

    def argRoulette(self, pop, num):
        '''轮盘赌选择num个适应值较高的个体并返回下标'''
        # 生成适应值累加序列
        fitness = self.getFitness(pop)
        fitness_sum = fitness.sum()
        accumulation = [None for col in range(fitness.shape[0])]
        accumulation[0] = fitness[0] / fitness_sum
        for i in range(1, fitness.shape[0]):
            accumulation[i] = accumulation[i - 1] + \
                fitness[i] / fitness_sum

        # 轮盘赌选择
        arg_pop = np.empty((num))
        for j in range(num):
            p = np.random.rand()
            for k in range(len(accumulation)):
                if accumulation[k] >= p:
                    arg_pop[j] = k
                    break
        return arg_pop

    def g2p(self, pop):
        '''基因型转换表现型'''
        pop_x = np.zeros((pop.shape[0], self.nV), dtype=float)
        for i in range(pop.shape[0]):
            for j in range(self.nV):
                for k in range(self.lenchrom):
                    pop_x[i, j] += pop[i, j, k] * pow(2, k)
                # 映射到范围内
                pop_x[i, j] = pop_x[i, j] * (self.ub[j] - self.lb[j]) / \
                    (pow(2, self.lenchrom) - 1) + self.lb[j]
        return pop_x

    def getFitness(self, pop):
        '''获取种群适应值'''
        pop_x = self.g2p(pop)
        fitness = np.empty((pop.shape[0]))
        for j in range(pop.shape[0]):
            # 原函数求最小值，所以这里适应值改为相反数 not
            fitness[j] = (1 / self.fobj(pop_x[j]))
        return fitness

    def drawPopPoint3D(self, pop_x, lb, ub, fobj):
        # fobj
        figure = plt.figure()
        axes = Axes3D(figure)
        X = np.arange(lb[0], ub[0], 0.5)
        Y = np.arange(lb[1], ub[1], 0.5)
        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)
        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        axes.plot_surface(X, Y, Z, cmap='rainbow', alpha=.3)

        # pop
        z = np.empty(pop_x.shape[0])
        for i in range(pop_x.shape[0]):
            z[i] = fobj(pop_x[i])
        z = z.T
        pop_t = pop_x.T
        x, y = pop_t[0], pop_t[1]
        axes.scatter(x, y, z, c='r', marker='.')
        plt.show()


if __name__ == '__main__':
    nP = 50
    MaxIt = 500

    import sys
    sys.path.append("..")
    from BenchmarkFunctions import BenchmarkFunctions
    bmf = BenchmarkFunctions()
    lb, ub, nV, fobj = bmf.get(1)

    ga = GA(nP=nP, MaxIt=MaxIt, lb=lb, ub=ub, nV=nV, fobj=fobj)
    Best_Cost, Best_X, Convergence_curve = ga.run()
    print("Best Cost: ", Best_Cost)
