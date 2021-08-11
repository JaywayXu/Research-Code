from .environments_dict import get_env
from .Network import CreateModel, CreateMediumModel, CreateBigModel
from copy import deepcopy
import numpy as np
from analyzer import kerpy
from PIL import Image

class MujocoEnv():
    def __init__(self, name, lb, ub):
        model_types = {'SMALL': CreateModel,
                       'MEDIUM': CreateMediumModel,
                       'BIG': CreateBigModel}
        self.name = name
        env, task, model_type = get_env(name)
        self.env = env
        self.metaworld_task = task
        self.model_type = model_type
        self.model = model_types[model_type](self.env)
        self.lb = lb
        self.ub = ub
        self.info = None
        self.episodes = 100

    def setInfo(self, info):
        self.info = info
        self.D = info.D

    def test(self, num_episodes, max_steps=None, candidate=None, render=False,
             decode=False, frame_skip=1):
        if candidate is not None:
            if decode:
                candidate = self._extract_candidate(candidate)
                candidate = self._decode_candidate(candidate)
            self._set_weights(candidate)

        if max_steps is None:
            self.max_steps = self.env.max_path_length
        else:
            self.max_steps = max_steps
        rewards = []
        win_times = np.full((num_episodes,), 0)
        for episode in range(num_episodes):
            episode_reward = 0
            self.env.set_task(self.metaworld_task)
            obs = deepcopy(self.env.reset())
            for step in range(self.max_steps):
                action = self.model.predict(np.array([obs]))[0]
                obs, r, done, info = self.env.step(action)
                obs = deepcopy(obs)
                episode_reward += r
                if bool(info['success']):
                    try:
                        _tr = self.env.target_reward
                    except AttributeError:
                        _tr = 0
                    episode_reward += (self.max_steps-step) * (_tr * 0.75)
                    win_times[episode] = 1
                    break
            rewards.append(episode_reward)
        success_rate = sum(win_times) / num_episodes
        # print(f"Rew: {sum(rewards)/len(rewards)} / sr: {success_rate}")
        return rewards, success_rate

    def _extract_candidate(self, candidate):
        new_candidate = []
        for i, l in enumerate(self.model.layers):
            l_info = getattr(self.info, f"layer{i}")
            if(l_info.trainable):
                b = candidate[l_info.b_index: l_info.b_index + l_info.b_size]
                w = candidate[l_info.w_index: l_info.w_index + l_info.w_size]
                b = candidate[l_info.b_index: l_info.b_index + l_info.b_size]
                new_candidate += list(w)
                new_candidate += list(b)
        return new_candidate

    def _decode_candidate(self, candidate):
        candidate = np.array(candidate)
        return self.lb + candidate * (self.ub - self.lb)

    def fitness(self, candidate):
        assert self.info is not None, "Error: self.info == None"
        candidate = self._extract_candidate(candidate)
        candidate = self._decode_candidate(candidate)
        self._set_weights(candidate)
        rews, perc = self.test(self.episodes)
        f = -round(np.mean(rews), 6)
        # print(f"fitness: {f}, success_rate: {perc},
        return f, candidate, perc

    def _set_weights(self, new_weights):
        m = self.model
        w = new_weights
        k = self.info.mask
        s = self.info.shapes
        kerpy.set_weights(m, w, k, s)
        del m, w, k, s
