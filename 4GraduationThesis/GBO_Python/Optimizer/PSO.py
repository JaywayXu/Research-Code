import numpy as np


class PSO:
    def __init__(self, nP, MaxIt, lb, ub, nV, fobj, wi=0.9, we=0.4, c1=0.5, c2=0.5, isDrawPop=False):
        self.isDrawPop = isDrawPop  # 是否画出每代种群分布
        self.MaxIt = MaxIt  # Maximum number of iterations
        self.nP = nP  # Number of Population
        self.nV = nV  # Number f Variables
        self.lb = lb  # lower boundary
        self.ub = ub  # upper boundary
        self.wini = wi  # 惯性因子(init)
        self.wend = we  # 惯性因子(end)
        self.k = 0  # 当前迭代次数
        self.c1 = c1  # 学习因子(个体)
        self.c2 = c2  # 学习因子(群体)
        self.fobj = fobj

        self.X = np.random.uniform(
            low=self.lb, high=self.ub, size=(self.nP, self.nV))  # 粒子位置
        v_high = (self.ub - self.lb) / 100
        self.V = np.random.uniform(
            low=-v_high, high=v_high, size=(self.nP, self.nV))  # 粒子速度
        self.Y = np.empty((self.nP))  # 粒子函数值
        self.cal_y()

        self.pbest_x = self.X.copy()  # 每个粒子最优位置
        self.pbest_y = np.full((self.nP), np.inf)  # 每个粒子最优函数值
        self.gbest_x = np.empty((self.nV))  # 种群最优位置
        self.gbest_y = np.inf  # 种群最优函数值
        self.update_gbest()
        self.gbest_y_hist = np.empty(self.MaxIt)  # 每代的最优函数值

    def run(self):
        '''Run the Particle Swarm Optimization Algorithm'''
        for Current_iter in range(self.MaxIt):
            if self.isDrawPop:  # test
                draw.drawPopScatter2D(self.X, self.lb, self.ub, self.fobj)

            self.k = Current_iter
            self.update_V()
            self.update_X()
            self.cal_y()
            self.update_pbest()
            self.update_gbest()
            self.gbest_y_hist[Current_iter] = self.gbest_y

            if self.isDrawPop:  # test
                print("Iter: ", Current_iter+1, "best cost: ", self.gbest_y)
        return self.gbest_y, self.gbest_x, self.gbest_y_hist

    def update_V(self):
        r1 = np.random.rand(self.nP, self.nV)
        r2 = np.random.rand(self.nP, self.nV)
        # 线性递减权值策略
        w = (self.wini-self.wend) * \
            (self.MaxIt - self.k) / self.MaxIt + self.wend
        self.V = w * self.V + self.c1 * r1 * \
            (self.pbest_x - self.X) + self.c2 * r2 * (self.gbest_x - self.X)

    def update_X(self):
        self.X = self.X + self.V
        # 越界则回到界限内随机位置
        mask = np.random.uniform(self.lb, self.ub, (self.nP, self.nV))
        self.X = np.where(self.X < self.lb, mask, self.X)
        self.X = np.where(self.X > self.ub, mask, self.X)
        # 越界则到最近边界
        # self.X = np.clip(self.X, self.lb, self.ub)

    def cal_y(self):
        '''calculate y for every x in X'''
        for j in range(self.X.shape[0]):
            self.Y[j] = self.fobj(self.X[j])

    def update_pbest(self):
        '''update personal best'''
        need_update = self.Y < self.pbest_y
        need_update_2 = need_update.reshape(self.nP, 1).repeat(self.nV, axis=1)
        self.pbest_x = np.where(need_update_2, self.X, self.pbest_x)
        self.pbest_y = np.where(need_update, self.Y, self.pbest_y)

    def update_gbest(self):
        '''update global best'''
        idx_min = self.pbest_y.argmin()
        if self.gbest_y > self.pbest_y[idx_min]:
            self.gbest_x = self.X[idx_min, :].copy()
            self.gbest_y = self.pbest_y[idx_min]


if __name__ == '__main__':
    nP = 50
    MaxIt = 500

    import sys
    sys.path.append("..")
    from Draw import Draw
    draw = Draw(isShow=True, isSavefig=False, isClose=False)
    from BenchmarkFunctions import BenchmarkFunctions
    bmf = BenchmarkFunctions(D=30)
    lb, ub, nV, fobj = bmf.get(13)

    pso = PSO(nP=nP, MaxIt=MaxIt, lb=lb, ub=ub,
              nV=nV, fobj=fobj, isDrawPop=True)
    Best_Cost, Best_X, Convergence_curve = pso.run()
    print("Best Cost: ", Best_Cost)
    draw.drawPloterro([Convergence_curve], ['PSO'], fobj.__doc__)
