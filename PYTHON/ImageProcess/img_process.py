from tkinter import *
from tkinter.messagebox import *
from PIL import Image
import numpy as np
import copy
import os

#窗口
window = Tk()
window.title("图像处理程序")
window.geometry("230x173")

#全局变量
im_matrix_rgb = []  #矩阵存储图像[3(rgb)][hight, width]
im_matrix_rgb_old = []  #原图像
im_matrix_l = []  #灰度图像[hight, width]
width, height = 0, 0  #图像的宽高
read_success = False  #读取成功与否的标志
neighber_width = 3  #中值滤波邻域的宽度
bin_flag = 127  #二值化的分界点像素值


def load_img():
    '''读取图像'''
    global im_matrix_rgb_old, im_matrix_rgb, im_matrix_l, width, height, read_success
    file_name = file_name_entry.get()
    if os.path.exists(file_name):  #存在文件
        im = Image.open(file_name)  #读取图像
        width, height = im.size  #获取图像宽高
        # 读取RGB图像
        [r, g, b] = im.split()
        im_matrix_rgb = [r.getdata(), g.getdata(), b.getdata()]  #获取RGB数据
        for i in range(3):  #依次取RGB
            im_matrix_rgb[i] = np.matrix(im_matrix_rgb[i])  #转为单通道一维矩阵
            im_matrix_rgb[i] = np.reshape(im_matrix_rgb[i],
                                          (height, width))  #转为单通道高x宽矩阵
        im_matrix_rgb_old = copy.deepcopy(im_matrix_rgb)
        # 读取灰度图像
        im_matrix_l = im.convert('L').getdata()  #获取灰度数据
        im_matrix_l = np.matrix(im_matrix_l)  #转为单通道一维矩阵
        im_matrix_l = np.reshape(im_matrix_l, (height, width))  #转为单通道高x宽矩阵
        # 显示信息
        showinfo(title="读取图像", message="成功！")
        read_success = True
    else:  #不存在文件，读取失败
        showinfo(title="读取图像", message="文件不存在！请输入正确文件名！")
        read_success = False


def save_img():
    '''保存图像'''
    global im_matrix_rgb, im_matrix_l, read_success
    if read_success:
        save_file_name = file_name_entry.get()
        im_rgb = []
        for i in range(3):
            im_rgb.append(Image.fromarray(
                im_matrix_rgb[i]).convert('L'))  #转换为图像
        im = Image.merge('RGB', im_rgb)
        im.save(save_file_name)  #写入文件
        im_l = Image.fromarray(im_matrix_l).convert('L')
        im_l = [im_l for i in range(3)]
        im_l = Image.merge('RGB', im_l)
        im_l.save('l_' + save_file_name)
        showinfo(title="info", message="成功！")
    else:
        showinfo(title="info", message="请先读取图像！")


def show_img_old():
    '''显示原图'''
    global im_matrix_rgb_old, read_success
    if read_success:
        # 显示原图
        im_rgb_old = []
        for i in range(3):
            im_rgb_old.append(
                Image.fromarray(im_matrix_rgb_old[i]).convert('L'))  #转换为图像
        im_rgb_old = Image.merge('RGB', im_rgb_old)
        im_rgb_old.show()  #显示原图
    else:
        showinfo(title="info", message="请先读取图像！")


def show_img_rgb():
    '''显示彩色图'''
    global im_matrix_rgb, read_success
    if read_success:
        # 显示彩色图
        im_rgb = []
        for i in range(3):
            im_rgb.append(Image.fromarray(
                im_matrix_rgb[i]).convert('L'))  #转换为图像
        im_rgb = Image.merge('RGB', im_rgb)
        im_rgb.show()  #显示彩色图像
    else:
        showinfo(title="info", message="请先读取图像！")


def show_img_l():
    '''显示灰度图'''
    global im_matrix_l, read_success
    if read_success:
        # 显示灰度图
        im_l = Image.fromarray(im_matrix_l)  #转换为图像
        im_l.show()
    else:
        showinfo(title="info", message="请先读取图像！")


def fun_reverse_rgb():
    '''颜色反转(RGB)'''
    global im_matrix_rgb, read_success
    if read_success:
        for i in range(3):
            im_matrix_rgb[i] = 255 - im_matrix_rgb[i]  #彩色反转
        showinfo(title="info", message="成功！")
    else:
        showinfo(title="info", message="请先读取图像！")


def fun_reverse_l():
    '''颜色反转(灰度)'''
    global im_matrix_l, read_success
    if read_success:
        im_matrix_l = 255 - im_matrix_l  #灰度反转
        showinfo(title="info", message="成功！")
    else:
        showinfo(title="info", message="请先读取图像！")


