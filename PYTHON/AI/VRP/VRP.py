# 题目：VRP
# 作者：李延炽
# 时间：

from tkinter import *
from tkinter.messagebox import *
from functools import cmp_to_key
import time
import copy

#全局变量
time_wait = 0.5  #每动态访问一个路径的时间间隔
N = 0  #节点个数
MIN = 0  #路径最小值
MAX = 1000  #路径最大值
Founation = [  #启发函数
    366, 0, 160, 242, 161, 176, 77, 151, 226, 244, 241, 234, 380, 100, 193,
    253, 329, 80, 199, 374
]
Nation = [  #节点名
    '武汉大学', '华中师范大学', '武汉理工大学', '华中农业大学', '中国地质大学', '中南民族大学', '中南财经政法大学',
    '华中科技大学'
]

Nation_point = [[637, 159], [465, 683], [199, 671], [455, 1213], [1135, 461],
                [1015, 1009], [919, 1189], [1231, 613]]
Graph = []  #图的临接矩阵
Canvas_point = []  #画布上点的句柄存储
Canvas_line = []  #画布上线的句柄存储(按照邻接矩阵)
Canvas_line_list = []  #画布上线的句柄存储(按照顺序)

#读取文件到图的邻接矩阵
with open('data.txt', 'r') as of:
    for line in of:
        line = line.replace('\n', '')
        linestr = line.split(',')
        Graph.append(linestr)
N = len(Graph[0])
Canvas_line = copy.deepcopy(Graph)


#处理函数
def clear():
    '''清屏'''
    #线
    for i in Canvas_line_list:
        canvas.itemconfig(i, fill='white')
    #圆
    for i in Canvas_point:
        canvas.itemconfig(i, fill='white')


def BFS():
    '''广度优先'''
    clear()

    #获取输入框的信息
    get_start_name = start_entry.get()
    get_end_name = end_entry.get()
    if get_end_name not in Nation or get_end_name not in Nation:
        showinfo(title="错误", message="请输入正确的起始点和结束点")
        return
    Start = Nation.index(get_start_name)
    End = Nation.index(get_end_name)

    #初始点和结束点颜色变化
    canvas.itemconfig(Canvas_point[Start], fill='yellow')
    canvas.itemconfig(Canvas_point[End], fill='yellow')
    window.update_idletasks()
    time.sleep(time_wait)

    father = [-1 for i in range(0, N)]  #记录每个城市的“父节点”的位置
    seek = [False for i in range(0, N)]  #记录此节点是否访问过，访问过就设置成true
    openList = []  #Open表，保存将要访问的节点，这里使用队列
    count = 0  #计数

    #开始计时
    start = time.time()

    #初始点加入
    openList.append(Start)
    seek[Start] = True

    #循环查找路径
    f_x = Start
    while openList:
        x = openList.pop(0)  #队列方法
        count += 1

        #路过的节点和路径颜色变化
        if x != End and x != Start:
            canvas.itemconfig(Canvas_point[x], fill='blue')
        if father[x] != -1:
            f_x = father[x]
        canvas.itemconfig(Canvas_line[f_x][x], fill='blue')
        window.update_idletasks()
        time.sleep(time_wait)

        if x == End:
            break
        for i in range(0, N):
            if int(Graph[x][i]) > MIN and int(
                    Graph[x][i]) < MAX and seek[i] == False:
                openList.append(i)
                father[i] = x
                seek[i] = True

    #结束计时
    end = time.time()

    #结果显示
    cost = 0
    road = []
    x = End
    while True:
        cost += int(Graph[x][father[x]])
        road.append(x)
        old_x = x
        x = father[x]

        #输出结果路径和点
        canvas.itemconfig(Canvas_point[old_x], fill='yellow')
        canvas.itemconfig(Canvas_point[x], fill='yellow')
        canvas.itemconfig(Canvas_line[old_x][x], fill='yellow')

        if x == Start:
            road.append(x)
            break

    #弹出提示框显示信息
    window.update_idletasks()
    info = "总访问节点数：" + str(count) + "\n最短路径节点数：" + str(
        len(road)) + "\n最短路径长度：" + str(cost) + "\n运行时间：" + str(
            (end - start)) + " s"
    showinfo(title="信息", message=info)


