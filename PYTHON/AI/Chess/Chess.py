from tkinter import *
from tkinter.messagebox import *
from AI_2 import ChessAI
import time
import copy


class chess_app:
    def __init__(self, master=None):
        '''初始化'''
        self.master = master
        self.N = 15  #五子棋盘一行的点数
        self.ai = ChessAI(self.N)
        self.radius = 14  #棋子的半径
        self.no = 0  #无棋
        self.black = 1  #黑棋
        self.white = 2  #白棋
        self.block_size = 32  #块的间距
        self.chess_map = [[self.no] * self.N for i in range(self.N)]  #下棋情况存储
        self.now_chess = self.black  #当前行走的
        self.win = False  #当前棋盘胜利过的标志
        self.human_mod = 0  #人人模式
        self.ai_mod = 1  #人机模式
        self.mod = self.human_mod  #当前运行模式标志
        self.is_ai = False  #判断当前走棋是不是AI
        self.create_widgets()
        self.create_chess_map()

    def create_widgets(self):
        '''创建控件'''
        self.canvas = Canvas(self.master)
        self.canvas.config(width=512, height=512, bg="BurlyWood")
        self.canvas.bind("<Button-1>", self.clicked)  #点击响应
        self.label_nowchess = Label(self.master, text="当前棋子：黑色")
        self.btn_human = Button(self.master,
                                text="双人游戏",
                                width=12,
                                command=self.human)
        self.btn_ai_pre = Button(self.master,
                                 text="人机对战（先）",
                                 width=12,
                                 command=self.ai_pre)
        self.btn_ai_after = Button(self.master,
                                   text="人机对战（后）",
                                   width=12,
                                   command=self.ai_after)

        self.canvas.grid(row=0, column=0, columnspan=4)
        self.label_nowchess.grid(row=1, column=0, columnspan=1)
        self.btn_human.grid(row=1, column=1, columnspan=1)
        self.btn_ai_pre.grid(row=1, column=2, columnspan=1)
        self.btn_ai_after.grid(row=1, column=3, columnspan=1)

    def create_chess_map(self):
        '''画棋盘'''
        # 横线
        x = self.block_size
        y = self.block_size
        for i in range(self.N):
            point1 = [x, y]
            point2 = [x + self.block_size * (self.N - 1), y]
            self.canvas.create_line(point1 + point2,
                                    width=2,
                                    fill='black',
                                    tags="line")
            y += self.block_size
        # 竖线
        x = self.block_size
        y = self.block_size
        for i in range(self.N):
            point1 = [x, y]
            point2 = [x, y + self.block_size * (self.N - 1)]
            self.canvas.create_line(point1 + point2,
                                    width=2,
                                    fill='black',
                                    tags="line")
            x += self.block_size
        # 标记点
        r = 5  #标记点的半径
        four_p = 3  #四个外点离边线的格数
        center_p = 8  #中心点离边线的格数
        c = center_p * self.block_size
        point1 = [c - r, c - r]
        point2 = [c + r, c + r]
        self.canvas.create_oval(point1 + point2, fill='black', tags="oval")
        z = [(self.block_size + four_p * self.block_size,
              self.block_size + four_p * self.block_size),
             (self.block_size * (self.N) - four_p * self.block_size,
              self.block_size + four_p * self.block_size),
             (self.block_size + four_p * self.block_size,
              self.block_size * (self.N) - four_p * self.block_size),
             (self.block_size * (self.N) - four_p * self.block_size,
              self.block_size * (self.N) - four_p * self.block_size)]
        for i in z:
            point1 = [i[0] - r, i[1] - r]
            point2 = [i[0] + r, i[1] + r]
            self.canvas.create_oval(point1 + point2, fill='black', tags="oval")
        self.master.update_idletasks()

    def create_black(self, p):
        '''画黑棋'''
        self.chess_map[p[0]][p[1]] = self.black
        point = [
            p[0] * self.block_size + self.block_size,
            p[1] * self.block_size + self.block_size
        ]
        point1 = [point[0] - self.radius, point[1] - self.radius]
        point2 = [point[0] + self.radius, point[1] + self.radius]
        self.canvas.create_oval(point1 + point2, fill='black', tags="chess")

    def create_white(self, p):
        '''画白棋'''
        self.chess_map[p[0]][p[1]] = self.white
        point = [
            p[0] * self.block_size + self.block_size,
            p[1] * self.block_size + self.block_size
        ]
        point1 = [point[0] - self.radius, point[1] - self.radius]
        point2 = [point[0] + self.radius, point[1] + self.radius]
        self.canvas.create_oval(point1 + point2,
                                fill='white',
                                outline='white',
                                tags="chess")

    def mark_lastchess(self, p):
        '''标记最后一个走的棋子'''
        self.canvas.delete("mark")
        point = [
            p[0] * self.block_size + self.block_size,
            p[1] * self.block_size + self.block_size
        ]
        point1 = [point[0] - self.radius, point[1] - self.radius]
        point2 = [point[0] + self.radius, point[1] + self.radius]
        self.canvas.create_rectangle(point1 + point2,
                                     fill='',
                                     outline='gray',
                                     tags="mark")

    def judge(self, judge_chess=0):
        if judge_chess == 0:
            judge_chess = self.now_chess
        '''判断有没有胜利'''
        for i in range(self.N):
            for j in range(self.N):
                if self.chess_map[i][j] == judge_chess:  #遇到刚走的旗色
                    # 判断竖线有没有成5子
                    flag = True
                    for jj in range(j + 1, j + 5):  #遍历接下来5个
                        if jj >= self.N or self.chess_map[i][jj] != judge_chess:
                            flag = False
                        if jj == j + 4 and flag:
                            return True
                    # 判断横线有没有成5子
                    flag = True
                    for ii in range(i + 1, i + 5):  #遍历接下来5个
                        if ii >= self.N or self.chess_map[ii][j] != judge_chess:
                            flag = False
                        if ii == i + 4 and flag:
                            return True
                    # 判断右下方斜线有没有成5子
                    flag = True
                    ii = i + 1
                    jj = j + 1
                    for x in range(4):
                        if ii >= self.N or jj >= self.N or self.chess_map[ii][
                                jj] != judge_chess:
                            flag = False
                        if ii == i + 4 and flag:
                            return True
                        ii += 1
                        jj += 1
                    # 判断右上方斜线有没有成5子
                    flag = True
                    ii = i + 1
                    jj = j - 1
                    for x in range(4):
                        if ii >= self.N or jj < 0 or self.chess_map[ii][
                                jj] != judge_chess:
                            flag = False
                        if ii == i + 4 and flag:
                            return True
                        ii += 1
                        jj -= 1
        return False

    def clicked(self, event):
        '''点击事件'''
        if self.win or self.is_ai:
            return
        x = event.x  #当前鼠标所在坐标x
        y = event.y  #当前鼠标所在坐标y
        low = self.block_size // 2  #棋盘边界下届
        high = self.block_size * self.N + self.block_size // 2  #棋盘边界上届

        if x > low and x < high and y > low and y < high:  #在边界内
            x_num = int(x / self.block_size - 0.5)  #离鼠标最近的棋盘上的点x
            y_num = int(y / self.block_size - 0.5)  #离鼠标最近的棋盘上的点y
            if self.chess_map[x_num][y_num] == self.no:  #该点没有棋子
                if self.now_chess == self.black:  #当前为黑棋
                    p = [x_num, y_num]
                    print(p)
                    self.mark_lastchess(p)  #标记当前棋子位置
                    self.create_black(p)  #画出棋子
                    window.update_idletasks()
                    if self.judge():  #成功，结束
                        info = "黑棋胜利！"
                        showinfo(title="信息", message=info)  #弹出信息框
                        self.win = True
                        return
                    if self.mod == self.human_mod:  #人人模式
                        self.now_chess = self.white
                        self.label_nowchess.config(text="当前棋子：白色")
                    else:  #人机模式
                        self.is_ai = True
                        self.ai_move()
                        self.is_ai = False
                else:  #当前为白棋
                    p = [x_num, y_num]
                    self.mark_lastchess(p)  #标记当前棋子位置
                    self.create_white(p)  #画出棋子
                    window.update_idletasks()
                    if self.judge():  #成功，结束
                        info = "白棋胜利！"
                        showinfo(title="信息", message=info)  #弹出信息框
                        self.win = True
                        return
                    if self.mod == self.human_mod:  #人人模式
                        self.now_chess = self.black
                        self.label_nowchess.config(text="当前棋子：黑色")
                    else:  #人机模式
                        self.is_ai = True
                        self.ai_move()
                        self.is_ai = False

    def transpose(self, matrix):
        new_matrix = []
        for i in range(len(matrix[0])):
            matrix1 = []
            for j in range(len(matrix)):
                matrix1.append(matrix[j][i])
            new_matrix.append(matrix1)
        return new_matrix

    def ai_move(self):
        '''AI移动'''
        if self.now_chess == self.black:  #用户为黑，AI为白
            map_ = copy.deepcopy(self.chess_map)
            map_ = self.transpose(map_)
            p = self.ai.findBestChess(map_, self.black)
            self.mark_lastchess(p)  #标记当前棋子位置
            self.create_white(p)  #画出棋子
            window.update_idletasks()
            if self.judge(self.white):  #成功，结束
                info = "白棋胜利！"
                showinfo(title="信息", message=info)  #弹出信息框
                self.win = True
                return
        else:  #用户为白，AI为黑
            map_ = copy.deepcopy(self.chess_map)
            map_ = self.transpose(map_)
            p = self.ai.findBestChess(map_, self.white)
            self.mark_lastchess(p)  #标记当前棋子位置
            self.create_black(p)  #画出棋子
            window.update_idletasks()
            if self.judge(self.black):  #成功，结束
                info = "黑棋胜利！"
                showinfo(title="信息", message=info)  #弹出信息框
                self.win = True
                return

    def human(self):
        '''双人游戏'''
        self.mod = self.human_mod
        self.chess_map = [[self.no] * self.N for i in range(self.N)]  #下棋情况存储
        self.now_chess = self.black  #当前行走的
        self.win = False
        self.label_nowchess.config(text="当前棋子：黑色")
        self.canvas.delete("chess", "mark")  #清空画布

    def ai_pre(self):
        '''人机对战 先手'''
        self.mod = self.ai_mod
        self.chess_map = [[self.no] * self.N for i in range(self.N)]  #下棋情况存储
        self.now_chess = self.black  #当前行走的
        self.win = False
        self.is_ai = False  #判断当前走棋是不是AI
        self.label_nowchess.config(text="当前棋子：黑色")
        self.canvas.delete("chess", "mark")  #清空画布

    def ai_after(self):
        '''人机对战 后手'''
        self.mod = self.ai_mod
        self.chess_map = [[self.no] * self.N for i in range(self.N)]  #下棋情况存储
        self.now_chess = self.white  #当前行走的
        self.win = False
        self.is_ai = False  #判断当前走棋是不是AI
        self.label_nowchess.config(text="当前棋子：白色")
        self.canvas.delete("chess", "mark")  #清空画布
        # 画第一步黑棋到中心
        self.chess_map[7][7] = self.black  #第一步走中点
        point = [7, 7]
        self.mark_lastchess(point)  #标记当前棋子位置
        self.create_black(point)  #画出棋子


window = Tk()
window.title("五子棋")
window.geometry("512x550")
app = chess_app(window)
window.mainloop()
