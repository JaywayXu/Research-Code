# !/usr/bin/env python3
# -*- coding: utf-8 -*-
from metaworld.envs.mujoco import env_dict
from metaworld import _make_tasks
from .model_types import ENV_ARQ


ALL_ENV_DICT = env_dict.ALL_V2_ENVIRONMENTS
ALLV2 = dict(ALL_ENV_DICT)
ALLV1 = dict(env_dict.ALL_V1_ENVIRONMENTS)
ALL_ENV_DICT.update(ALLV1)
FLAG = dict(partially_observable=False)


def get_env(name):
    kwargs = dict(task_id=0)
    if name == 'reach-v1' or name == 'reach-wall-v1':
        kwargs['task_type'] = 'reach'
    elif name == 'push-v1' or name == 'push-wall-v1':
        kwargs['task_type'] = 'push'
    elif name == 'pick-place-v1' or name == 'pick-place-wall-v1':
        kwargs['task_type'] = 'pick_place'
    env_args = {name: {'args': [], 'kwargs': kwargs}}
    task = _make_tasks(ALL_ENV_DICT, env_args, FLAG)[0]
    kwargs.pop('task_id')
    return ALL_ENV_DICT[name](), task, ENV_ARQ[name]  # (**kwargs)


def list_environments():
    print("________ ENVIRONMENT LIST ________\n")
    print(f"{list(ALL_ENV_DICT)}\n")
