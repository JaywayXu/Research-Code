# -*- coding:utf-8 -*-
import numpy as np
from .individual import Individual, PIndividual
from .operators import layer_wise_crossover, mutate, RouletteWheelSelection

import ray
import time
import tqdm

# ------------------
# RAY INITIALIZATION
# ------------------
ray.init()
print(f"Available resources: {ray.available_resources()}")


# ------------------
# METHODS
# ------------------
def update_remotes(population, remote_pop):
    assert len(population) == len(remote_pop), "Different lengths"
    remotes = []
    for i, ind in enumerate(remote_pop):
        rnvec, candidate, skf = population[i].get_individual()
        r = ind.set_individual.remote(rnvec, candidate, skf)
        remotes.append(r)
    exit_status = ray.get(remotes)
    assert all(exit_status), "Error when updating remotes info"


def evaluate_parallel(candidates, remotes, p_il, method):
    evals = len(candidates)
    maxV = len(candidates)
    results = np.full((evals,), None)
    index = 0
    b_format = '{desc} |{bar}| [elapsed: {elapsed}]'
    _desc = f"Evaluating 0/{maxV} : 0%"
    tq = tqdm.tqdm(total=maxV, bar_format=b_format, desc=_desc)
    while evals > 0:
        eval_amount = min(len(remotes), evals)
        pop_eval = candidates[index: index + eval_amount]
        # Update remotes
        update_remotes(pop_eval, remotes[:eval_amount])
        # Evaluate candidates in parallel
        rmt = remotes[:eval_amount]
        partials = [ind.evaluate.remote(p_il, method) for ind in rmt]
        evaluated_pop = ray.get(partials)
        results[index:index+eval_amount] = evaluated_pop
        # Update counts
        evals -= eval_amount
        index += eval_amount
        tq.update(eval_amount)
        tq.desc = "Evaluating " + f"({index}/{maxV}): "
        tq.desc += f"{round(index/maxV*100,3)}%"
    tq.close()
    return results


def rnd(x):
    return np.random.random() <= x


def isnan(x):
    return np.isnan(x)


