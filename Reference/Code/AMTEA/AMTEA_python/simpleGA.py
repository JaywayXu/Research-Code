import numpy as np
import pickle
from ProbabilisticModel import ProbabilisticModel
from ProbabilisticModel import MixtureModel
from double_pole_physics import PoledCart


def crossover(p1, p2, muc, dims):
    child1 = np.zeros(dims)
    child2 = np.zeros(dims)
    randlist = np.random.rand(dims)
    for i in range(dims):
        if randlist[i] <= 0.5:
            k = (2*randlist[i])**(1/(muc + 1))
        else:
            k = (1/(2*(1 - randlist[i])))**(1/(muc + 1))
        child1[i] = 0.5*(((1 + k)*p1[i]) + (1 - k)*p2[i])
        child2[i] = 0.5*(((1 - k)*p1[i]) + (1 + k)*p2[i])
        if np.random.rand() < 0.5:
            tmp = child1[i]
            child1[i] = child2[i]
            child2[i] = tmp
    return child1, child2


def mutation(p, mum, dims):
    child = p.copy()
    for i in range(dims):
        if np.random.rand() < 1/dims:
            u = np.random.rand()
            if u <= 0.5:
                delta = (2*u)**(1/(1 + mum)) - 1
                child[i] = p[i] + delta*p[i]
            else:
                delta = 1 - (2*(1 - u))**(1/(1 + mum))
                child[i] = p[i] + delta*(1 - p[i])
    return child


class Net(object):

    def __init__(self, nInput, nHidden, nOutput):
        super(Net, self).__init__()
        self.nInput = nInput
        self.nHidden = nHidden
        self.nOutput = nOutput
        self.nVariables = nInput*nHidden + nHidden*nOutput
        self.fc1 = None
        self.fc2 = None

    def feedforward(self, x):
        x = np.tanh(np.matmul(self.fc1, x))
        x = np.tanh(np.matmul(self.fc2, x))
        return x

    def init_weight(self, weights):
        if weights.size != self.nVariables:
            raise ValueError('Error length of variables!')
        self.fc1 = weights[:self.nInput*self.nHidden].reshape(self.nHidden, self.nInput)
        self.fc2 = weights[self.nInput*self.nHidden:].reshape(self.nOutput, self.nHidden)

    def get_nVariables(self):
        return self.nVariables

    def evaluate(self, cart, sLen):
        cart.__init__(sLen)
        while True:
            state = cart.get_state()
            cart.applied_force = 10*self.feedforward(state)
            cart.update_state()
            cart.update_state()
            if cart.failed:
                return cart.time
            elif (cart.time - 2000) > -0.00001:
                return cart.time


def simpleGA(sLen, buildmodel):
    """
    Simpe GA for double pole balancing problem
    :param sLen: length of shorter pole
    :param buildmodel: if True, then build probabilistic model
    :return: Optimized solution
    """
    if buildmodel:
        try:
            with open('allDPModels.pkl', 'rb') as f:
                allModels = pickle.load(f)
        except OSError:
            print("File not exist. Create an empty template.")
            allModels = []
    pop = 100
    generation = 100
    muc = 20  # crossover index SBX
    mum = 20  # mutation index (polynomial mutation)

    # define a feedforward neural network
    cart = PoledCart(sLen)
    bestfit_hist = np.zeros(generation)

    # initialize a feedforward net
    nInput = 6
    nHidden = 10
    nOutput = 1
    net = Net(nInput, nHidden, nOutput)
    nVariables = net.nVariables

    population = 12*np.random.rand(pop, nVariables) - 6
    fitness = np.zeros(pop)
    for i in range(pop):
        net.init_weight(population[i, :])
        fitness[i] = net.evaluate(cart, sLen)
    bestfit_hist[0] = np.max(fitness)
    print('Generation 0 best fitness = %f' % bestfit_hist[0])
    bestInd = np.argmax(fitness)
    bestSol = population[bestInd, :]

    for gen in range(1, generation):
        randlist = np.random.permutation(pop)
        offspring = np.zeros([pop, nVariables])
        for i in range(0, pop, 2):
            p1 = randlist[i]
            p2 = randlist[i+1]
            offspring[i, :], offspring[i+1, :] = crossover(population[p1, :], population[p2, :], muc, nVariables)
            offspring[i, :] = mutation(offspring[i, :], mum, nVariables)
            offspring[i+1, :] = mutation(offspring[i+1, :], mum, nVariables)
        cfitness = np.zeros(pop)
        for i in range(pop):
            net.init_weight(offspring[i, :])
            cfitness[i] = net.evaluate(cart, sLen)

        intpopulation = np.concatenate((population, offspring), axis=0)
        intfitness = np.concatenate((fitness, cfitness), axis=0)
        bestfit_hist[gen] = np.max(intfitness)
        bestInd = np.argmax(intfitness)
        bestSol = intpopulation[bestInd, :]

        # Elitist
        index = np.argsort(-intfitness)
        population = intpopulation[index[:pop], :]
        fitness = intfitness[index[:pop]]
        print('Generation %d best fitness = %f' % (gen, fitness[0]))

        if bestfit_hist[gen] - 2000 > -0.0001:
            print('Solution found!')
            bestfit_hist[(gen + 1):] = bestfit_hist[gen]
            break
    if buildmodel and bestfit_hist[-1] - 2000 > -0.0001:
        model = ProbabilisticModel('mvarnorm')
        model.buildModel(solutions=population)
        allModels.append(model)
        print("Model built successfully! There are %d probabilistic models in total." % len(allModels))
        with open('allDPModels.pkl', 'wb') as f:
            pickle.dump(allModels, f)

    return bestSol, bestfit_hist


