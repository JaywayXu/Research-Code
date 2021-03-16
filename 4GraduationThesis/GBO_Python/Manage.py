import numpy as np
from BenchmarkFunctions import BenchmarkFunctions
from Optimizer.GBO import GBO
from Optimizer.GA import GA
from Optimizer.DE import DE
import Draw


class Manage:
    def __init__(self, nP=50, nV=30, MaxIt=500, testNum=30):
        self.nP = nP
        self.MaxIt = MaxIt
        self.testNum = testNum
        self.bmf = BenchmarkFunctions(D=nV)

    def runGBO(self, fname):
        print("GBO")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_best_cost = np.empty([self.testNum])
        np_best_x = np.empty([self.testNum, nV])
        np_convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            gbo = GBO(self.nP, self.MaxIt, lb, ub, nV, fobj)
            np_best_cost[i], np_best_x[i], np_convergence_curve[i] = gbo.run()
            print("%d test: " % (i + 1), np_best_cost[i])

        best_cost = np_best_cost.min()
        ave_cost = np_best_cost.mean()
        var_cost = np_best_cost.var()
        ave_convergence_curve = np.empty((self.MaxIt))
        for i in range(self.MaxIt):
            ave_convergence_curve[i] = np_convergence_curve[:, i].mean()
        return best_cost, ave_cost, var_cost, ave_convergence_curve

    def runGA(self, fname):
        print("GA")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_best_cost = np.empty([self.testNum])
        np_best_x = np.empty([self.testNum, nV])
        np_convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            ga = GA(nP=self.nP, MaxIt=self.MaxIt,
                    lb=lb, ub=ub, nV=nV, fobj=fobj)
            np_best_cost[i], np_best_x[i], np_convergence_curve[i] = ga.run()
            print("%d test: " % (i + 1), np_best_cost[i])

        best_cost = np_best_cost.min()
        ave_cost = np_best_cost.mean()
        var_cost = np_best_cost.var()
        ave_convergence_curve = np.empty((self.MaxIt))
        for i in range(self.MaxIt):
            ave_convergence_curve[i] = np_convergence_curve[:, i].mean()
        return best_cost, ave_cost, var_cost, ave_convergence_curve

    def runDE(self, fname):
        print("DE")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_best_cost = np.empty([self.testNum])
        np_best_x = np.empty([self.testNum, nV])
        np_convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            de = DE(nP=self.nP, MaxIt=self.MaxIt,
                    lb=lb, ub=ub, nV=nV, fobj=fobj)
            np_best_cost[i], np_best_x[i], np_convergence_curve[i] = de.run()
            print("%d test: " % (i + 1), np_best_cost[i])

        best_cost = np_best_cost.min()
        ave_cost = np_best_cost.mean()
        var_cost = np_best_cost.var()
        ave_convergence_curve = np.empty((self.MaxIt))
        for i in range(self.MaxIt):
            ave_convergence_curve[i] = np_convergence_curve[:, i].mean()
        return best_cost, ave_cost, var_cost, ave_convergence_curve


if __name__ == "__main__":
    mng = Manage(nP=50, nV=30, MaxIt=500, testNum=20)
    for i in range(1, mng.bmf.size+1):
        fname = i
        lb, ub, nV, fobj = mng.bmf.get(fname)
        # mng.drawFunction3D(fname)
        cost_gbo, ave_gbo, var_gbo, cc_gbo = mng.runGBO(fname)
        cost_ga, ave_ga, var_ga, cc_ga = mng.runGA(fname)
        cost_de, ave_de, var_de, cc_de = mng.runDE(fname)
        print("- Best Cost -")
        print("GBO: ", cost_gbo)
        print("GA : ", cost_ga)
        print("DE : ", cost_de)
        print()
        print("- Average Cost -")
        print("GBO: ", ave_gbo)
        print("GA : ", ave_ga)
        print("DE : ", ave_de)
        print()
        print("- Variance Cost -")
        print("GBO: ", var_gbo)
        print("GA : ", var_ga)
        print("DE : ", var_de)

        it_l = 0
        it_u = mng.MaxIt
        Draw.drawPloterro([cc_gbo[it_l:it_u], cc_ga[it_l:it_u], cc_de[it_l:it_u]],
                        ['GBO', 'GA', 'DE'], fobj.__doc__)
