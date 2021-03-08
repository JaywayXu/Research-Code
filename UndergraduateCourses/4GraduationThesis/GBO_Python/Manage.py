from BenchmarkFunctions import BenchmarkFunctions
from Optimizer import GBO
import numpy as np


class Manage:
    def __init__(self):
        self.nP = 50
        self.MaxIt = 50
        self.fname = "F1"
        self.bmf = BenchmarkFunctions()
        self.testNum = 10

    def run_GBO(self):
        for fname in range(1, self.bmf.size + 1):
            print("\n%d Problem\n" % (fname))
            lb, ub, nV, fobj = self.bmf.get(fname)
            np_Best_Cost = np.zeros([self.testNum])
            np_Best_X = np.zeros([self.testNum, nV])
            np_Convergence_curve = np.zeros([self.testNum, self.MaxIt])

            for test_i in range(self.testNum):
                print("%d test:" % (test_i))
                gbo = GBO(self.nP, self.MaxIt, lb, ub, nV, fobj)
                np_Best_Cost[test_i], np_Best_X[test_i], np_Convergence_curve[
                    test_i] = gbo.get_resault()
            
            ave_Best_Cost = np_Best_Cost.mean()
            print(ave_Best_Cost)
            input()


if __name__ == "__main__":
    mng = Manage()
    mng.run_GBO()
