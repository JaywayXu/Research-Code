from BenchmarkFunctions import BenchmarkFunctions
from GBO import GBO

if __name__ == "__main__":
    nP = 50
    MaxIt = 500
    fname = "F11"

    bf = BenchmarkFunctions()
    lb, ub, dim, fobj = bf.get(fname)

    gbo = GBO(nP, MaxIt, lb, ub, dim, fobj)
    Best_Cost, Best_X, Convergence_curve = gbo.get_resault()
    print(Best_Cost, Best_X)
