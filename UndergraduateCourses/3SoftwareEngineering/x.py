from tkinter import *
import cv2


class login_page:
    def __init__(self, master=None):
        '''初始化'''
        self.master = master
        self.create_widgets()

    def create_widgets(self):
        '''创建控件'''
        self.canvas = Canvas(self.master, width=500, height=228)
        self.image_file = PhotoImage(file='x.png')
        self.canvas.create_image(250, 0, anchor='n', image=self.image_file)
        self.label_u = Label(self.master, text="用户名：")
        self.entry_u = Entry(self.master)
        self.label_p = Label(self.master, text="密  码：")
        self.entry_p = Entry(self.master)
        self.btn_login = Button(self.master,
                                text="登录",
                                width=12,
                                command=self.login)
        self.btn_logup = Button(self.master,
                                text="注册",
                                width=12,
                                command=self.logup)

        self.canvas.grid(row=0, column=0, columnspan=2)
        self.label_u.grid(row=1, column=0, columnspan=1)
        self.entry_u.grid(row=1, column=1, columnspan=1)
        self.label_p.grid(row=2, column=0, columnspan=1)
        self.entry_p.grid(row=2, column=1, columnspan=1)
        self.btn_login.grid(row=3, column=0, columnspan=2)
        self.btn_logup.grid(row=4, column=0, columnspan=2)

    def login(self):
        '''登录'''
        pass

    def logup(self):
        '''注册'''
        pass


class run_page:
    def __init__(self, master=None):
        '''初始化'''
        self.master = master
        self.create_widgets()

    def create_widgets(self):
        '''创建控件'''
        self.canvas = Canvas(self.master, width=500, height=228)
        self.image_file = PhotoImage(file='x.png')
        self.canvas.create_image(250, 0, anchor='n', image=self.image_file)
        self.btn_start = Button(self.master,
                                text="开始运行",
                                width=12,
                                command=self.start)
        self.btn_end = Button(self.master,
                              text="停止运行",
                              width=12,
                              command=self.end)
        self.btn_mix = Button(self.master,
                              text="仪器修正",
                              width=12,
                              command=self.mix)
        self.btn_now = Button(self.master,
                              text="当前基本数据",
                              width=12,
                              command=self.mix)
        self.btn_compare = Button(self.master,
                                  text="历史数据对比",
                                  width=12,
                                  command=self.mix)

        self.canvas.grid(row=0, column=0, columnspan=2)
        self.btn_start.grid(row=1, column=0, columnspan=1)
        self.btn_end.grid(row=2, column=0, columnspan=1)
        self.btn_mix.grid(row=3, column=0, columnspan=1)
        self.btn_now.grid(row=1, column=1, columnspan=1)
        self.btn_compare.grid(row=2, column=1, columnspan=1)

    def start(self):
        # 读取图像
        img = cv2.imread('a.jpg')
        cv2.imshow('img', img)
        # cv2.imwrite('x.jpg',img)

        # 转换为灰度图
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        cv2.imshow('gray_img', gray)

        # Canny算子求边界
        caimg = cv2.Canny(gray, 200, 300)
        cv2.imshow('Canny', caimg)

        # 旋转图像
        (h, w) = caimg.shape[:2]
        center = (w // 2, h // 2)
        M = cv2.getRotationMatrix2D(center, -20.5, 1)
        rotated_ca = cv2.warpAffine(caimg, M, (w, h))
        cv2.imshow('rotate_Canny', rotated_ca)
        (h, w) = img.shape[:2]
        center = (w // 2, h // 2)
        M = cv2.getRotationMatrix2D(center, -20.5, 1)
        rotated_img = cv2.warpAffine(img, M, (w, h))
        cv2.imshow('rotate', rotated_img)

        cv2.waitKey()

    def end(self):
        pass

    def mix(self):
        pass

    def now(self):
        pass

    def compare(self):
        pass


window = Tk()
window.title("二次压降检测系统")
window.geometry("502x350")
# login_page(window)
run_page(window)
window.mainloop()
