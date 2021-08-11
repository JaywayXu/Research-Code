# -*- coding:utf-8 -*-
import numpy as np


# CROSSOVER - Especialized for DNNs ---
def layer_wise_crossover(p1, p2, cf, info, info2, layers):
    # Check both models' size and get sharable layers
    infos = info.info.getInfos()
    lay1 = info.info.num_layers
    lay2 = info2.info.num_layers
    sharable_layers = min(lay1, lay2)
    res = np.array(p1)
    for i, info in enumerate(infos[:sharable_layers]):
        if info.trainable and layers[i]:
            # Cross weights
            start = info.w_index
            end = start + info.w_size
            cross_w = crossover(p1[start:end], p2[start:end], cf[start:end])
            res[start:end] = cross_w
            # Cross biases
            start = info.b_index
            end = start + info.b_size
            cross_b = crossover(p1[start:end], p2[start:end], cf[start:end])
            res[start:end] = cross_b
    return res


# MUTATOR - polynomial mutation ---
def mutate(p, dim, mum):
    p_tmp = np.copy(p)
    for i in range(dim):
        if np.random.uniform() < (1 / dim):
            u = np.random.uniform()
            if u <= 0.5:
                delta = (2 * u) ** (1 / (1 + mum)) - 1
                p_tmp[i] = p[i] + delta * p[i]
            else:
                delta = 1 - (2 * (1 - u)) ** (1 / (1 + mum))
                p_tmp[i] = p[i] + delta * (1 - p[i])
    return p_tmp


# Find random candidate of same skill factor
def find_relative(population, skill_factor, N):
    pop_sf = np.array([p.skf for p in population[:N]])
    index = np.random.choice(np.where(pop_sf == skill_factor)[0])
    return population[index]


# Simulated Binary Crossover
def crossover(p1, p2, cf):
    # p1, p2 为genotype， ndarray类型, shape = (dim, )
    child = 0.5 * ((1+cf) * p1 + (1-cf) * p2)
    child[child < 0] = 0
    child[child > 1] = 1
    return child


# Selector ---
def RouletteWheelSelection(fitness):
    length = len(fitness)
    if length == 1:
        return 0
    accumulator = 0
    sumFits = np.sum(fitness)
    rndPoints = np.random.uniform(low=0, high=sumFits)
    for index, val in enumerate(fitness):
        accumulator += val
        if accumulator >= rndPoints:
            return index
