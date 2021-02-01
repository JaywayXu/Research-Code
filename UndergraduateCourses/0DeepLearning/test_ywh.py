import  numpy as np
import tensorflow as tf
from PIL import Image
from keras import backend as K

model = tf.keras.models.load_model('ywh.model')

target = model.predict(np.array([[7, 5.5, 6.5, 3.9]])).argmax()
print(target)
if target == 0:
    print("Iris-setosa")
elif target == 1:
    print("Iris-versicolor")
else:
    print("Iris-virginica")