def DFS():
    '''深度优先'''
    clear()

    #获取输入框的信息
    get_start_name = start_entry.get()
    get_end_name = end_entry.get()
    if get_end_name not in Nation or get_end_name not in Nation:
        showinfo(title="错误", message="请输入正确的起始点和结束点")
        return
    Start = Nation.index(get_start_name)
    End = Nation.index(get_end_name)

    #初始点和结束点颜色变化
    canvas.itemconfig(Canvas_point[Start], fill='yellow')
    canvas.itemconfig(Canvas_point[End], fill='yellow')
    window.update_idletasks()
    time.sleep(time_wait)

    father = [-1 for i in range(0, N)]  #记录每个城市的“父节点”的位置
    from_to = [[False] * N for i in range(0, N)]
    openList = []  #Open表，保存将要访问的节点，这里使用栈
    count = 0  #计数

    #开始计时
    start = time.time()

    #初始点加入
    openList.append(Start)

    #循环查找路径
    f_x = Start
    while openList:
        x = openList.pop()  #栈方法
        count += 1

        #路过的节点和路径颜色变化
        if x != End and x != Start:
            canvas.itemconfig(Canvas_point[x], fill='blue')
        if father[x] != -1:
            f_x = father[x]
        canvas.itemconfig(Canvas_line[f_x][x], fill='blue')
        window.update_idletasks()
        time.sleep(time_wait)

        if (x == End):
            break
        for i in range(N - 1, -1, -1):
            if int(Graph[x][i]) > MIN and int(
                    Graph[x][i]) < MAX and from_to[x][i] == False:
                openList.append(i)
                father[i] = x
                from_to[x][i] = True
                from_to[i][x] = True

    #结束计时
    end = time.time()

    #结果显示
    cost = 0
    road = []
    x = End
    while True:
        cost += int(Graph[x][father[x]])
        road.append(x)
        old_x = x
        x = father[x]

        #输出结果路径和点
        canvas.itemconfig(Canvas_point[old_x], fill='yellow')
        canvas.itemconfig(Canvas_point[x], fill='yellow')
        canvas.itemconfig(Canvas_line[old_x][x], fill='yellow')

        if x == Start:
            road.append(x)
            break
    #弹出提示框显示信息
    window.update_idletasks()
    info = "总访问节点数：" + str(count) + "\n最短路径节点数：" + str(
        len(road)) + "\n最短路径长度：" + str(cost) + "\n运行时间：" + str(
            (end - start)) + " s"
    showinfo(title="信息", message=info)


