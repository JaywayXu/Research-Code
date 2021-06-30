import numpy as np


# ~~~~~~~~~~~~~~~~~~~~~~~~~
#   ACTIVATION FUNCTIONS
# ~~~~~~~~~~~~~~~~~~~~~~~~~
def linear(X):
    return X


def relu(X):
    return np.maximum(X, np.zeros(X.shape))


# ~~~~~~~~~~~~~~~~~~~~~~~~~
#          LAYERS
# ~~~~~~~~~~~~~~~~~~~~~~~~~
class Layer(object):
    def __init__(self, input_units, output_units, activation='linear'):
        activations = {'relu': relu, 'linear': linear}
        self.input_units = input_units
        self.output_units = output_units
        self.w = np.random.uniform(-1, 1, (input_units, output_units))
        self.b = np.random.uniform(-1, 1, (output_units,))
        self.activation = activations[activation]
        self.trainable_params = np.prod(self.w.shape) + np.prod(self.b.shape)

    def forward(self, input_data):
        return self.activation(np.dot(input_data, self.w) + self.b)

    def get_config(self):
        return None

    def get_weights(self):
        return [self.w, self.b]

    def set_weights(self, weights):
        new_w = weights[0]
        new_b = weights[1]
        w_shape = new_w.shape
        b_shape = new_b.shape
        assert w_shape == self.w.shape, f"Error: shape in {w_shape} != {self.w.shape}"
        assert b_shape == self.b.shape, f"Error: shape in {b_shape} != {self.b.shape}"
        self.w = new_w
        self.b = new_b


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# MULTI-LAYER PERCEPTRON IMPLEMENTATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class MLP(object):
    def __init__(self):
        self.layers = None

    def set_weights(self, weights):
        i = 0
        for layer in self.layers:
            new_w_shape = weights[i].shape
            new_b_shape = weights[i + 1].shape
            w_shape = layer.w.shape
            b_shape = layer.b.shape
            assert new_w_shape == w_shape, f"ErrorW: shape {w_shape} != {new_w_shape}"
            assert new_b_shape == b_shape, f"ErrorB shape {b_shape} != {new_b_shape}"
            layer.w = weights[i]
            layer.b = weights[i + 1]
            i += 2

    def summary(self):
        print("===========================")
        print("    MODEL SUMMARY")
        print("===========================")
        for i, layer in enumerate(self.layers):
            msg = f"Dense-{i} => shape(in,out): ({layer.input_units},{layer.output_units}),"
            msg += f"trainable_params: {format(layer.trainable_params)}"
            print(msg)
            print("~"*len(msg))
        print("Total params: " + "{:,}".format(self.count_params()))

    def predict(self, data):
        res = data
        for layer in self.layers:
            res = layer.forward(res)
        return res

    def AddLayer(self, output_units, input_units=None, activation='linear'): pass
    def get_weights(self): pass
    def count_params(self): pass