def transferGA(sLen, trans, buildmodel):
    """
    Simpe GA for double pole balancing problem
    :param sLen: length of shorter pole
    :param trans: trans['transfer'], trans['TrInt']
    :param buildmodel: if True, then build probabilistic model
    :return: Optimized solution
    """
    try:
        with open('allDPModels.pkl', 'rb') as f:
            allModels = pickle.load(f)
    except OSError:
        print("File not exist. Create an empty template.")
        allModels = []

    if trans['transfer'] and (not allModels):
        raise ValueError('No probabilistic models stored for transfer optimization.')

    pop = 100
    generation = 100
    muc = 20  # crossover index SBX
    mum = 20  # mutation index (polynomial mutation)
    alpha_rep = []

    # define a feedforward neural network
    cart = PoledCart(sLen)
    bestfit_hist = np.zeros(generation)

    # initialize a feedforward net
    nInput = 6
    nHidden = 10
    nOutput = 1
    net = Net(nInput, nHidden, nOutput)
    nVariables = net.nVariables

    population = 12*np.random.rand(pop, nVariables) - 6
    fitness = np.zeros(pop)
    for i in range(pop):
        net.init_weight(population[i, :])
        fitness[i] = net.evaluate(cart, sLen)
    bestfit_hist[0] = np.max(fitness)
    print('Generation 0 best fitness = %f' % bestfit_hist[0])
    bestInd = np.argmax(fitness)
    bestSol = population[bestInd, :]

    for gen in range(1, generation):
        if trans['transfer'] and gen % trans['TrInt'] == 0:
            mixModel = MixtureModel(allModels)
            mixModel.createTable(population, True, 'mvarnorm')
            mixModel.EMstacking()
            mixModel.mutate()
            offspring = mixModel.sample(pop)
            alpha_rep = np.concatenate((alpha_rep, mixModel.alpha), axis=0)
            print('Mixture coefficients: %s' % np.array(mixModel.alpha))
        else:
            randlist = np.random.permutation(pop)
            offspring = np.zeros([pop, nVariables])
            for i in range(0, pop, 2):
                p1 = randlist[i]
                p2 = randlist[i+1]
                offspring[i, :], offspring[i+1, :] = crossover(population[p1, :], population[p2, :], muc, nVariables)
                offspring[i, :] = mutation(offspring[i, :], mum, nVariables)
                offspring[i+1, :] = mutation(offspring[i+1, :], mum, nVariables)

        cfitness = np.zeros(pop)
        for i in range(pop):
            net.init_weight(offspring[i, :])
            cfitness[i] = net.evaluate(cart, sLen)

        intpopulation = np.concatenate((population, offspring), axis=0)
        intfitness = np.concatenate((fitness, cfitness), axis=0)
        bestfit_hist[gen] = np.max(intfitness)
        bestInd = np.argmax(intfitness)
        bestSol = intpopulation[bestInd, :]

        # Elitist
        index = np.argsort(-intfitness)
        population = intpopulation[index[:pop], :]
        fitness = intfitness[index[:pop]]
        print('Generation %d best fitness = %f' % (gen, fitness[0]))

        if bestfit_hist[gen] - 2000 > -0.0001:
            print('Solution found!')
            bestfit_hist[(gen + 1):] = bestfit_hist[gen]
            break
    if buildmodel and bestfit_hist[-1] - 2000 > -0.0001:
        model = ProbabilisticModel('mvarnorm')
        model.buildModel(solutions=population)
        allModels.append(model)
        print("Model built successfully! There are %d probabilistic models in total." % len(allModels))
        with open('allDPModels.pkl', 'wb') as f:
            pickle.dump(allModels, f)

    return bestSol, bestfit_hist


def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('sLen', type=float)
    parser.add_argument('--buildmodel', action='store_true')
    parser.add_argument('--transfer', action='store_true')
    parser.add_argument('--TrInt', type=int, default=10)
    args = parser.parse_args()

    bestSol, _ = simpleGA(args.sLen, args.buildmodel)
    trans = {'transfer': args.transfer, 'TrInt': args.TrInt}
    bestSol, _ = transferGA(args.sLen, trans, args.buildmodel)
    with open('bestParameter.pkl', 'wb') as f:
        pickle.dump(bestSol, f)


if __name__ == '__main__':
    main()
