# -*- coding: utf-8 -*-
import numpy as np
import ray
import pickle

@ray.remote
class PIndividual(object):
    def __init__(self, D_multitask, n_tasks):
        self.dim = D_multitask
        self.tasks = None
        self.no_of_tasks = n_tasks
        self.rnvec = np.random.uniform(size=D_multitask)
        self.candidate = None
        self.skf = None  # skill factor

    def evaluate(self, p_il, method):
        assert self.skf is not None, "Error: Skill factor is None"
        if self.skf is None:
            raise ValueError("skill factor not set")
        else:
            task = self.tasks # check set_individual
            objective, candidate, sr = task.mujoco_env.fitness(self.rnvec)
            funcCount = 1
        self.objective = objective
        self.candidate = candidate
        self.success_rate = sr
        ret_dict = {'skf': self.skf, 'candidate': candidate,
                    'objective':objective, 'success_rate': sr,
                    'rnvec':self.rnvec}
        return ret_dict

    def set_individual(self, rnvec, candidate, skf):
        self.rnvec = rnvec
        self.candidate = candidate
        if skf != self.skf:
            env = pickle.load(open('/tmp/amfearl/'+str(skf)+'.pickle','rb'))
            self.tasks = env
            del env
        self.skf = skf
        return 1

    def get_individual(self):
        return self.rnvec, self.candidate, self.skf


class Individual(object):
    def __init__(self, D_multitask, tasks):
        self.dim = D_multitask
        self.tasks = tasks
        self.no_of_tasks = len(tasks)
        self.rnvec = np.random.uniform(size=D_multitask)
        self.candidate = None
        self.scalar_fitness = None
        self.skf = None
        self.objective = None
        self.mut_cross = (False, False)
        self.parent_fitness = None
        self.parents_skfactor = None
        self.layers_updated = None
        self.success_rate = None

    def update_fitness(self, res):
        assert res['skf'] == self.skf, "Error: skill factor not matching"
        self.candidate = res['candidate']
        self.objective = res['objective']
        self.success_rate = res['success_rate']

    def clear(self):
        self.parent_fitness = None
        self.parents_skfactor = None
        self.mut_cross = (False, False)
        self.candidate = None

    def get_individual(self):
        return self.rnvec, self.candidate, self.skf

    def set_individual(self, rnvec, candidate, skf):
        self.rnvec = rnvec
        self.candidate = candidate
        sekf.skf = skf

    def evaluate(self, p_il, method):
        assert self.skf is not None, "Error: Skill factor is None"
        if self.skf is None:
            raise ValueError("skill factor not set")
        else:
            task = self.tasks[self.skf]
            objective, candidate, sr = task.mujoco_env.fitness(self.rnvec)
            funcCount = 1
        self.objective = objective
        self.candidate = candidate
        self.success_rate = sr
        ret_dict = {'skf': self.skf, 'candidate': candidate,
                    'objective':objective, 'success_rate': sr,
                    'rnvec':self.rnvec}
        return ret_dict
