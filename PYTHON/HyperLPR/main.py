# -*- coding:utf-8 -*-

import HyperLPRLite as pr  # 引入LPR大类
import numpy as np
import matplotlib.pyplot as plt
import cv2
from PIL import ImageTk
from PIL import ImageFont
from PIL import Image
from PIL import ImageDraw
from tkinter import ttk
import tkinter as tk
from tkinter.filedialog import askopenfilename
from tkinter.messagebox import *
import pymysql
import datetime

# 连接数据库
db = pymysql.connect("localhost", "root", "lyc12030017",
                     "CarApp", charset='utf8')
print("数据库已连接")
# 获取操作游标
cursor = db.cursor()


# 初始化，读取模型
fontC = ImageFont.truetype(
    "/Volumes/DISK/CODE/PYTHON/HyperLPR-master//Font/platech.ttf", 14, 0)
model = pr.LPR("/Volumes/DISK/CODE/PYTHON/HyperLPR-master//model/cascade.xml", "/Volumes/DISK/CODE/PYTHON/HyperLPR-master//model/model12.h5",
               "/Volumes/DISK/CODE/PYTHON/HyperLPR-master//model/ocr_plate_all_gru.h5")  # 输入之前训练好的目标检测，车牌边界左右回归，车牌文字检测模型

# GUI窗口
window = tk.Tk()
window.title("车牌检测")
window.geometry("940x628")

global cv_img  # cv读取的图像
global canvas_img  # tk的图像格式

frame = tk.Frame(window)
canvas = tk.Canvas(frame, scrollregion=(0, 0, 2000, 2000))
plate_lable = tk.Label(window, text="预测结果：", width=12)
plate_entry = tk.Entry(window, width=12)
confidence_lable = tk.Label(window, text="准确度：", width=12)
confidence_entry = tk.Entry(window, width=12)
data_text = tk.Text(window, width=15, height=30)


def drawRectBox(image, rect, addText):  # 定义划定车牌矩形框函数，即定位车牌位置
    cv2.rectangle(image, (int(rect[0]), int(rect[1])),
                  (int(rect[0] + rect[2]), int(rect[1] + rect[3])),
                  (0, 0, 255), 2, cv2.LINE_AA)
    cv2.rectangle(image, (int(rect[0] - 1), int(rect[1]) - 16),
                  (int(rect[0] + 115), int(rect[1])), (0, 0, 255), -1,
                  cv2.LINE_AA)  # 设定矩形框的边界范围
    img = Image.fromarray(image)
    draw = ImageDraw.Draw(img)
    draw.text((int(rect[0] + 1), int(rect[1] - 16)),
              addText.encode('utf-8').decode('utf-8'), (255, 255, 255),
              font=fontC)
    imagex = np.array(img)
    return imagex  # 返回带有矩形框的车牌


def load_file():
    # 读取文件
    global cv_img, canvas_img

    plate_entry.delete(0, tk.END)
    confidence_entry.delete(0, tk.END)
    data_text.delete(1.0, tk.END)

    file_path = askopenfilename()
    if file_path:
        cv_img = cv2.imread(file_path)
        canvas_img = ImageTk.PhotoImage(image=Image.fromarray(cv_img))
        canvas.create_image(0, 0, image=canvas_img, anchor=tk.NW)
        canvas.update()


def run():
    # 运行
    global cv_img, canvas_img, cursor, db
    for pstr, confidence, rect in model.SimpleRecognizePlateByE2E(cv_img):
        if confidence > 0.7:  # 若置信度大于0.7，则识别结果可信(最大为1)
            image = drawRectBox(cv_img, rect, pstr + " " +
                                str(round(confidence, 3)))
            # 在Entry显示数据
            plate_entry.delete(0, tk.END)
            confidence_entry.delete(0, tk.END)
            plate_entry.insert(0, pstr)
            confidence_entry.insert(0, confidence)
            # 数据库
            sql = "SELECT car_id,username,phone,addr,ctime FROM Car WHERE car_id='%s'" % (
                pstr)
            try:
                cursor.execute(sql)
                u_get = cursor.fetchall()
                # 如果查询到数据
                if u_get:
                    usermane = str(u_get[0][1])
                    phone = str(u_get[0][2])
                    addr = str(u_get[0][3])
                    ctime = str(u_get[0][4])
                    # 显示数据
                    data_text.delete(1.0, tk.END)
                    data_str = "车牌号：\n  "+pstr + "\n\n车主：\n  "+usermane + \
                        "\n\n电话：\n  "+phone+"\n\n地址：\n  "+addr+"\n\n注册时间：\n  "+ctime
                    data_text.insert(tk.INSERT, data_str)

                    canvas_img = ImageTk.PhotoImage(
                        image=Image.fromarray(image))
                    canvas.create_image(0, 0, image=canvas_img, anchor=tk.NW)
                    canvas.update()

                    # 插入信息记录表
                    order_time = str(datetime.date.today())
                    sql = "INSERT INTO Info(order_id, car_id, status, order_time) VALUES (NULL, '%s', %s, '%s')" % \
                        (pstr, '1', order_time)
                    try:
                        cursor.execute(sql)
                        # 提交到数据库执行
                        db.commit()
                        showinfo(title="成功", message="成功，请进入")  # 弹出信息框
                    except:
                        # 如果发生错误则回滚
                        db.rollback()
                        showinfo(title="失败", message="录入信息失败")  # 弹出信息框

                else:
                    # 不在库中
                    showinfo(title="失败", message="非本小区车辆")  # 弹出信息框

            except:
                print("Error: unable to fecth data")


# 控件
load_file_button = ttk.Button(window, text="读取文件", width=8, command=load_file)
run_button = ttk.Button(window, text="识别", width=8, command=run)
xbar = ttk.Scrollbar(frame, orient=tk.HORIZONTAL)
ybar = ttk.Scrollbar(frame, orient=tk.VERTICAL)

# 显示控件
load_file_button.grid(row=0, column=0)
run_button.grid(row=1, column=0)
plate_lable.grid(row=2, column=0)
plate_entry.grid(row=3, column=0)
confidence_lable.grid(row=4, column=0)
confidence_entry.grid(row=5, column=0)
data_text.grid(row=6, column=0)
frame.grid(row=0, column=1, rowspan=8)
xbar.pack(side=tk.BOTTOM, fill=tk.X)
xbar.config(command=canvas.xview)
ybar.pack(side=tk.RIGHT, fill=tk.Y)
ybar.config(command=canvas.yview)
canvas.config(width=800, height=600)
canvas.config(yscrollcommand=ybar.set)
canvas.config(xscrollcommand=xbar.set)
canvas.pack(side=tk.LEFT, expand=True, fill=tk.BOTH)

# 运行
window.mainloop()
