import numpy as np
import pickle
from ProbabilisticModel import ProbabilisticModel
from ProbabilisticModel import MixtureModel


def funceval(population, problem, dims):
    population = population.astype(int)
    if problem == 'onemax':
        fitness = np.sum(population, axis=1)
    elif problem == 'onemin':
        fitness = dims - np.sum(population, axis=1)
    elif problem == 'trap5':
        pop = population.shape[0]
        fitness = np.zeros(pop)
        index = np.arange(dims).reshape([-1, 5])
        nRows = index.shape[0]
        for i in range(pop):
            fitsum = 0
            for j in range(nRows):
                contri = np.sum(population[i, index[j, :]])
                if contri == 5:
                    fitsum += 5
                else:
                    fitsum += 4 - contri
            fitness[i] = fitsum
    elif problem == 'trap2':
        pop = population.shape[0]
        fitness = np.zeros(pop)
        index = np.arange(dims).reshape([-1, 2])
        nRows = index.shape[0]
        for i in range(pop):
            fitsum = 0
            for j in range(nRows):
                contri = np.sum(population[i, index[j, :]])
                if contri == 2:
                    fitsum += 2
                else:
                    fitsum += 1 - contri
            fitness[i] = fitsum
    else:
        raise ValueError('Invalid function call! Please enter an valid problem name.')
    return fitness


def binaryGA(problem, dims, objective, buildmodel=False):
    # load probabilistic models
    try:
        with open('allProbModels.pkl', 'rb') as f:
            allModels = pickle.load(f)
    except OSError:
        print("File not exist. Create an empty template.")
        allModels = []

    pop = 200
    gen = 1000

    population = np.round(np.random.rand(pop, dims))
    fitness = funceval(population, problem, dims)
    bestfitness = np.max(fitness)
    print('Generation 0 best fitness = %f' % bestfitness)

    for i in range(1, gen):
        parent1 = population[np.random.permutation(pop), :]
        parent2 = population[np.random.permutation(pop), :]
        offspring = np.zeros([pop, dims])
        tmp = np.random.rand(pop, dims)
        index = tmp >= 0.5  # uniform crossover
        offspring[index] = parent1[index]
        index = tmp < 0.5
        offspring[index] = parent2[index]
        tmp = np.random.rand(pop, dims)
        index = tmp < (1/dims)
        offspring[index] = np.abs(1 - offspring[index])  # flip bit mutation
        cfitness = funceval(offspring, problem, dims)
        interpop = np.concatenate((population, offspring), axis=0)
        interfitness = np.concatenate((fitness, cfitness), axis=0)
        index = np.argsort(-interfitness)  # default argsort is ascending
        population = interpop[index[:pop], :]
        fitness = interfitness[index[:pop]]
        bestfitness = fitness[0]
        print('Generation %d best fitness = %f' % (i, bestfitness))
        if buildmodel and (fitness[0] >= objective or i == gen):
            model = ProbabilisticModel('umd')
            model.buildModel(population)
            allModels.append(model)
            with open('allProbModels.pkl', 'wb') as f:
                pickle.dump(allModels, f)
            break


def transferBGA(problem, dims, reps, trans, buildmodel=False, objective=None):
    # load probabilistic models
    try:
        with open('allProbModels.pkl', 'rb') as f:
            allModels = pickle.load(f)
    except OSError:
        print("File not exist. Create an empty template.")
        allModels = []

    pop = 200
    gen = 100
    if trans['transfer'] and (not allModels):
        raise ValueError('No probabilistic models stored for transfer optimization.')
    fitness_hist = np.zeros([reps, gen])
    alpha = list()

    for rep in range(reps):
        alpha_rep = []
        population = np.round(np.random.rand(pop, dims))
        fitness = funceval(population, problem, dims)
        bestfitness = np.max(fitness)
        print('Generation 0 best fitness = %f' % bestfitness)
        for i in range(1, gen):
            if trans['transfer'] and i % trans['TrInt'] == 0:
                mixModel = MixtureModel(allModels)
                mixModel.createTable(population, True, 'umd')
                mixModel.EMstacking()
                mixModel.mutate()
                offspring = mixModel.sample(pop)
                alpha_rep = np.concatenate((alpha_rep, mixModel.alpha), axis=0)
                print('Mixture coefficients: %s' % np.array(mixModel.alpha))
            else:
                parent1 = population[np.random.permutation(pop), :]
                parent2 = population[np.random.permutation(pop), :]
                offspring = np.zeros([pop, dims])
                tmp = np.random.rand(pop, dims)
                index = tmp >= 0.5  # uniform crossover
                offspring[index] = parent1[index]
                index = tmp < 0.5
                offspring[index] = parent2[index]
                tmp = np.random.rand(pop, dims)
                index = tmp < (1 / dims)
                offspring[index] = np.abs(1 - offspring[index])  # flip bit mutation
            cfitness = funceval(offspring, problem, dims)
            interpop = np.concatenate((population, offspring), axis=0)
            interfitness = np.concatenate((fitness, cfitness), axis=0)
            index = np.argsort(-interfitness)  # default argsort is ascending
            population = interpop[index[:pop], :]
            fitness = interfitness[index[:pop]]
            bestfitness = fitness[0]
            fitness_hist[rep, i] = bestfitness
            print('Generation %d best fitness = %f' % (i, bestfitness))
            if buildmodel and (fitness[0] >= objective or i == gen):
                model = ProbabilisticModel('umd')
                model.buildModel(population)
                allModels.append(model)
                with open('allProbModels.pkl', 'wb') as f:
                    pickle.dump(allModels, f)
                break
        alpha.append(alpha_rep)


def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('problem', type=str)
    parser.add_argument('dims', type=int)
    parser.add_argument('--objective', type=float, default=None)
    parser.add_argument('--reps', type=int, default=1)
    parser.add_argument('--transfer', action='store_true')
    parser.add_argument('--TrInt', type=int, default=2)
    parser.add_argument('--buildmodel', action='store_true')
    args = parser.parse_args()

    binaryGA(args.problem, args.dims, args.objective, args.buildmodel)
    trans = {'transfer': args.transfer, 'TrInt': args.TrInt}
    transferBGA(args.problem, args.dims, args.reps, trans)


if __name__ == '__main__':
    main()