def Greedy():
    '''贪婪算法'''
    clear()

    #获取输入框的信息
    get_start_name = start_entry.get()
    get_end_name = end_entry.get()
    if get_end_name not in Nation or get_end_name not in Nation:
        showinfo(title="错误", message="请输入正确的起始点和结束点")
        return
    Start = Nation.index(get_start_name)
    End = Nation.index(get_end_name)

    #初始点和结束点颜色变化
    canvas.itemconfig(Canvas_point[Start], fill='yellow')
    canvas.itemconfig(Canvas_point[End], fill='yellow')
    window.update_idletasks()
    time.sleep(time_wait)

    father = [-1 for i in range(0, N)]  #记录每个城市的“父节点”的位置
    seek = [[False] * N for i in range(0, N)]  #记录此节点是否访问过，访问过就设置成true
    openList = []  #Open表，保存将要访问的节点，这里使用队列方法
    count = 0  #计数

    #开始计时
    start = time.time()

    def f(a, b):
        return int(Graph[Start][a]) - int(Graph[Start][b])

    #初始点加入
    for i in range(0, N):
        if int(Graph[Start][i]) > MIN and int(
                Graph[Start][i]) < MAX and seek[Start][i] == False:
            openList.append(i)
            seek[Start][i] = True
            seek[i][Start] = True
            father[i] = Start
    openList.sort(key=cmp_to_key(f))
    count += 1

    def Find_next(x, seek):
        '''查找当前点距离最近的点'''
        nextList = []
        for i in range(0, N):
            if int(Graph[x][i]) > MIN and int(
                    Graph[x][i]) < MAX and seek[x][i] == False:
                nextList.append(i)
                seek[x][i] = True
                seek[i][x] = True
        if not nextList:
            return -1
        min_x = nextList[0]
        for i in nextList:
            if int(Graph[x][i]) < int(Graph[x][min_x]):
                min_x = i
        return min_x

    #循环查找路径
    flag = False
    while openList:
        count += 1
        x = openList.pop(0)

        #路过的节点和路径颜色变化
        if i != End:
            canvas.itemconfig(Canvas_point[x], fill='blue')
        canvas.itemconfig(Canvas_line[Start][x], fill='blue')
        window.update_idletasks()
        time.sleep(time_wait)

        t = Find_next(x, seek)
        while t != -1:
            if x == End:
                flag = True
                break
            count += 1

            #路过的节点和路径颜色变化
            if t != End:
                canvas.itemconfig(Canvas_point[t], fill='blue')
            canvas.itemconfig(Canvas_line[x][t], fill='blue')
            window.update_idletasks()
            time.sleep(time_wait)

            father[t] = x
            x = t
            t = Find_next(x, seek)
        if flag == True:
            break

    #结束计时
    end = time.time()

    #结果显示
    cost = 0
    road = []
    x = End
    while True:
        cost += int(Graph[x][father[x]])
        road.append(x)
        old_x = x
        x = father[x]
        if (x == -1):  #没搜索到点，失败
            showinfo(title="信息", message="贪婪算法搜索不到，失败！")
            return

        #输出结果路径和点
        canvas.itemconfig(Canvas_point[old_x], fill='yellow')
        canvas.itemconfig(Canvas_point[x], fill='yellow')
        canvas.itemconfig(Canvas_line[old_x][x], fill='yellow')

        if x == Start:
            road.append(x)
            break
    #弹出提示框显示信息
    window.update_idletasks()
    info = "总访问节点数：" + str(count) + "\n最短路径节点数：" + str(
        len(road)) + "\n最短路径长度：" + str(cost) + "\n运行时间：" + str(
            (end - start)) + " s"
    showinfo(title="信息", message=info)


def Astar():
    '''A*算法'''
    clear()

    #获取输入框的信息
    get_start_name = start_entry.get()
    get_end_name = end_entry.get()
    if get_end_name not in Nation or get_end_name not in Nation:
        showinfo(title="错误", message="请输入正确的起始点和结束点")
        return
    Start = Nation.index(get_start_name)
    End = Nation.index(get_end_name)

    #初始点和结束点颜色变化
    canvas.itemconfig(Canvas_point[Start], fill='yellow')
    canvas.itemconfig(Canvas_point[End], fill='yellow')
    window.update_idletasks()
    time.sleep(time_wait)

    father = [-1 for i in range(0, N)]  #记录每个城市的“父节点”的位置
    seek = [False for i in range(0, N)]  #记录此节点是否访问过，访问过就设置成true
    openList = []  #Open表，保存将要访问的节点，此处使用队列
    count = 0  #计数

    class Data:
        '''节点'''
        location = 0
        cost = 0

        def __init__(self, lo, co):
            self.location = lo
            self.cost = co

    def f(a, b):
        return a.cost - b.cost

    #开始计时
    start = time.time()

    #初始点加入
    openList.append(Data(Start, Founation[Start]))
    seek[Start] = True

    #循环查找路径
    f_x = Start
    while openList:
        openList.sort(key=cmp_to_key(f))
        x = openList.pop(0)  #队列方法
        count += 1

        #路过的节点和路径颜色变化
        if x.location != End and x.location != Start:
            canvas.itemconfig(Canvas_point[x.location], fill='blue')
        if father[x.location] != -1:
            f_x = father[x.location]
        canvas.itemconfig(Canvas_line[f_x][x.location], fill='blue')
        window.update_idletasks()
        time.sleep(time_wait)

        if (x.location == End):
            break
        for i in range(0, N):
            if int(Graph[x.location][i]) > MIN and int(
                    Graph[x.location][i]) < MAX and seek[i] == False:
                openList.append(
                    Data(i,
                         int(Graph[x.location][i]) + int(Founation[i])))
                father[i] = x.location
                seek[i] = True

    #结束计时
    end = time.time()

    #结果显示
    cost = 0
    road = []
    x = End
    while True:
        cost += int(Graph[x][father[x]])
        road.append(int(x))
        old_x = x
        x = father[x]

        #输出结果路径和点
        canvas.itemconfig(Canvas_point[old_x], fill='yellow')
        canvas.itemconfig(Canvas_point[x], fill='yellow')
        canvas.itemconfig(Canvas_line[old_x][x], fill='yellow')

        if x == Start:
            road.append(x)
            break
    #弹出提示框显示信息
    window.update_idletasks()
    info = "总访问节点数：" + str(count) + "\n最短路径节点数：" + str(
        len(road)) + "\n最短路径长度：" + str(cost) + "\n运行时间：" + str(
            (end - start)) + " s"
    showinfo(title="信息", message=info)


