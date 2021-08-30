"""This is to build a probabilistic model and mixture model for the population."""
import numpy as np
from scipy.stats import multivariate_normal

def RandomkeyEncoding(solutions):
    encoded_solution = np.zeros_like(solutions, dtype=float)
    [n, dims] = solutions.shape
    keys = np.arange(0, 1, 1./dims)
    for i in range(n):
        encoded_solution[i] = keys[solutions[i]]
    return encoded_solution

def RandomkeyDecoding(solutions):
    decoded_solution = np.zeros_like(solutions).astype(int)
    [n, dims] = solutions.shape
    for i in range(n):
        decoded_solution[i, np.argsort(solutions[i])] = np.arange(dims).astype(int)
    return decoded_solution

class ProbabilisticModel(object):
    def __init__(self, modelType):
        self.type = modelType
        self.dim = None
        if self.type == 'mvarnorm':
            self.mean = None
            self.cov = None
            self.mean_noisy = None
            self.cov_noisy = None
        elif self.type == 'umd':
            self.probOne = None
            self.probZero = None
            self.probOne_noisy = None
            self.probZero_noisy = None
        else:
            raise ValueError('Invalid probabilistic model type!')

    def buildModel(self, solutions):
        pop = solutions.shape[0]
        self.dim = solutions.shape[1]
        if self.type == 'mvarnorm':
            self.mean = np.mean(solutions, axis=0)
            self.cov = np.cov(solutions.T)
            self.cov = np.diag(np.diag(self.cov))
            solutions_noisy = np.concatenate((solutions, np.random.rand(int(0.1*pop), self.dim)), axis=0)
            self.mean_noisy = np.mean(solutions_noisy, axis=0)
            self.cov_noisy = np.cov(solutions_noisy.T)
            self.cov_noisy = np.diag(np.diag(self.cov_noisy))
        else:
            self.probOne = np.mean(solutions, axis=0)
            self.probZero = 1 - self.probOne
            solutions_noisy = np.concatenate((solutions, np.random.rand(int(0.1*pop), self.dim)), axis=0)
            self.probOne_noisy = np.mean(solutions_noisy, axis=0)
            self.probZero_noisy = 1 - self.probOne_noisy

    def sample(self, nSol):
        if self.type == 'mvarnorm':
            solutions = np.random.multivariate_normal(self.mean, self.cov, nSol)
        else:
            solutions = np.random.rand(nSol, self.dim)
            index1 = solutions <= self.probOne
            index0 = solutions > self.probOne
            solutions[index1] = 1
            solutions[index0] = 0
        return solutions

    def pdfEval(self, solutions):
        if self.type == 'mvarnorm':
            pdf = multivariate_normal.pdf(solutions, mean=self.mean_noisy, cov=self.cov_noisy)
        else:
            nSol = solutions.shape[0]
            pdf = np.zeros(nSol)
            probvector = np.zeros(self.dim)
            for i in range(nSol):
                index = solutions[i, :] == 1
                probvector[index] = self.probOne_noisy[index]
                index = solutions[i, :] == 0
                probvector[index] = self.probZero_noisy[index]
                pdf[i] = np.prod(probvector)
        return pdf

    def modify(self, dims):
        if dims < self.dim:
            if self.type == 'mvarnorm':
                self.mean = self.mean[:dims]
                self.cov = self.cov[:dims, :dims]
                self.mean_noisy = self.mean_noisy[:dims]
                self.cov_noisy = self.cov_noisy[:dims, :dims]
            else:
                self.probOne = self.probOne[:dims]
                self.probZero = self.probZero[:dims]
                self.probOne_noisy = self.probOne_noisy[:dims]
                self.probZero_noisy = self.probZero_noisy[:dims]

        elif dims > self.dim:
            if self.type == 'mvarnorm':
                mean_cat = np.zeros(dims) + 0.5
                mean_cat[:self.dim] = self.mean
                self.mean = mean_cat
                cov_cat = np.diag(np.ones(dims) + 1)
                cov_cat[:self.dim, :self.dim] = self.cov
                self.cov = cov_cat

                mean_cat = np.zeros(dims) + 0.5
                mean_cat[:self.dim] = self.mean_noisy
                self.mean_noisy = mean_cat
                cov_cat = np.diag(np.ones(dims))
                cov_cat[:self.dim, :self.dim] = self.cov_noisy
                self.cov_noisy = cov_cat
            else:
                self.probOne = np.concatenate((self.probOne, np.zeros(dims - self.dim) + 0.5))
                self.probZero = np.concatenate((self.probZero, np.zeros(dims - self.dim) + 0.5))
                self.probOne_noisy = np.concatenate((self.probOne_noisy, np.zeros(dims - self.dim) + 0.5))
                self.probZero_noisy = np.concatenate((self.probZero_noisy, np.zeros(dims - self.dim) + 0.5))

        self.dim = dims




