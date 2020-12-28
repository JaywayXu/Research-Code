import  numpy as np
import tensorflow as tf
from PIL import Image
from keras import backend as K

def load_data(path='./mnist.npz'):
    f = np.load(path)
    x_train = f['x_train']
    f.close()
    return (x_train)

x_train = load_data()

index=15 #选择第n个数据

im = Image.fromarray(x_train[index])
im.show()

img_rows, img_cols = 28, 28

x_train = x_train.reshape(x_train.shape[0], img_rows, img_cols, 1)
x_train = x_train.astype('float32')
x_train /= 255

model = tf.keras.models.load_model('mnist-CNN.model')

preds = model.predict(x_train[index:index+1],1)

for i in range(0,9):
    print(i,"的概率是：",preds[0,i])