#GUI窗口
window = Tk()
window.title("光谷地区高校VRP问题Demo")

frame = Frame(window)

#画布
canvas = Canvas(frame, scrollregion=(0, 0, 1600, 1280))
xbar = Scrollbar(frame, orient=HORIZONTAL)
ybar = Scrollbar(frame, orient=VERTICAL)
#导入图片到画布
image_file = PhotoImage(file='graph.png')
image = canvas.create_image(0, 0, anchor='nw', image=image_file)
#画布上标记线
for i in range(0, N):
    for j in range(i + 1, N):
        if int(Graph[i][j]) > MIN and int(Graph[i][j]) < MAX:
            cl = canvas.create_line(Nation_point[i] + Nation_point[j],
                                    width=4,
                                    fill='white')
            Canvas_line[i][j] = cl
            Canvas_line[j][i] = cl
            Canvas_line_list.append(cl)
#画布上标记圆
for i in Nation_point:
    cp = canvas.create_oval([ii - 8 for ii in i] + [ii + 8 for ii in i],
                            fill='white')
    Canvas_point.append(cp)

empty_label_1 = Label(window, text=' ')
empty_label_2 = Label(window, text=' ')
start_label = Label(window, text='开始点：')
end_label = Label(window, text='结束点：')
start_entry = Entry(window, width=30)
start_entry.insert(END, "中国地质大学")
end_entry = Entry(window, width=30)
end_entry.insert(END, "华中农业大学")
BFS_button = Button(window, text="广度优先", width=20, command=BFS)
DFS_button = Button(window, text="深度优先", width=20, command=DFS)
Greedy_button = Button(window, text="贪婪算法", width=20, command=Greedy)
Astar_button = Button(window, text="A*算法", width=20, command=Astar)

#显示控件
frame.grid(row=0, column=0, columnspan=7)
xbar.pack(side=BOTTOM, fill=X)
xbar.config(command=canvas.xview)
ybar.pack(side=RIGHT, fill=Y)
ybar.config(command=canvas.yview)
canvas.config(width=1000, height=700)
canvas.config(yscrollcommand=ybar.set)
canvas.pack(side=LEFT, expand=True, fill=BOTH)
empty_label_1.grid(row=1, column=0)
empty_label_2.grid(row=2, column=0)
start_label.grid(row=1, column=1)
end_label.grid(row=2, column=1)
start_entry.grid(row=1, column=2)
end_entry.grid(row=2, column=2)
BFS_button.grid(row=1, column=3, rowspan=2)
DFS_button.grid(row=1, column=4, rowspan=2)
Greedy_button.grid(row=1, column=5, rowspan=2)
Astar_button.grid(row=1, column=6, rowspan=2)

#运行
window.mainloop()
