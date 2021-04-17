import numpy as np
from scipy import dot, exp, log, sqrt, floor, ones, randn, zeros_like, Inf, argmax, argmin, eye, outer, zeros
from scipy import array, power, diag, cos, sin
from scipy.linalg import expm, cholesky, solve, norm, eig
from scipy.stats import multivariate_normal


def tNES(f, x0, cApast, bs=20, lr=1e-3, sigma=1, maxEvals=1e6, verbose=False, targetFitness=-1e-10):
    """ transfer NES (tNES) as described in
    Wong, Jian Cheng, Abhishek Gupta, and Yew-Soon Ong.
    "Can Transfer Neuroevolution Tractably Solve Your Differential Equations?." arXiv preprint arXiv:2101.01998 (2021).

    Maximizes a function f. Returns (best solution found, corresponding fitness, etc.).
    Transfer optimization: inject sample from a mixture distribution that unifying current vs. past search distributions.

    Implemented baseline algo.: Exponential NES (xNES) as described in Glasmachers, Schaul, Sun, Wierstra and Schmidhuber (GECCO'10).
    """

    # target search
    dim = len(x0)
    I = eye(dim)
    center = x0.copy()
    A = eye(dim) * sigma  # sqrt of the covariance matrix
    # a same learning rate apply to all updates (including mixture model coef.)
    learningRate = lr
    batchSize = bs
    hist, thist = [], []  # to store history
    bestFound = None
    bestFitness = -Inf
    # sources
    ns = len(cApast)
    cps, Aps = [cp for (cp, Ap) in cApast], [Ap for (cp, Ap) in cApast]
    Cps = [eye(dim) * diag(Ap.dot(Ap.T)) for (cp, Ap) in cApast]
    mixtures = np.array([1 / (ns+1)]*(ns+1))  # initial mixing coef.
    # transfer settings
    # set mahalanobis dist. boundary to cover approx. 95% of normal
    radius = sqrt(12)
    every, till = 2, 1000   # do transfer every #steps till a #maxstep
    # loop
    numEvals = 0
    while numEvals + batchSize <= maxEvals and bestFitness < targetFitness:
        # produce and evaluate samples
        samples = [randn(dim) for _ in range(batchSize)]
        transfer = (numEvals/batchSize %
                    every == 0) and (numEvals/batchSize < till)
        if transfer:
            # transfer happens
            latents = np.random.choice(
                np.arange(0, ns+1), size=batchSize, p=mixtures)
            samples_o = [dot(A, samples[i]) + center if (latents[i] == ns) else
                         dot(Aps[latents[i]], samples[i]) + cps[latents[i]] for i in range(batchSize)]
            # projection applied to source samples
            samples_t = [samples_o[i] if (latents[i] == ns) else
                         center +
                         (samples_o[i] - center) * min(1, radius /
                                                       norm(solve(A, samples_o[i] - center)))
                         for i in range(batchSize)]
            # map (projected) source samples back to natural coordinates w.r.t. cur. search dist.
            samples = [samples[i] if (latents[i] == ns) else
                       solve(A, samples_t[i] - center) for i in range(batchSize)]
            # finesss evaluation & utilities
            fitnesses = [f(s) for s in samples_o]
            utilities = computeUtilities(fitnesses)
        else:
            # no transfer
            latents = zeros(batchSize)
            samples_o = [dot(A, s) + center for s in samples]
            fitnesses = [f(s) for s in samples_o]
            utilities = computeUtilities(fitnesses)
            # update best fitness
            if max(fitnesses) > bestFitness:
                bestFitness = max(fitnesses)
                bestFound = samples_o[argmax(fitnesses)]
                # return optimzied search dist. in form of center, A
                bestSearchdist = (center, A)
        numEvals += batchSize
        # print progress
        if verbose:
            if transfer:
                print("Step %5d | lr %.1e | numEvals %7d  : %.3e   [Best: %.5e]   | Mixture: %s" % (numEvals/batchSize,
                                                                                                    lr, numEvals,
                                                                                                    max(
                                                                                                        fitnesses),
                                                                                                    bestFitness,
                                                                                                    ' | '.join(['%.1f%%' % (100*m)
                                                                                                                for m in mixtures])))
            else:
                print("Step %5d | lr %.1e | numEvals %7d  : %.3e   [Best: %.5e]" % (numEvals/batchSize, lr, numEvals,
                                                                                    max(fitnesses), bestFitness))
        # store history
        hist.append([numEvals/batchSize, lr, numEvals,
                     max(fitnesses), bestFitness])
        thist.append([transfer] + list(mixtures))
        # update mixing coef.
        if transfer:
            C = A.dot(A.T)  # covariance matrix of current search dist.
            # a hack here: use diagonal matrix instead of full covariance for numerical stability
            C = eye(dim) * diag(C)
            pn_n = multivariate_normal.pdf(
                np.array(samples_o), mean=center, cov=C)
            pn_i = [multivariate_normal.pdf(
                np.array(samples_o), mean=cps[i], cov=Cps[i]) for i in range(ns)] + [pn_n]
            pmix = dot(mixtures, np.array(pn_i))
            gw = np.sum(utilities * pn_i / pmix, axis=1)
            mixtures += learningRate * gw
            mixtures /= sum(mixtures)   # rescale to 1
        # update center and variances
        center += dot(A, dot(utilities, samples))
        covGradient = sum([u * (outer(s, s) - I)
                           for (s, u) in zip(samples, utilities)])
        A = dot(A, expm(0.5 * learningRate * covGradient))

    return bestFound, bestFitness, bestSearchdist, hist, thist


