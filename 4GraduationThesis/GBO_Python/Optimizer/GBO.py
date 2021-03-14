import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class GBO:
    def __init__(self, nP, MaxIt, lb, ub, nV, fobj):
        self.MaxIt = MaxIt  # Maximum number of iterations
        self.nP = nP  # Number of Population
        self.nV = nV  # Number f Variables
        self.lb = lb  # lower boundary
        self.ub = ub  # upper boundary
        self.fobj = fobj
        self.pr = 0.5  # Probability Parameter

    def run(self):
        '''Run the Optimize Algorithm'''
        self.Cost = np.zeros([self.nP, 1])
        # Initialize the set of random solutions
        self.X = self.lb + (self.ub-self.lb) * np.random.rand(self.nP, self.nV)
        Convergence_curve = np.zeros([self.MaxIt])

        # Calculate the Value of Objective Function
        for i in range(self.nP):
            self.Cost[i, :] = self.fobj(self.X[i, :])
        Ind = self.Cost.argsort(axis=0)  # 按列排序获取索引

        # Determine the vale of Best Fitness
        Best_Cost = self.Cost[Ind[0, :]]
        Best_X = self.X[Ind[0, :], :]
        # Determine the vale of Worst Fitness
        Worst_Cost = self.Cost[Ind[-1, :]]
        Worst_X = self.X[Ind[-1, :], :]

        # Main Loop
        for it in range(self.MaxIt):
            # test
            self.drawPopPoint(self.X, self.lb, self.ub, self.fobj)

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
                Xm = (self.X[r1, :] + self.X[r2, :] + self.X[r3, :] +
                      self.X[r4, :]) / 4
                ro = alpha * (2 * np.random.rand() - 1)
                ro1 = alpha * (2 * np.random.rand() - 1)
                eps = 5e-3 * np.random.rand()  # Randomization Epsilon

                # Direction of Movement Eq.(18)
                DM = np.random.rand() * ro * (Best_X - self.X[r1, :])
                Flag = 1
                GSR = self.GradientSearchRule(ro1, Best_X, Worst_X,
                                              self.X[i, :], self.X[r1, :], DM,
                                              eps, Xm, Flag)
                DM = np.random.rand() * ro * (Best_X - self.X[r1, :])
                X1 = self.X[i, :] - GSR + DM  # Eq.(25)

                Flag = 2
                DM = np.random.rand() * ro * (self.X[r1, :] - self.X[r2, :])
                GSR = self.GradientSearchRule(ro1, Best_X, Worst_X,
                                              self.X[i, :], self.X[r1, :], DM,
                                              eps, Xm, Flag)
                DM = np.random.rand() * ro * (self.X[r1, :] - self.X[r2, :])
                X2 = Best_X - GSR + DM  # Eq.(26)

                Xnew = np.zeros([1, self.nV])
                for j in range(self.nV):
                    ro = alpha * (2 * np.random.rand() - 1)
                    X3 = self.X[i, j] - ro * (X2[0, j] - X1[0, j])
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
                    Xk = L2 * Xp[0, :] + (1 - L2) * self.X[k, :]  # Eq.(28.7)

                    if np.random.rand() < 0.5:
                        Xnew = Xnew + f1 * (
                            u1 * Best_X - u2 * Xk) + f2 * ro * (
                                u3 * (X2 - X1) + u2 *
                                (self.X[r1, :] - self.X[r2, :])) / 2
                    else:
                        Xnew = Best_X + f1 * (
                            u1 * Best_X - u2 * Xk) + f2 * ro * (
                                u3 * (X2 - X1) + u2 *
                                (self.X[r1, :] - self.X[r2, :])) / 2

                # Check if solutions go outside the search space
                # and bring them back
                Flag4ub = Xnew > self.ub
                Flag4lb = Xnew < self.lb
                Xnew = (Xnew * (~(Flag4ub+Flag4lb))) + self.ub * \
                    Flag4ub + self.lb * Flag4lb  # 越界的数据变为上/下边界
                Xnew_Cost = self.fobj(Xnew[0, :])
                # Update the Best Position
                if Xnew_Cost < self.Cost[i]:
                    self.X[i, :] = Xnew
                    self.Cost[i] = Xnew_Cost
                    if self.Cost[i] < Best_Cost:
                        Best_X = self.X[i, :]
                        Best_Cost = self.Cost[i]
                # Update the Worst Position
                if self.Cost[i] > Worst_Cost:
                    Worst_X = self.X[i, :]
                    Worst_Cost = self.Cost[i]

            # Show Iteration Information
            Convergence_curve[it] = Best_Cost
            # print('Iteration ', it + 1, ': Best Fitness = ',
            #       Convergence_curve[it])

        return Best_Cost, Best_X, Convergence_curve

    def GradientSearchRule(self, ro1, Best_X, Worst_X, X, Xr1, DM, eps, Xm,
                           Flag):
        '''Gradient Search Rule'''

        nV = X.shape[0]
        Delta = 2 * np.random.rand() * abs(Xm - X)  # Eq.(16.2)
        Step = ((Best_X - Xr1) + Delta) / 2  # Eq.(16.1)
        DelX = np.random.rand(1, nV) * (abs(Step))  # Eq.(16)

        # Gradient search rule  Eq.(15)
        GSR = np.random.randn() * ro1 * (2 * DelX * X) / (Best_X - Worst_X +
                                                          eps)
        if Flag == 1:
            Xs = X - GSR + DM  # Eq.(21)
        else:
            Xs = Best_X - GSR + DM
        yp = np.random.rand() * (0.5 * (Xs + X) + np.random.rand() * DelX
                                 )  # Eq.(22.6)
        yq = np.random.rand() * (0.5 * (Xs + X) - np.random.rand() * DelX
                                 )  # Eq.(22.7)
        GSR = np.random.randn() * ro1 * (2 * DelX * X) / (yp - yq + eps
                                                          )  # Eq.(23)
        return GSR

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
    MaxIt = 500

    import sys
    sys.path.append("..")
    from BenchmarkFunctions import BenchmarkFunctions
    bmf = BenchmarkFunctions()
    lb, ub, nV, fobj = bmf.get(10)

    gbo = GBO(nP, MaxIt, lb, ub, nV, fobj)
    Best_Cost, Best_X, Convergence_curve = gbo.run()
    print(Best_Cost, Best_X, Convergence_curve)