class MixtureModel(object):
    def __init__(self, allModels):
        self.model_list = allModels.copy()
        self.nModels = len(allModels)
        self.alpha = (1/self.nModels)*np.ones(self.nModels)
        self.probTable = None
        self.nSol = None

    def createTable(self, solutions, CV, modelType, probs_RL=None):
        if CV:
            self.nModels = self.nModels + 1
            self.model_list.append(ProbabilisticModel(modelType=modelType))
            self.model_list[-1].buildModel(solutions)
            self.alpha = (1/self.nModels) * np.ones(self.nModels)
            nSol = solutions.shape[0]
            self.nSol = nSol
            self.probTable = np.ones([nSol, self.nModels])
            if probs_RL is None:
                for j in range(self.nModels-1):
                    self.probTable[:, j] = self.model_list[j].pdfEval(solutions)
            else:
                for j in range(0, self.nModels-2):
                    self.probTable[:, j] = self.model_list[j].pdfEval(solutions)
                self.probTable[:, -2] = probs_RL
            for i in range(nSol):  # Leave-one-out cross validation
                x = np.concatenate((solutions[:i, :], solutions[i+1:, :]))
                tModel = ProbabilisticModel(modelType=modelType)
                tModel.buildModel(x)
                self.probTable[i, -1] = tModel.pdfEval(solutions[[i], :])
        else:
            nSol = solutions.shape[0]
            self.probTable = np.ones([nSol, self.nModels])
            for j in range(self.nModels):
                self.probTable[:, j] = self.model_list[j].pdfEval(solutions)
            self.nSol = nSol

    def EMstacking(self):
        iterations = 100
        for _ in range(iterations):
            talpha = self.alpha
            probVector = np.matmul(self.probTable, talpha.T)
            for i in range(self.nModels):
                talpha[i] = np.sum((1/self.nSol)*talpha[i]*self.probTable[:, i]/probVector)
            self.alpha = talpha

    def mutate(self):
        modif_alpha = np.maximum(self.alpha + np.random.normal(0, 0.01, self.nModels), 0)
        total_alpha = np.sum(modif_alpha)
        if total_alpha == 0:
            self.alpha = np.zeros(self.nModels)
            self.alpha[-1] = 1
        else:
            self.alpha = modif_alpha/total_alpha

    def sample(self, nSol, samplesRL=None):
        indSamples = np.ceil(nSol*self.alpha).astype(int)
        solutions = np.array([])
        for i in range(self.nModels):
            if indSamples[i] == 0:
                pass
            elif i == self.nModels - 2 and samplesRL is not None:
                solutions = np.vstack([solutions, samplesRL]) if solutions.size else samplesRL
            else:
                sols = self.model_list[i].sample(indSamples[i])
                solutions = np.vstack([solutions, sols]) if solutions.size else sols
        solutions = solutions[np.random.permutation(solutions.shape[0]), :]
        solutions = solutions[:nSol, :]
        return solutions

    def n_samples(self, ind, nSol):
        return np.ceil(nSol * self.alpha[ind]).astype(int)