def computeUtilities(fitnesses):
    L = len(fitnesses)
    ranks = zeros_like(fitnesses)
    l = zip(fitnesses, range(L))
    l = sorted(l)
    for i, (_, j) in enumerate(l):
        ranks[j] = i
    # smooth reshaping
    utilities = array([max(0., x)
                       for x in log(L / 2. + 1.0) - log(L - array(ranks))])
    utilities /= sum(utilities)       # make the utilities sum to 1
    # utilities -= 1. / L  # baseline
    return utilities

# test functions
# Rosenbrock function


def rosen(x):
    return - sum(100 * (x[:-1] ** 2 - x[1:]) ** 2 + (x[:-1] - 1) ** 2)

# Ellipsoid function


def elli(x):
    dim = len(x)
    A = array([power(10, 2 * i / (dim - 1.)) for i in range(dim)])
    return -dot(A * x, x)

# Square function


def square(x):
    return - sum((x - .5)**2)


# demo run
f = rosen
# past search dist.
cp1, Ap1 = np.array([.85, .85]), np.array([[-.05, -.012], [.05, -.04]])
cp2, Ap2 = np.array([.85, -.85]), np.array([[.15, -.02], [.05, -.04]])
cApast = [(cp1, Ap1), (cp2, Ap2)]
#cApast = [(cp1, Ap1)]
# test run (2D)
EVAL = 2e5
x0 = np.zeros(2) - 10.5  # initial sample
op_weight, op_fitness, op_searchdist, op_hist, op_thist = tNES(f, x0, cApast, bs=20, lr=1e-1, sigma=1e-1,
                                                               maxEvals=EVAL, verbose=True, targetFitness=-1e-9)
# in mixture model: source1, source2, ..., current search dist.

d = 45
f = rosen
# past search dist.
cp1, Ap1 = np.array([1.05]*d), np.diag(np.array([1e-3]*d))
cp2, Ap2 = np.array([.45]*d), np.diag(np.array([1e-3]*d))
cApast = [(cp1, Ap1), (cp2, Ap2)]
#cApast = [(cp1, Ap1)]
EVAL = 5e5
x0 = np.zeros(d) - 10.5  # initial sample
op_weight, op_fitness, op_searchdist, op_hist, op_thist = tNES(f, x0, cApast, bs=20, lr=1e-2, sigma=1e-2,
                                                               maxEvals=EVAL, verbose=True, targetFitness=-1e-9)
# in mixture model: source1, source2, ..., current search dist.
