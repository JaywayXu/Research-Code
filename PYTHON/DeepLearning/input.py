import tensorflow as tf
import numpy as np
from PIL import Image
import h5py

train_dataset = h5py.File('data.h5', 'r')
x = np.array(train_dataset['X_train'])  # your train set features
train_dataset.close()

x = x[0:3]
print(x[0].shape)

for i in x:
    im=Image.fromarray(i[:,:,0])
    im.show()

model = tf.keras.models.load_model('clock-CNN.model')

preds = model.predict(x)
print(preds)
