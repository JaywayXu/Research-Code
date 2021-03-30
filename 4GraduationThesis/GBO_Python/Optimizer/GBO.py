import numpy as np


class GBO:
    def __init__(self, nP, MaxIt, lb, ub, nV, fobj, pr=0.5, isDrawPop=False):
        self.isDrawPop = isDrawPop  # 是否画出每代种群分布
        self.MaxIt = MaxIt  # Maximum number of iterations
        self.nP = nP  # Number of Population
        self.nV = nV  # Number f Variables
        self.lb = lb  # lower boundary
        self.ub = ub  # upper boundary
        self.fobj = fobj
        self.pr = pr  # Probability Parameter

    def run(self):
        '''Run the Optimize Algorithm'''
        cost = np.zeros([self.nP, 1])
        # Initialize the set of random solutions
        X = self.lb + (self.ub-self.lb) * np.random.rand(self.nP, self.nV)
        convergence_curve = np.zeros([self.MaxIt])

        # Calculate the Value of Objective Function
        for i in range(self.nP):
            cost[i, :] = self.fobj(X[i, :])

        # Determine the vale of Best Fitness
        index_min = cost.argmin(axis=0)
        best_cost = cost[index_min]
        best_x = X[index_min, :]
        # Determine the vale of Worst Fitness
        index_max = cost.argmax(axis=0)
        worst_cost = cost[index_max]
        worst_x = X[index_max, :]

        # Main Loop
        for it in range(self.MaxIt):
            if self.isDrawPop:  # test
                draw.drawPopScatter2D(X, self.lb, self.ub, self.fobj)

            # Eq.(14.2)
            beta = 0.2 + (1.2 - 0.2) * pow((1 - pow((it / self.MaxIt), 3)), 2)
            # Eq.(14.1)
            alpha = abs(beta * np.sin(
                (3 * np.pi / 2 + np.sin(3 * np.pi / 2 * beta))))

            for i in range(self.nP):
                # Four positions randomly selected from population
                A1 = np.fix(np.random.rand(1, self.nP) * self.nP)
                r1, r2, r3, r4 = A1[:, 0:4][0, :].astype(np.int16)

                # Average of Four positions randomly selected from population
                Xm = (X[r1, :] + X[r2, :] + X[r3, :] +
                      X[r4, :]) / 4
                ro = alpha * (2 * np.random.rand() - 1)
                ro1 = alpha * (2 * np.random.rand() - 1)
                eps = 5e-3 * np.random.rand()  # Randomization Epsilon

                # Direction of Movement Eq.(18)
                DM = np.random.rand() * ro * (best_x - X[r1, :])
                Flag = 1
                GSR = self.GradientSearchRule(ro1, best_x, worst_x,
                                              X[i, :], X[r1, :], DM,
                                              eps, Xm, Flag)
                DM = np.random.rand() * ro * (best_x - X[r1, :])
                X1 = X[i, :] - GSR + DM  # Eq.(25)

                Flag = 2
                DM = np.random.rand() * ro * (X[r1, :] - X[r2, :])
                GSR = self.GradientSearchRule(ro1, best_x, worst_x,
                                              X[i, :], X[r1, :], DM,
                                              eps, Xm, Flag)
                DM = np.random.rand() * ro * (X[r1, :] - X[r2, :])
                X2 = best_x - GSR + DM  # Eq.(26)

                Xnew = np.zeros([1, self.nV])
                for j in range(self.nV):
                    ro = alpha * (2 * np.random.rand() - 1)
                    X3 = X[i, j] - ro * (X2[0, j] - X1[0, j])
                    ra, rb = np.random.rand(), np.random.rand()
                    Xnew[0,
                         j] = ra * (rb * X1[0, j] +
                                    (1 - rb) * X2[0, j]) + (1 -
                                                            ra) * X3  # Eq.(27)

                # Local escaping operator(LEO) # Eq.(28)
                if np.random.rand() < self.pr:
                    k = np.fix(np.random.rand() * self.nP).astype(np.int16)
                    f1 = -1 + (1 - (-1)) * np.random.rand()
                    f2 = -1 + (1 - (-1)) * np.random.rand()
                    ro = alpha * (2 * np.random.rand() - 1)
                    Xp = self.lb + (self.ub-self.lb) * \
                        np.random.rand(1, self.nV)  # Eq.(28.8)

                    L1 = np.random.rand() < 0.5
                    u1 = L1 * 2 * np.random.rand() + (1 - L1) * 1
                    u2 = L1 * np.random.rand() + (1 - L1) * 1
                    u3 = L1 * np.random.rand() + (1 - L1) * 1
                    L2 = np.random.rand() < 0.5
                    Xk = L2 * Xp[0, :] + (1 - L2) * X[k, :]  # Eq.(28.7)

                    if np.random.rand() < 0.5:
                        Xnew = Xnew + f1 * (
                            u1 * best_x - u2 * Xk) + f2 * ro * (
                                u3 * (X2 - X1) + u2 *
                                (X[r1, :] - X[r2, :])) / 2
                    else:
                        Xnew = best_x + f1 * (
                            u1 * best_x - u2 * Xk) + f2 * ro * (
                                u3 * (X2 - X1) + u2 *
                                (X[r1, :] - X[r2, :])) / 2

                # Check if solutions go outside the search space
                # and bring them back
                Flag4ub = Xnew > self.ub
                Flag4lb = Xnew < self.lb
                Xnew = (Xnew * (~(Flag4ub+Flag4lb))) + self.ub * \
                    Flag4ub + self.lb * Flag4lb  # 越界的数据变为上/下边界
                Xnew_Cost = self.fobj(Xnew[0, :])
                # Update the Best Position
                if Xnew_Cost < cost[i]:
                    X[i, :] = Xnew
                    cost[i] = Xnew_Cost
                    if cost[i] < best_cost:
                        best_x = X[i, :]
                        best_cost = cost[i]
                # Update the Worst Position
                if cost[i] > worst_cost:
                    worst_x = X[i, :]
                    worst_cost = cost[i]

            # Show Iteration Information
            convergence_curve[it] = best_cost
            if self.isDrawPop:  # test
                print("Iter: ", it+1, "best cost: ", best_cost[0])

        return best_cost, best_x, convergence_curve

    def GradientSearchRule(self, ro1, best_x, worst_x, X, Xr1, DM, eps, Xm,
                           Flag):
        '''Gradient Search Rule'''

        nV = X.shape[0]
        Delta = 2 * np.random.rand() * abs(Xm - X)  # Eq.(16.2)
        Step = ((best_x - Xr1) + Delta) / 2  # Eq.(16.1)
        DelX = np.random.rand(1, nV) * (abs(Step))  # Eq.(16)

        # Gradient search rule  Eq.(15)
        GSR = np.random.randn() * ro1 * (2 * DelX * X) / (best_x - worst_x +
                                                          eps)
        if Flag == 1:
            Xs = X - GSR + DM  # Eq.(21)
        else:
            Xs = best_x - GSR + DM
        yp = np.random.rand() * (0.5 * (Xs + X) + np.random.rand() * DelX
                                 )  # Eq.(22.6)
        yq = np.random.rand() * (0.5 * (Xs + X) - np.random.rand() * DelX
                                 )  # Eq.(22.7)
        GSR = np.random.randn() * ro1 * (2 * DelX * X) / (yp - yq + eps
                                                          )  # Eq.(23)
        return GSR


if __name__ == '__main__':
    nP = 50
    MaxIt = 500

    import sys
    sys.path.append("..")
    from Draw import Draw
    draw = Draw(isShow=True, isClose=True)
    from BenchmarkFunctions import BenchmarkFunctions
    bmf = BenchmarkFunctions(D=30)

    for i in range(1, bmf.size+1):
        lb, ub, nV, fobj = bmf.get(i)
        gbo = GBO(nP, MaxIt, lb, ub, nV, fobj, isDrawPop=False)
        best_cost, best_x, convergence_curve = gbo.run()

        draw.drawPloterro([convergence_curve], ['GBO'],
                          fobj.__doc__, isDrawSub=False)
