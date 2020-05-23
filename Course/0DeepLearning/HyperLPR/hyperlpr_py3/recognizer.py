#coding=utf-8
from keras.models import Sequential
from keras.layers import Dense, Dropout, Activation, Flatten
from keras.layers import Conv2D,MaxPool2D
from keras.optimizers import SGD
from keras import backend as K

K.set_image_dim_ordering('tf')


import cv2
import numpy as np



index = {"京": 0, "沪": 1, "津": 2, "渝": 3, "冀": 4, "晋": 5, "蒙": 6, "辽": 7, "吉": 8, "黑": 9, "苏": 10, "浙": 11, "皖": 12,
         "闽": 13, "赣": 14, "鲁": 15, "豫": 16, "鄂": 17, "湘": 18, "粤": 19, "桂": 20, "琼": 21, "川": 22, "贵": 23, "云": 24,
         "藏": 25, "陕": 26, "甘": 27, "青": 28, "宁": 29, "新": 30, "0": 31, "1": 32, "2": 33, "3": 34, "4": 35, "5": 36,
         "6": 37, "7": 38, "8": 39, "9": 40, "A": 41, "B": 42, "C": 43, "D": 44, "E": 45, "F": 46, "G": 47, "H": 48,
         "J": 49, "K": 50, "L": 51, "M": 52, "N": 53, "P": 54, "Q": 55, "R": 56, "S": 57, "T": 58, "U": 59, "V": 60,
         "W": 61, "X": 62, "Y": 63, "Z": 64,"港":65,"学":66 ,"O":67 ,"使":68,"警":69,"澳":70,"挂":71};

chars = ["京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
             "琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
             "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P",
         "Q", "R", "S", "T", "U", "V", "W", "X",
             "Y", "Z","港","学","O","使","警","澳","挂" ];  #可以索引到的车牌号码和省份



def Getmodel_tensorflow(nb_classes): #定义了一个五层的卷积神经网络，在TensorFlow中可运行
    # nb_classes = len(charset)

    img_rows, img_cols = 23, 23
    # number of convolutional filters to use
    nb_filters = 32
    # size of pooling area for max pooling
    nb_pool = 2
    # convolution kernel size
    nb_conv = 3

    # x = np.load('x.npy')
    
    # y = np_utils.to_categorical(range(3062)*45*5*2, nb_classes)
    # weight = ((type_class - np.arange(type_class)) / type_class + 1) ** 3
    # weight = dict(zip(range(3063), weight / weight.mean()))  # 调整权重，高频字优先

    model = Sequential()
    model.add(Conv2D(32, (5, 5),input_shape=(img_rows, img_cols,1)))   #前三层为卷积池化层，包括正则化减少过拟合
    model.add(Activation('relu'))      #激活函数
    model.add(MaxPool2D(pool_size=(nb_pool, nb_pool)))    #最大池化
    model.add(Dropout(0.25))           #正则化
    model.add(Conv2D(32, (3, 3)))      #第二次卷积，32个3*3的滤波器
    model.add(Activation('relu'))      #激活函数
    model.add(MaxPool2D(pool_size=(nb_pool, nb_pool)))    #最大池化，滤波器尺寸为3*2
    model.add(Dropout(0.25))           #正则化参数0.25
    model.add(Conv2D(512, (3, 3)))
    # model.add(Activation('relu'))
    # model.add(MaxPooling2D(pool_size=(nb_pool, nb_pool)))
    # model.add(Dropout(0.25))
    model.add(Flatten())       #归一化，转变为X*1维向量
    model.add(Dense(512))     #全连接层，输出一个512维向量
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(nb_classes))
    model.add(Activation('softmax'))   #最后一层为一个softmax多分类器
    model.compile(loss='categorical_crossentropy',   #梯度下降，adam优化算法
                  optimizer='adam',
                  metrics=['accuracy'])
    return model




def Getmodel_ch(nb_classes):   ##设定字符识别网络，定义了一个五层的卷积神经网络，在ch中可运行，接入C++接口，与上一个函数相同
    # nb_classes = len(charset)

    img_rows, img_cols = 23, 23
    # number of convolutional filters to use
    nb_filters = 32
    # size of pooling area for max pooling
    nb_pool = 2
    # convolution kernel size
    nb_conv = 3

    # x = np.load('x.npy')
    # y = np_utils.to_categorical(range(3062)*45*5*2, nb_classes)
    # weight = ((type_class - np.arange(type_class)) / type_class + 1) ** 3
    # weight = dict(zip(range(3063), weight / weight.mean()))  # 调整权重，高频字优先

    model = Sequential()
    model.add(Conv2D(32, (5, 5),input_shape=(img_rows, img_cols,1)))   #前三层为卷积池化层，包括正则化减少过拟合
    model.add(Activation('relu'))  #激活函数
    model.add(MaxPool2D(pool_size=(nb_pool, nb_pool)))  #池化
    model.add(Dropout(0.25))  #正则化
    model.add(Conv2D(32, (3, 3)))
    model.add(Activation('relu'))
    model.add(MaxPool2D(pool_size=(nb_pool, nb_pool)))
    model.add(Dropout(0.25))
    model.add(Conv2D(512, (3, 3)))
    # model.add(Activation('relu'))
    # model.add(MaxPooling2D(pool_size=(nb_pool, nb_pool)))
    # model.add(Dropout(0.25))
    model.add(Flatten())
    model.add(Dense(756))     #全连接层，输出一个向量
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(nb_classes))
    model.add(Activation('softmax'))    #最后一层为一个softmax函数
    model.compile(loss='categorical_crossentropy',    #梯度下降，adam优化算法
                  optimizer='adam',
                  metrics=['accuracy'])
    return model



model  = Getmodel_tensorflow(65)
#构建网络

model_ch = Getmodel_ch(31)

model_ch.load_weights("./model/char_chi_sim.h5")  #训练过后保存权重
# model_ch.save_weights("./model/char_chi_sim.h5")
model.load_weights("./model/char_rec.h5")
# model.save("./model/char_rec.h5")


def SimplePredict(image,pos):  #初步预测车牌省份和数字
    image = cv2.resize(image, (23, 23))   #重设图片尺寸为23*23
    image = cv2.equalizeHist(image)
    image = image.astype(np.float) / 255  #对识别图像降维，以符合后续处理
    image -= image.mean()
    image = np.expand_dims(image, 3)
    if pos!=0:    #对数组进行区分
        res = np.array(model.predict(np.array([image]))[0])
    else:
        res = np.array(model_ch.predict(np.array([image]))[0])

    zero_add = 0 ;

    if pos==0:  #对数组进行再次区分，判断是否为偶数
        res = res[:31]
    elif pos==1:  #判断列表长度是否为奇数
        res = res[31+10:65]
        zero_add = 31+10
    else:
        res = res[31:]
        zero_add = 31

    max_id = res.argmax()  #返回最大索引值


    return res.max(),chars[max_id+zero_add],max_id+zero_add

