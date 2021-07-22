#! /usr/bin/env python3
# -*- coding: utf-8 -*-
import os
import ray
import shutil
import signal
import argparse
from mfea import mfea
from utils.callback import callback_function as cb
from utils.utils import load_compressed_pickle as lp
from pickle import dump as pdump

PATH_TO_METAWORLD_FILE = './metaworld/metaworld/envs/mujoco/sawyer_xyz/sawyer_xyz_env.py'
PATH_TO_FIXED = './exp_type/sawyer_xyz_env_fixed.py'
PATH_TO_RANDOM = './exp_type/sawyer_xyz_env_random.py'


def end_exp():
    shutil.rmtree('/tmp/amfearl/', ignore_errors=True)
    ray.shutdown()


def handler(signum, frame):
    end_exp()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', dest='path', type=str, default="summary")
    parser.add_argument('-t', dest='threads', type=int, default=None)
    parser.add_argument('-exp', dest='experiment', type=int, default=0)
    parser.add_argument('-r', dest='random', type=int, default=1,
                        help="0 - fixed ; 1 (default) - random")

    args = parser.parse_args()
    filename = args.path

    signal.signal(signal.SIGINT, handler)

    # Prepare temporary folder
    try:
        os.mkdir('/tmp/amfearl/')
    except FileExistsError:
        shutil.rmtree('/tmp/amfearl/')
        os.mkdir('/tmp/amfearl/')

    envs = []

    # Copy required files to make episodes' initialization random
    if args.random:
        shutil.copyfile(PATH_TO_RANDOM, PATH_TO_METAWORLD_FILE)
        print("Experiment configured for random reinitialization")
    else:
        shutil.copyfile(PATH_TO_FIXED, PATH_TO_METAWORLD_FILE)
        print("Experiment configured for fixed reinitialization")

    if args.experiment == 0:
        #   TOY EXPERIMENT
        print('Loading compressed_TOY.pbz2, this may take a few seconds...')
        data = lp('./compressed_TOY.pbz2')
        tasks = data['tasks']
        dim = data['unified_dimensions']
        filename = "TOY"

    if args.experiment == 1:
        #   MT-10
        print('Loading compressed_MT10.pbz2, this may take a few seconds...')
        data = lp('./compressed_MT10.pbz2')
        tasks = data['tasks']
        dim = data['unified_dimensions']
        filename = "MT10"

    if args.experiment == 2:
        #   MT-50
        print('Loading compressed_MT50.pbz2, this may take a few seconds...')
        data = lp('./compressed_MT50.pbz2')
        tasks = data['tasks']
        dim = data['unified_dimensions']
        filename = "MT50"

    for i in range(len(tasks)):
        pdump(tasks[i], open('/tmp/amfearl/'+str(i)+'.pickle', 'wb'))

    mfea.mfea(tasks, rmp=0.8, gen=1000, pop=60, episodes=300,
              D_multitask=dim, callback=cb,
              f_name=filename, num_threads=args.threads)

    # Cleaning
    end_exp()
