import os
import numpy as np
import matplotlib.pyplot as plt
import h5py

def get_files(file_dir):
    twelve = []
    label_twelve = []
    halfpasttwelve = []
    label_halfpasttwelve = []
    three = []
    label_three = []
    halfpastthree = []
    label_halfpastthree = []
    six = []
    label_six = []
    halfpastsix = []
    label_halfpastsix = []

    for file in os.listdir(file_dir+'/000'):
            twelve.append(file_dir +'/000'+'/'+ file)
            label_twelve.append(0)
    for file in os.listdir(file_dir+'/030'):
            halfpasttwelve.append(file_dir +'/030'+'/'+file)
            label_halfpasttwelve.append(1)
    for file in os.listdir(file_dir+'/300'):
            three.append(file_dir +'/300'+'/'+ file)
            label_three.append(2)
    for file in os.listdir(file_dir+'/330'):
            halfpastthree.append(file_dir +'/330'+'/'+file)
            label_halfpastthree.append(3)
    for file in os.listdir(file_dir+'/600'):
            six.append(file_dir +'/600'+'/'+ file)
            label_six.append(4)
    for file in os.listdir(file_dir+'/630'):
            halfpastsix.append(file_dir +'/630'+'/'+file)
            label_halfpastsix.append(5)

    image_list = np.hstack((twelve, halfpasttwelve, three, halfpastthree, six, halfpastsix))
    label_list = np.hstack((label_twelve, label_halfpasttwelve, label_three, label_halfpastthree, label_six, label_halfpastsix))
 
    
    temp = np.array([image_list, label_list])
    temp = temp.transpose()
    np.random.shuffle(temp)
 
    
    image_list = list(temp[:, 0])
    label_list = list(temp[:, 1])
    label_list = [int(i) for i in label_list]
    
    return image_list,label_list

train_dir = './clock'
image_list,label_list = get_files(train_dir)

test_num = 600

Train_image =  np.random.rand(len(image_list)-test_num, 128, 128, 3).astype('float32')
Train_label = np.random.rand(len(image_list)-test_num, 1).astype('float32')
 
Test_image =  np.random.rand(test_num, 128, 128, 3).astype('float32')
Test_label = np.random.rand(test_num, 1).astype('float32')

for i in range(len(image_list)-test_num):
    Train_image[i] = np.array(plt.imread(image_list[i]))
    Train_label[i] = np.array(label_list[i])
 
for i in range(len(image_list)-test_num, len(image_list)):
    Test_image[i+test_num-len(image_list)] = np.array(plt.imread(image_list[i]))
    Test_label[i+test_num-len(image_list)] = np.array(label_list[i])

f = h5py.File('data.h5', 'w')
f.create_dataset('X_train', data=Train_image)
f.create_dataset('y_train', data=Train_label)
f.create_dataset('X_test', data=Test_image)
f.create_dataset('y_test', data=Test_label)
f.close()
