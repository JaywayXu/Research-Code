from sko.DE import DE
import numpy as np

nP = 50
MaxIt = 500
lb = -100
ub = 100
dim = 30


def f1(x):
    '''Bent Cigar (Unimodal)'''
    D = x.shape[0]
    z = np.power(x[1], 2) + pow(10, 6) * np.power(x[2:D], 2).sum()
    return z


de = DE(
    func=f1,
    n_dim=dim,
    size_pop=nP,
    max_iter=MaxIt,
    lb=np.full(dim, lb),
    ub=np.full(dim, ub),
    # constraint_eq=constraint_eq,
    # constraint_ueq=constraint_ueq
)

best_x, best_y = de.run()
print('best_x:', best_x, '\n', 'best_y:', best_y)