# ----------
# A-MFEA-RL
# ----------
def mfea(tasks, pop=100, gen=1000, selproc='elitist',
         rmp=0.3, p_il=0.0, episodes=100, method='L-BFGS-B',
         D_multitask=None, callback=None, f_name=None,
         num_threads=None):
    '''
    :param tasks:       List of Task type, can not be empty
    :param pop:         Integer, population size
    :param gen:         Integer, generation
    :param selproc:     String, 'elitist', 'roulette wheel' or customized
    :param rmp:         Float, between 0 and 1
    :param p_il:        Float, between 0 and 1
    :param episodes:    Integer, episodes to test in the fitness function
    :param method:      String, details in scipy.optimize.minimize
    :param D_multitask: Integer, size of the Unified Space
    :param callback:    Function, function to call on each generation end
    :param f_name:      String, name of the folder in ./summary
    :param num_threads: Int, number of parallely evaluated candidates
    :return: Dict()
    '''

    # Population MUST be an EVEN number and tasks at LEAST 1
    pop = pop + 1 if pop % 2 != 0 else pop
    no_of_tasks = len(tasks)
    assert no_of_tasks >= 1 and pop % 2 == 0
    print('Valid configuration detected ==> (STARTING)')

    # Set the number of episodes to test the environments
    for i in range(no_of_tasks):
        tasks[i].mujoco_env.episodes = episodes

    # Matrix containing best individual per task
    bestobj = np.empty(shape=(gen, no_of_tasks))

    # (MFEA) Start MFEA variables
    pop = pop * no_of_tasks
    _shape = (2 * pop, no_of_tasks)
    factorial_costs = np.full(shape=_shape, fill_value=np.inf)
    factorial_ranks = np.empty(shape=_shape)

    # (MFEA) Initialize the local and remote populations
    max_threads = min(int(ray.available_resources()['CPU']), pop)
    if num_threads is not None:
        max_threads = min(num_threads, max_threads)
    print(f"Creating {pop} individuals and {max_threads} threads... ", end='')
    population = np.asarray([Individual(D_multitask, tasks) for _ in range(2 * pop)])
    remote_pop = [PIndividual.remote(D_multitask, no_of_tasks) for _ in range(max_threads)]
    print("Completed!")

    # Assign skill factor to each individual in population
    for i, individual in enumerate(population[:pop]):
        individual.skf = i % no_of_tasks

    # Algorithm data
    mu, mum = 2, 5
    rmp = float(rmp)
    crossover_matrix = np.full((len(tasks), len(tasks)), 0.0)
    effective_crossovers = np.full((len(tasks), len(tasks)), 0.0)
    mutation_matrix = np.full((len(tasks),), 0.0)
    effective_mutations = np.full((len(tasks),), 0.0)
    best_tmp = np.full(shape=no_of_tasks, fill_value=np.Inf)

    # Create layer-wise rmp matrix
    layer_amount = [task.num_layers for task in tasks]
    no_sharable_layers = max(layer_amount)
    rmp_matrix = np.full((no_of_tasks, no_of_tasks, no_sharable_layers), rmp)

    # Set rmp in tasks (i==j) = 1, np.nan if not trainable
    for i in range(no_of_tasks):
        rmp_matrix[i][i] = np.full((no_sharable_layers,), 1.0)
        infos = tasks[i].mujoco_env.info.getInfos()
        for idx, layer_info in enumerate(infos):
            if not layer_info.trainable:
                rmp_matrix[i, :, idx] = np.nan
        rmp_matrix[i, :, len(infos):] = np.nan
        for ii in range(no_of_tasks):
            if ii != i:
                rmp_matrix[i, ii, layer_amount[ii]:] = np.nan

    # EXTRA: Crossover and effective crossovers per layer
    lcrossover_matrix = np.copy(rmp_matrix)
    lcrossover_matrix[lcrossover_matrix >= 0] = 0
    leffective_crossovers = np.copy(rmp_matrix)
    leffective_crossovers[lcrossover_matrix >= 0] = 0

    # Evaluate population the first time
    res = evaluate_parallel(population[:pop], remote_pop, p_il, method)

    # Update local population and factorial costs
    for i, res in enumerate(res):
        population[i].update_fitness(res)
        j, factorial_cost = res['skf'], res['objective']
        factorial_costs[i, j] = factorial_cost

    for generation in range(gen):
        initial_time = time.time()
        count = pop
        factorial_costs[pop:, :] = np.inf
        inorder = np.random.permutation(pop)

        for i in range(int(pop/2)):
            # Get parents and offspring
            p1 = population[inorder[i]]
            p2 = population[inorder[i + int(pop/2)]]
            c1 = population[count]
            c2 = population[count+1]
            c1.clear()
            c2.clear()
            count += 2

            # Crossover ----
            rmp_row = rmp_matrix[p1.skf][p2.skf]

            if p1.skf == p2.skf:
                # INTRA-task crossover if same skill factor
                cross_layers = [False if isnan(i) else True for i in rmp_row]
            else:
                # else INTER-task crossover
                cross_layers = [False if isnan(i) else rnd(i) for i in rmp_row]

            # Crossover factors
            u = np.random.uniform(size=D_multitask)
            cf = np.empty(shape=D_multitask)
            cf[u <= 0.5] = np.power((2 * u[u <= 0.5]), (1 / (mu + 1)))
            cf[u > 0.5] = np.power((2 * (1 - u[u > 0.5])), (-1 / (mu + 1)))

            if any(cross_layers):
                # Required info
                infop1 = tasks[p1.skf].mujoco_env
                infop2 = tasks[p2.skf].mujoco_env

                # cross and get offspring
                c1.rnvec = layer_wise_crossover(p1.rnvec, p2.rnvec,
                                                cf, infop1, infop2,
                                                cross_layers)
                c2.rnvec = layer_wise_crossover(p2.rnvec, p1.rnvec,
                                                cf, infop2, infop1,
                                                cross_layers)
                c1.layers_updated = cross_layers
                c2.layers_updated = cross_layers

                # Update children skill factor
                sf1 = 1 + np.round(np.random.uniform())
                sf2 = 1 + np.round(np.random.uniform())
                if sf1 == 1:
                    c1.mut_cross = (False, True)
                    c1.skf = p1.skf
                    c1.parents_skfactor = (p1.skf, p2.skf)
                    c1.parent_fitness = p1.objective
                else:
                    c1.mut_cross = (False, True)
                    c1.skf = p2.skf
                    c1.parents_skfactor = (p2.skf, p1.skf)
                    c1.parent_fitness = p2.objective

                if sf2 == 1:
                    c2.mut_cross = (False, True)
                    c2.skf = p1.skf
                    c2.parents_skfactor = (p1.skf, p2.skf)
                    c2.parent_fitness = p1.objective
                else:
                    c2.mut_cross = (False, True)
                    c2.skf = p2.skf
                    c2.parents_skfactor = (p2.skf, p1.skf)
                    c2.parent_fitness = p2.objective

            else:
                c1.rnvec = mutate(c1.rnvec, D_multitask, mum)
                c2.rnvec = mutate(c2.rnvec, D_multitask, mum)

                # Allways get parents skill factor
                c1.skf = p1.skf
                c1.parents_skfactor = (p1.skf, p1.skf)
                c1.parent_fitness = p1.objective
                c1.mut_cross = (True, False)

                c2.skf = p2.skf
                c2.parents_skfactor = (p2.skf, p2.skf)
                c2.parent_fitness = p2.objective
                c2.mut_cross = (True, False)

        # Evaluate the offspring
        res = evaluate_parallel(population[pop:], remote_pop, p_il, method)

        # Update offspring values
        for i, individual in enumerate(population[pop:]):
            individual.update_fitness(res[i])
            j, factorial_cost = individual.skf, individual.objective
            factorial_costs[pop+i, j] = factorial_cost
            individual = population[pop+i]

            # Update crossover matrix
            if individual.mut_cross[1]:
                a, b = individual.parents_skfactor
                mask = np.array(individual.layers_updated)
                mask = np.where(mask==True)
                crossover_matrix[a][b] += 1
                lcrossover_matrix[a][b][individual.layers_updated] += 1

                # If child is better
                if individual.objective < individual.parent_fitness:
                    effective_crossovers[a][b] += 1
                    leffective_crossovers[a][b][individual.layers_updated] += 1
                    if a is not b:
                        new_rmp = rmp_matrix[a][b]
                        new_rmp[mask] += 0.1
                        new_rmp = np.clip(new_rmp, 0.15, 0.95)
                        rmp_matrix[a][b] = new_rmp

                # If child is worse
                elif a is not b:
                    new_rmp = rmp_matrix[a][b]
                    new_rmp[mask] -= 1e-2
                    new_rmp = np.clip(new_rmp, 0.15, 0.95)
                    rmp_matrix[a][b] = new_rmp

            # Update mutation matrix
            elif individual.mut_cross[0]:
                skf = individual.skf
                mutation_matrix[skf] += 1
                if individual.objective < individual.parent_fitness:
                    effective_mutations[skf] += 1

        for j in range(no_of_tasks):
            factorial_cost_j = factorial_costs[:, j]
            indices = list(range(len(factorial_cost_j)))
            indices.sort(key=lambda x: factorial_cost_j[x])
            ranks = np.empty(shape=2*pop)
            for i, x in enumerate(indices):
                ranks[x] = i + 1
            factorial_ranks[:, j] = ranks

        for i in range(2*pop):
            population[i].scalar_fitness = 1/np.min(factorial_ranks[i])

        if selproc == 'elitist':
            scalar_fitnesses = np.array([x.scalar_fitness for x in population])
            y = np.argsort(scalar_fitnesses)[::-1]
            population = population[y]
            factorial_costs = factorial_costs[y]
            factorial_ranks = factorial_ranks[y]

        elif selproc == 'roulette wheel':
            scalar_fitnesses = np.array([x.scalar_fitness for x in population])
            for i in range(pop):
                RW = RouletteWheelSelection
                population[i] = population[RW(scalar_fitnesses)]

        final_time = time.time() - initial_time
        # Parte de recogida y print de datos
        for j in range(no_of_tasks):
            xxx = np.argmin(factorial_costs[:, j])
            if(best_tmp[j] > factorial_costs[xxx, j]):
                bestobj[generation, j] = factorial_costs[xxx, j]
                best_tmp[j] = factorial_costs[xxx, j]

        pop_sf = np.array([p.skf for p in population[:pop]])
        fc = np.array(factorial_costs)
        pop_std = []
        pop_mean = []
        for i in range(len(tasks)):
            index = np.where(pop_sf == i)
            mean = np.mean(fc[:, i][index])
            std = np.std(fc[:, i][index])
            pop_mean.append(mean)
            pop_std.append(std)

        # Num of individuals per task
        popskf = np.full((len(tasks), ), 0)
        for i in range(pop):
            popskf[population[i].skf] += 1

        # Data
        pop_info = {'crossover_matrix': crossover_matrix,
                    'effective_crossovers': effective_crossovers,
                    'layer_crossover_matrix': lcrossover_matrix,
                    'layer_effective_crossovers': leffective_crossovers,
                    'mutation_matrix': mutation_matrix,
                    'effective_mutations': effective_mutations,
                    'rmp_matrix': rmp_matrix,
                    'num_tasks': no_of_tasks,
                    'configuration': {'pop_size': pop,
                                      'generations': gen,
                                      'selection_process': selproc,
                                      'rmp': rmp,
                                      'dimension': D_multitask}}

        for j in range(no_of_tasks):
            nnn = np.argsort(factorial_costs[:, j])
            pole_c = list(map(lambda x: x.candidate, population[nnn[:2]]))
            pole_f = list(map(lambda x: x.objective, population[nnn[:2]]))
            pole_s = list(map(lambda x: x.success_rate, population[nnn[:2]]))
            # The two best solutions (candidate, fitness, success rate)
            pole = list(zip(pole_c, pole_f, pole_s))
            env = tasks[population[nnn[0]].skf].mujoco_env
            pop_info['task'+str(j)] = dict()
            pop_info['task'+str(j)]['mean'] = pop_mean[j]
            pop_info['task'+str(j)]['std'] = pop_std[j]
            pop_info['task'+str(j)]['name'] = env.name
            pop_info['task'+str(j)]['num_ind'] = popskf[j]
            pop_info['task'+str(j)]['env'] = env
            pop_info['task'+str(j)]['pole'] = pole

        # Callback data
        if callback:
            msg = f" GENERATION {generation}"
            msg += f"Elapsed time: {round(final_time, 3)} s."
            print('/'+'='*len(msg)+'\\')
            print(msg)
            print(' '+'-'*(len(msg)))
            callback(pop_info, f_name, generation)
            print('\n '+'-'*(len(msg)))
            print(msg)
            print('\\'+'='*len(msg)+'/')

    return pop_info
