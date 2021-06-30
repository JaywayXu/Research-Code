# -*- coding: utf-8 -*-
import numpy as np


# ------------------------------------------------------------
# Operations with models
# ------------------------------------------------------------
def get_flattened_weights(model):
    weights = model.get_weights()
    np_array = np.array([])
    for i in range(np.shape(weights)[0]):
        np_array = np.append(np_array, weights[i])
    return np_array


def unravel(weights, layer_shapes):
    reshaped_weights = []
    for layer_shape in layer_shapes:
        if type(layer_shape) == list:
            layer_weights = []
            for shape in layer_shape:
                to_r, weights = np.split(weights, [np.nanprod(shape)])
                layer_weights.append(np.reshape(to_r, shape))
            reshaped_weights.append(layer_weights)
        else:
            split = np.nanprod(layer_shape)
            to_r, weights = np.split(weights, [split])
            reshaped_weights.append(np.reshape(to_r, layer_shape))
    return reshaped_weights


def set_weights(model, weights, mask, shapes):
    weights = unravel(weights, shapes)
    for i, l in enumerate(model.layers):
        if mask[i] == 1:
            l.set_weights(weights.pop(0))
