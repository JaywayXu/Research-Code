# -*- coding: utf-8 -*-
"""
Created on Sat Mar 25 09:32:14 2017

@author: Administrator
"""
from keras.models import Sequential
from keras.layers.core import Dense,Dropout,Activation
from keras.optimizers import SGD
from sklearn import datasets, model_selection
import numpy as np
from keras.utils import np_utils
#转换数据
def one_hot_encode_object_array(arr):  
    '''''One hot encode a numpy array of objects (e.g. strings)'''  
    uniques, ids = np.unique(arr, return_inverse=True)  
    return np_utils.to_categorical(ids, len(uniques))  

#train_y_ohe = one_hot_encode_object_array(train_y)  
#test_y_ohe = one_hot_encode_object_array(test_y)  

iris=datasets.load_iris();
X,y=iris.data,iris.target
X_train,X_test,Y_train,Y_test=model_selection.train_test_split(X,y,test_size=0.25,random_state=33)  #分割数据

Y_train=one_hot_encode_object_array(Y_train)
Y_test=one_hot_encode_object_array(Y_test)


model=Sequential()#模型初始化

model.add(Dense(64, input_dim=4, init='uniform'))#输入20节点，第一隐含层64节点
model.add(Activation('tanh')) #第一隐含层激活函数为tanh
model.add(Dropout(0.5))
model.add(Dense(64, init='uniform')) #第一隐含层输出和第二隐含层输入
model.add(Activation('tanh')) 
model.add(Dropout(0.5))
model.add(Dense(3, init='uniform'))
model.add(Activation('sigmoid'))

sgd=SGD(lr=0.01,decay=1e-6,momentum=0.9,nesterov=True) #定义求解算法梯度下降
model.compile(loss='mean_squared_error',optimizer=sgd,metrics=["accuracy"]) #编译生成模型和损失函数
model.fit(X_train,Y_train,nb_epoch=200,batch_size=50)
model.save('ywh.model')
loss, accuracy=model.evaluate(X_test,Y_test,verbose=1)
print("\n")
print("Accuracy = {:.2f}".format(accuracy)) 
print("loss=",loss)
