from BenchmarkFunctions import BenchmarkFunctions
from Optimizer.GBO import GBO
from Optimizer.GA import GA
# from sko.DE import DE  # use scikit-opt
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class Manage:
    def __init__(self):
        self.nP = 50
        self.MaxIt = 200
        self.bmf = BenchmarkFunctions()
        self.testNum = 20

    def run_GBO(self, fname):
        print("GBO")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_Best_Cost = np.empty([self.testNum])
        np_Best_X = np.empty([self.testNum, nV])
        np_Convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            gbo = GBO(self.nP, self.MaxIt, lb, ub, nV, fobj)
            np_Best_Cost[i], np_Best_X[i], np_Convergence_curve[i] = gbo.run()
            print("%d test: " % (i + 1), np_Best_Cost[i])

        ave_Best_Cost = np_Best_Cost.mean()
        print("Average Cost:", ave_Best_Cost)

    def run_GA(self, fname):
        print("GA")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_Best_Cost = np.empty([self.testNum])
        np_Best_X = np.empty([self.testNum, nV])
        np_Convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            ga = GA(nP=self.nP, MaxIt=self.MaxIt,
                    lb=lb, ub=ub, nV=nV, fobj=fobj)
            np_Best_Cost[i], np_Best_X[i], np_Convergence_curve[i] = ga.run()
            print("%d test: " % (i + 1), np_Best_Cost[i])
            ga.Ploterro(np_Convergence_curve[i])
            input()

        ave_Best_Cost = np_Best_Cost.mean()
        print("Average Cost:", ave_Best_Cost)

    def run_DE(self, fname):
        print("DE")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_Best_Cost = np.empty([self.testNum])
        np_Best_X = np.empty([self.testNum, nV])

        for i in range(self.testNum):
            de = DE(
                func=fobj,
                n_dim=nV,
                size_pop=self.nP,
                max_iter=self.MaxIt,
                lb=lb,
                ub=ub,
            )
            np_Best_X[i], np_Best_Cost[i] = de.run()
            print("%d test: " % (i + 1), np_Best_Cost[i])

        ave_Best_Cost = np_Best_Cost.mean()
        print("Average Cost:", ave_Best_Cost)

    def drawFunction_2D(self, fname):
        lb, ub, nV, fobj = self.bmf.get(fname)
        lb = lb[0]
        ub = ub[0]

        figure = plt.figure()
        axes = Axes3D(figure)
        X = np.arange(lb, ub, 1)
        Y = np.arange(lb, ub, 1)

        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)

        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        axes.plot_surface(X, Y, Z, cmap='rainbow')
        print(fobj.__doc__)
        plt.title(fobj.__doc__)
        plt.show()


if __name__ == "__main__":
    mng = Manage()
    fname = 1
    mng.drawFunction_2D(fname)
    # mng.run_GBO(fname)
    # mng.run_GA(fname)
    # mng.run_DE(fname)
    # for i in range(1, 15):
    #     mng.drawFunction_2D(i)