def fun_ave_rgb():
    '''中值滤波(RGB)'''
    global im_matrix_rgb, read_success, width, height, neighber_width
    if read_success:
        # RGB图中值滤波(没有处理边界)
        for x in range(3):
            nb_num = pow(neighber_width, 2)  #邻域大小
            nb_range = neighber_width // 2  #偏移大小
            pixel = [0 for _ in range(nb_num)]  #保存邻域像素值
            r = [i for i in range(-nb_range, nb_range + 1)]
            delta = []
            #计算偏移
            for i in range(neighber_width):
                for j in range(neighber_width):
                    delta.append((r[i], r[j]))
            #中值滤波
            for i in range(nb_range, height - nb_range):
                for j in range(nb_range, width - nb_range):
                    #提取邻域值
                    for k in range(nb_num):
                        pixel[k] = im_matrix_rgb[x][i + delta[k][0],
                                                    j + delta[k][1]]
                    pixel.sort()
                    im_matrix_rgb[x][i, j] = pixel[nb_num // 2]
        showinfo(title="info", message="成功！")
    else:
        showinfo(title="info", message="请先读取图像！")


def fun_ave_l():
    '''中值滤波(灰度)'''
    global im_matrix_l, read_success, width, height, neighber_width
    if read_success:
        # 灰度图中值滤波(没有处理边界)
        nb_num = pow(neighber_width, 2)  #邻域大小
        nb_range = neighber_width // 2  #偏移大小
        pixel = [0 for _ in range(nb_num)]  #保存邻域像素值
        r = [i for i in range(-nb_range, nb_range + 1)]
        delta = []
        #计算偏移
        for i in range(neighber_width):
            for j in range(neighber_width):
                delta.append((r[i], r[j]))
        #中值滤波
        for i in range(nb_range, height - nb_range):
            for j in range(nb_range, width - nb_range):
                #提取邻域值
                for k in range(nb_num):
                    pixel[k] = im_matrix_l[i + delta[k][0], j + delta[k][1]]
                pixel.sort()
                im_matrix_l[i, j] = pixel[nb_num // 2]
        showinfo(title="info", message="成功！")
    else:
        showinfo(title="info", message="请先读取图像！")


def fun_bin():
    '''二值化(灰度)'''
    global im_matrix_l, read_success, width, height, bin_flag
    if read_success:
        for i in range(height):
            for j in range(width):
                if int(im_matrix_l[i, j]) > bin_flag:
                    im_matrix_l[i, j] = 255
                else:
                    im_matrix_l[i, j] = 0

        showinfo(title="info", message="成功！")
    else:
        showinfo(title="info", message="请先读取图像！")


def fun_edge():
    '''梯度求边界'''


input_lable = Label(window, text="文件名:", width=10)
file_name_entry = Entry(window, width=15)
file_name_entry.insert(END, "x.jpg")
load_img_button = Button(window, text="读取图像", width=15, command=load_img)
save_img_button = Button(window, text="保存图像", width=15, command=save_img)
show_img_old_button = Button(window,
                             text="显示原图",
                             width=15,
                             command=show_img_old)  #显示原图按钮
show_img_rgb_button = Button(window,
                             text="显示RGB图",
                             width=15,
                             command=show_img_rgb)
show_img_l_button = Button(window, text="显示灰度图", width=15, command=show_img_l)
spatial_reverse_rgb_button = Button(window,
                                    text="颜色反转(RGB)",
                                    width=15,
                                    command=fun_reverse_rgb)
spatial_reverse_l_button = Button(window,
                                  text="颜色反转(灰度)",
                                  width=15,
                                  command=fun_reverse_l)
spatial_ave_rgb_button = Button(window,
                                text="中值滤波(RGB)",
                                width=15,
                                command=fun_ave_rgb)
spatial_ave_l_button = Button(window,
                              text="中值滤波(灰度)",
                              width=15,
                              command=fun_ave_l)
spatial_sharp_button = Button(window,
                              text="二值化(灰度)",
                              width=15,
                              command=fun_bin)

#显示控件
input_lable.grid(row=0, column=0, columnspan=1)
file_name_entry.grid(row=0, column=1, columnspan=1)
load_img_button.grid(row=1, column=0, columnspan=1)
save_img_button.grid(row=2, column=0, columnspan=1)
show_img_old_button.grid(row=3, column=0, columnspan=1)
show_img_rgb_button.grid(row=4, column=0, columnspan=1)
show_img_l_button.grid(row=5, column=0, columnspan=1)
spatial_reverse_rgb_button.grid(row=1, column=1, columnspan=1)
spatial_reverse_l_button.grid(row=2, column=1, columnspan=1)
spatial_ave_rgb_button.grid(row=3, column=1, columnspan=1)
spatial_ave_l_button.grid(row=4, column=1, columnspan=1)
spatial_sharp_button.grid(row=5, column=1, columnspan=1)

#运行
window.mainloop()
