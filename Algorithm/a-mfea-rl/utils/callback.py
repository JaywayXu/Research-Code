# -*- coding: utf-8 -*-
import pickle as pk
import pandas as pd


FIRST_CALL = True


def callback_function(pop_info, fname, generation):
    global FIRST_CALL
    if FIRST_CALL:
        from shutil import rmtree
        from os import mkdir

        try:
            rmtree(f"summary/{fname}/")
        except FileNotFoundError:
            pass
        mkdir(f"summary/{fname}")

    # print("Crossover Matrix:")
    # print(pd.DataFrame(pop_info['crossover_matrix'], dtype=np.uintc))
    # print("\nEffective Crossover:")
    # print(pd.DataFrame(pop_info['effective_crossovers'], dtype=np.uintc))
    # print("Mutation Matrix:")
    # print(pd.DataFrame(pop_info['mutation_matrix'], dtype=np.uintc))
    # print("\nEffective Mutation:")
    # print(pd.DataFrame(pop_info['effective_mutations'], dtype=np.uintc))
    print("\nRMP Matrix:")
    print(pop_info['rmp_matrix'])
    # print("RMP por capas")
    # print("Total")
    # print(pop_info['layer_crossover_matrix'])
    print("Effectives")
    print(pop_info['layer_effective_crossovers'])

    print('\n ~~ TASKS INFO ~~')
    envs = []
    means = []
    stds = []
    bests = []
    srates = []
    names = []
    pops = []
    for i in range(pop_info['num_tasks']):
        name = pop_info['task'+str(i)]['name']
        mean = pop_info['task'+str(i)]['mean']
        std = pop_info['task'+str(i)]['std']
        best = pop_info['task'+str(i)]['pole'][0][1]
        p = pop_info['task'+str(i)]['num_ind']
        srate = pop_info['task'+str(i)]['pole'][0][2]
        means.append(round(mean, 3))
        stds.append(round(std, 3))
        bests.append(round(best, 3))
        srates.append(round(srate, 6))
        names.append(name)
        pops.append(p)

        # Delete ENV
        if FIRST_CALL:
            envs.append(pop_info['task'+str(i)]['env'])

        # print(f'Task-{i} ({name}): {p} indivs', end=' ')
        # print(f'Best/Success(%):{best}/{srate} Mean: {mean} Std: {std} ')
    path = f"summary/{fname}/{str(generation)}.pickle"
    path_envs = f"summary/{fname}/envs.pickle"

    # PRINT
    colms = ['Name', 'Pop Amount', 'Best', 'Success Rate', 'Mean', 'Std']
    df = pd.DataFrame(list(zip(names, pops, bests, srates, means, stds)),
                      columns=colms)
    print(df.to_string(justify='center'))
    with open(path, 'wb') as f:
        pk.dump(pop_info, f)
        f.close()

    # Helps saving space on next calls
    if FIRST_CALL:
        with open(path_envs, 'wb') as f:
            pk.dump(envs, f)
            f.close()

    FIRST_CALL = False
