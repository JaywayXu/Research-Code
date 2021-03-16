import numpy as np


class DE:
    def __init__(self, nP, MaxIt, lb, ub, nV, fobj, pc=0.5, F=0.5):
        self.MaxIt = MaxIt  # Maximum number of iterations
        self.nP = nP  # Number of Population
        self.nV = nV  # Number f Variables
        self.lb = lb  # lower boundary
        self.ub = ub  # upper boundary
        self.pc = pc  # 杂交概率
        self.F = F  # 缩放因子
        self.fobj = fobj

    def run(self):
        '''Run the Differential Evolution Algorithm'''
        convergence_curve = np.empty(self.MaxIt)  # 每代的最优
        best_fitness = -1  # 最优适应度
        best_x = None  # 最优个体表现型

        pop = self.initPop()  # 初始化种群
        for Current_iter in range(self.MaxIt):
            # Draw.drawPopScatter2D(pop, self.lb, self.ub, self.fobj)  # test

            pop_m = self.Mutation(pop)
            pop_c = self.Crossover(pop, pop_m)
            pop_s = self.Selection(pop, pop_c)

            fitness = self.getFitness(pop_s)
            arg = fitness.argmax()
            current_best_fitness = fitness[arg]
            current_best_x = pop_s[arg]
            if best_fitness < current_best_fitness:
                best_fitness = current_best_fitness
                best_x = current_best_x
            convergence_curve[Current_iter] = 1 / best_fitness

            pop = pop_s
            # print("Iter: ", Current_iter+1, "best cost: ", 1 / best_fitness)
        return (1 / best_fitness), best_x, convergence_curve

    def initPop(self):
        '''初始化种群'''
        # 每维变量都由在[lb, ub]范围内的实数表示
        # pop = self.lb + (self.ub-self.lb) * np.random.rand(self.nP, self.nV)
        pop = np.random.uniform(self.lb, self.ub, (self.nP, self.nV))
        return pop

    def Mutation(self, pop):
        '''差分变异，vi = xr1 + F * (xr2−xr3)'''
        random_idx = np.random.randint(0, self.nP, (self.nP, 3))
        # 选择父母
        r1, r2, r3 = random_idx[:, 0], random_idx[:, 1], random_idx[:, 2]
        # 差分变异
        pop_mut = pop[r1] + self.F * (pop[r2] - pop[r3])
        # 越界则回到界限内随机位置
        mask = np.random.uniform(self.lb, self.ub, (self.nP, self.nV))
        pop_mut = np.where(pop_mut < self.lb, mask, pop_mut)
        pop_mut = np.where(pop_mut > self.ub, mask, pop_mut)
        return pop_mut

    def Crossover(self, pop, pop_mut):
        '''杂交，if rand < prob_crossover, use V, else use X'''
        pop_cro = np.empty(pop.shape)
        mask = np.random.rand(self.nP, self.nV) < self.pc
        pop_cro = np.where(mask, pop_mut, pop)
        return pop_cro

    def Selection(self, pop, pop_cro):
        '''选择，锦标赛'''
        pop_fitness = self.getFitness(pop)
        cro_fitness = self.getFitness(pop_cro)
        pop_sel = np.where(
            (pop_fitness > cro_fitness).reshape(-1, 1), pop, pop_cro)
        return pop_sel

    def getFitness(self, pop):
        '''获取种群适应值'''
        fitness = np.empty((pop.shape[0]))
        for j in range(pop.shape[0]):
            # 原函数求最小值，所以这里适应值改为相反数 not
            fitness[j] = (1 / self.fobj(pop[j]))
        return fitness

if __name__ == '__main__':
    nP = 50
    MaxIt = 500

    import sys
    sys.path.append("..")
    import Draw
    from BenchmarkFunctions import BenchmarkFunctions
    bmf = BenchmarkFunctions(D=2)
    lb, ub, nV, fobj = bmf.get(13)

    de = DE(nP=nP, MaxIt=MaxIt, lb=lb, ub=ub, nV=nV, fobj=fobj)
    Best_Cost, Best_X, Convergence_curve = de.run()
    print("Best Cost: ", Best_Cost)
    Draw.drawPloterro([Convergence_curve], ['DE'], fobj.__doc__)
