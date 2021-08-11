# -*- coding:utf-8 -*-


class Task(object):
    def __init__(self, mujoco_env):
        self.dim = mujoco_env.D
        self.lb = mujoco_env.lb
        self.ub = mujoco_env.ub
        self.mujoco_env = mujoco_env
        self.num_layers = mujoco_env.info.num_layers

    def decode(self, rnvec):
        return self.lb + rnvec * (self.ub - self.lb)

    def encode(self, vec):
        return (vec - self.lb)/(self.ub - self.lb)
