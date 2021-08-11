from .myNet import MLP


def CreateModel(env):
    nb_actions = env.action_space.shape[0]
    newnet = MLP()
    newnet.AddLayer(256, input_units=env.observation_space.shape[0], activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(nb_actions, activation='linear')
    newnet.summary()
    return newnet


def CreateMediumModel(env):
    nb_actions = env.action_space.shape[0]
    newnet = MLP()
    newnet.AddLayer(256, input_units=env.observation_space.shape[0], activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(nb_actions, activation='linear')
    newnet.summary()
    return newnet


def CreateBigModel(env):
    nb_actions = env.action_space.shape[0]
    newnet = MLP()
    newnet.AddLayer(256, input_units=env.observation_space.shape[0], activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(128, activation='relu')
    newnet.AddLayer(nb_actions, activation='linear')
    newnet.summary()
    return newnet
