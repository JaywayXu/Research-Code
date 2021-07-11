# -*- coding:utf-8 -*-
import numpy as np


class Layer():
    def __init__(self, ltype, lkeras_config, w_size,
                 w_shape, b_size, b_shape, trainable):
        self.type = ltype
        self.keras_config = lkeras_config
        self.w_size = w_size
        self.b_size = b_size
        self.w_shape = w_shape
        self.b_shape = b_shape
        self.trainable = trainable
        if self.trainable:
            self.he_limit = np.sqrt(6/w_shape[0])

    def __str__(self):
        retstr = f"\t | Type: {self.type}\n"
        retstr += f"\t | Trainable: {self.trainable}\n"
        retstr += f"\t | Size: Weights={self.w_size}, Bias={self.b_size}\n"
        retstr += f"\t | Shapes: Weights={self.w_shape}, Bias={self.b_shape}\n"
        try:
            w_i = self.w_index
            b_i = self.b_index
            retstr += f"\t | Indexes: Weights={w_i}, Bias={b_i}\n"
        except Exception:
            pass
        retstr += "\t |__\n"
        return retstr

    def AddIndexes(self, weights, bias): pass


class ModelInfo():
    def __init__(self, model):
        self.model = model
        self.D = model.count_params()
        self.num_layers = 0
        self.mask = []
        self.shapes = []

    def getInfos(self):
        infos = []
        for i in range(self.num_layers):
            layer_info = getattr(self, f"layer{i}")
            infos.append(layer_info)
        return infos

    def __str__(self):
        retstr = "---------- MODEL INFO ----------\n\n"
        retstr += f"\t* The model has {self.num_layers} layers:\n"
        for i in range(self.num_layers):
            layer_info = getattr(self, f"layer{i}")
            retstr += f"\n\t* Layer{i}:\n"
            retstr += str(layer_info)
        return retstr

    def AddLayerInfo(self, layer, trainable):
        pass


class Analyzer():
    def __init__(self):
        self.models_info = []

    def __str__(self):
        retstr = ""
        for m in self.models_info:
            retstr += str(m)
            retstr += "\n"
        return retstr

    def analyze(self, model): pass
    def unified_space(self, layers_to_share=None): pass
