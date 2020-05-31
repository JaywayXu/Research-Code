from tkinter import *
from tkinter.messagebox import *
import random
import copy
import time
import math

# 全局变量
N = 8  #棋盘、皇后数量
Queen = [0 for i in range(N)]  #皇后位置
one_block_size = 21  #棋盘每个格的像素宽度

# 回溯法全局变量
count_sum = 0  #所有情况统计计数
back_blok_size = 10  #棋盘每个格的像素宽度
every_size = back_blok_size * (N + 1)  #每个棋盘的距离
x = back_blok_size  #第一个棋盘的x坐标
y = back_blok_size  #第一个棋盘的y坐标
count_x = 0  #每行棋盘计数
max_x = 10  #每行棋盘数
is_success_back = False  #只输出一种情况的成功判断条件
Queen_succ = [0 for i in range(N)]

# 遗传算法全局变量
group_num = 100  #种群中个体的个数
population = []  #种群
adaptive = []  #种群的适应值
max_iter_genetic = 2000  #迭代最大次数
count_genetic = 0  #迭代次数计数
is_success_genetic = False  #遗传算法是否成功

# 模拟退火算法全局变量
max_temperature = 5  #初始温度
nt_multiple = 0.98  #一次迭代降低的温度倍数
min_temperature = 1e-200  #结束温度
temperature = max_temperature
is_success_anneal = False  #模拟退火算法是否成功

# 爬山法全局变量
max_iter_climb = 100  #迭代最大次数
is_success_climb = False  #爬山法是否成功

# 算法比较全局变量
compare_times = 10  #每种算法测试次数
compare_min = 4  #皇后数量区间的最小
compare_max = 15  #皇后数量区间的最大
count_climb = 0  #迭代次数计数


# 全局函数
def print_one_canvas(Queen):
    '''画布打印一个棋盘'''
    # 棋盘外框横线
    x = one_block_size
    y = one_block_size
    point1 = [x, y]
    point2 = [x, y + one_block_size * N]
    canvas.create_line(point1 + point2, width=1, fill='black', tags="line")
    point1 = [x + one_block_size * N, y]
    point2 = [x + one_block_size * N, y + one_block_size * N]
    canvas.create_line(point1 + point2, width=1, fill='black', tags="line")
    # 棋盘外框竖线
    x = one_block_size
    y = one_block_size
    point1 = [x, y]
    point2 = [x + one_block_size * N, y]
    canvas.create_line(point1 + point2, width=1, fill='black', tags="line")
    point1 = [x, y + one_block_size * N]
    point2 = [x + one_block_size * N, y + one_block_size * N]
    canvas.create_line(point1 + point2, width=1, fill='black', tags="line")
    # 黑块填充
    x = one_block_size
    y = one_block_size
    for i in range(N):
        for j in range(N):
            if (i + j) % 2 == 0:  #涂黑块
                point1 = [x + i * one_block_size, y + j * one_block_size]
                point2 = [
                    x + (i + 1) * one_block_size, y + (j + 1) * one_block_size
                ]
                canvas.create_rectangle(point1 + point2,
                                        fill='black',
                                        tags="rectangle")
    # 棋子
    for i in range(N):
        x = one_block_size + Queen[i] * one_block_size
        y = one_block_size + i * one_block_size
        point1 = [x + 2, y + 2]
        point2 = [x + one_block_size - 2, y + one_block_size - 2]
        canvas.create_oval(point1 + point2, fill='black', tags="oval")
        canvas.create_image(x + 1,
                            y + 1,
                            anchor='nw',
                            image=image_queen,
                            tags="oval")

    window.update_idletasks()  #屏幕刷新


# 回溯法函数
def back_print_every_canvas(A, point):
    '''回溯法 画布打印'''
    # 棋盘横线
    x = point[0]
    y = point[1]
    for i in range(N + 1):
        point1 = [x, y]
        point2 = [x, y + back_blok_size * N]
        canvas.create_line(point1 + point2, width=1, fill='black', tags="line")
        x += back_blok_size
    # 棋盘竖线
    x = point[0]
    y = point[1]
    for i in range(N + 1):
        point1 = [x, y]
        point2 = [x + back_blok_size * N, y]
        canvas.create_line(point1 + point2, width=1, fill='black', tags="line")
        y += back_blok_size
    # 黑块填充
    x = point[0]
    y = point[1]
    for i in range(N):
        for j in range(N):
            if (i + j) % 2 == 0:  #涂黑块
                point1 = [x + i * back_blok_size, y + j * back_blok_size]
                point2 = [
                    x + (i + 1) * back_blok_size, y + (j + 1) * back_blok_size
                ]
                canvas.create_rectangle(point1 + point2,
                                        fill='black',
                                        tags="rectangle")
    # 棋子
    for i in range(N):
        x = point[0] + A[i] * back_blok_size
        y = point[1] + i * back_blok_size
        point1 = [x + 2, y + 2]
        point2 = [x + back_blok_size - 2, y + back_blok_size - 2]
        if (A[i] + i) % 2 == 0:  #遇到黑块
            out_color = 'white'
        else:
            out_color = 'black'
        canvas.create_oval(point1 + point2,
                           fill='gray',
                           outline=out_color,
                           tags="oval")
    window.update_idletasks()  #窗口刷新


def back_reset():
    '''回溯法 初始化'''
    global Queen, count_sum, back_blok_size, every_size, x, y, count_x, is_success_back
    is_success_back = False  #只输出一种情况的成功判断条件
    Queen = [0 for i in range(N)]  #皇后位置
    count_sum = 0  #所有情况统计计数
    back_blok_size = 10  #棋盘每个格的像素宽度
    every_size = back_blok_size * (N + 1)  #每个棋盘的距离
    x = back_blok_size  #第一个棋盘的x坐标
    y = back_blok_size  #第一个棋盘的y坐标
    count_x = 0  #每行棋盘计数
    canvas.delete("oval", "line", "rectangle")  #清空画布
    window.update_idletasks()  #窗口刷新


def back_recursive(cur=0):
    '''回溯法 递归子程序'''
    global x, y, count_x, count_sum, Queen
    if cur == len(Queen):  #满足要求并打印
        if count_x >= max_x:  #判断每行有没有到max_x个棋盘
            count_x = 0
            x = back_blok_size
            y += every_size
        back_print_every_canvas(Queen, [x, y])  #画布输出该情况
        x += every_size
        count_x += 1
        count_sum += 1
        return
    for col in range(len(Queen)):
        Queen[cur], flag = col, True
        for row in range(cur):
            if Queen[row] == col or abs(col - Queen[row]) == cur - row:  #找到了解
                flag = False  #有冲突
                break
        if flag:  #当前无冲突
            back_recursive(cur + 1)  #递归查找


def back_every_Queen():
    '''回溯法(所有情况)'''
    global N
    N = int(entry_input.get())  #获取entry内容
    back_reset()  #初始化全局变量
    t_start = time.time()  #开始计时
    back_recursive()  #递归算法
    t_end = time.time()  #结束计时
    info = "生成数量：" + str(count_sum) + "\n使用时间：" + str(t_end - t_start) + "s"
    showinfo(title="信息", message=info)  #弹出信息框


def back_single(cur=0):
    '''回溯法 一种情况递归子程序'''
    global is_success_back, Queen, Queen_succ
    if is_success_back == True:
        return
    if cur == len(Queen):
        is_success_back = True
        Queen_succ = copy.deepcopy(Queen)
        return
    for col in range(len(Queen)):
        Queen[cur], flag = col, True
        for row in range(cur):
            if Queen[row] == col or abs(col - Queen[row]) == cur - row:  #找到了解
                flag = False  #有冲突
                break
        if flag:  #当前无冲突
            back_single(cur + 1)  #递归查找


def back_single_Queen():
    '''回溯法(一种情况)'''
    global N, Queen, is_success_back, Queen_succ
    N = int(entry_input.get())  #获取entry内容
    back_reset()  #初始化全局变量
    t_start = time.time()  #开始计时
    back_single()  #递归算法
    t_end = time.time()  #结束计时
    if is_success_back:
        print_one_canvas(Queen_succ)
    info = "\n使用时间：" + str(t_end - t_start) + "s"
    showinfo(title="信息", message=info)  #弹出信息框


# 遗传算法函数
def genetic_reset():
    '''遗传算法 初始化'''
    global population, adaptive, is_success_genetic, count_genetic
    count_genetic = 0  #迭代次数计数
    is_success_genetic = False  #遗传算法是否成功
    population = []  #种群
    adaptive = [0 for i in range(group_num)]  #种群的适应值
    canvas.delete("oval", "line", "rectangle")  #清空画布
    window.update_idletasks()  #窗口刷新


def genetic_cal_adaptive(x):
    '''遗传算法 计算适应值'''
    conflict = 0  #冲突值，每遇到冲突就加1
    for i in range(N):
        for j in range(i + 1, N):
            if x[i] == x[j] or abs(x[i] - x[j]) == j - i:  #冲突
                conflict += 1
    if conflict == 0:  #找到解
        return 2
    return 1 / conflict  #返回适应值，冲突值的倒数


def genetic_reproduce(p1, p2):
    '''遗传算法 遗传（父母交换基因片段并返回两个孩子）'''
    #随机选取两个点，将两个点之间的两个体基因交换
    a = copy.deepcopy(p1)
    b = copy.deepcopy(p2)
    start = random.randint(0, N - 1)
    end = random.randint(0, N - 1)
    if start > end:
        start, end = end, start
    for i in range(start, end + 1):
        a[i], b[i] = b[i], a[i]
    return a, b


def genetic_mutate(a):
    '''遗传算法 变异（随机改变个体某个位置的基因）'''
    index = random.randint(0, N - 1)  #随机选取变异位置
    a[index] = random.randint(0, N - 1)  #将该位置变异为随机下标
    return a


def genetic_single():
    global N, Queen, population, adaptive, count_genetic, is_success_genetic
    # 初始化种群
    for i in range(group_num):
        x = [random.randint(0, N - 1) for j in range(N)]  #随机生成个体基因
        population.append(x)
        adaptive[i] = genetic_cal_adaptive(x)

    count_genetic = 0  #迭代计数
    is_success_genetic = False
    while not is_success_genetic:  #迭代
        new_population = []  #创建一个新的空种群

        # 选取适应值最好的个体当所有孩子的父亲
        index_a = 0
        for i in range(group_num):
            if adaptive[index_a] < adaptive[i]:
                index_a = i
        parent_a = population[index_a]
        best = adaptive[index_a]
        if group_num % 2 == 1:
            new_population.append(parent_a)
        adaptive[index_a] = 0  #父亲适应值取消，之后不会再选

        # 找到解
        if best == 2:
            is_success_genetic = True
            Queen = copy.deepcopy(parent_a)
            break

        # 迭代最大次数就退出
        if count_genetic == max_iter_genetic:
            Queen = copy.deepcopy(parent_a)
            break

        # 不断选取母亲创造新种群
        for i in range(group_num // 2):
            # 选取当前适应值最好的个体当两个孩子的母亲
            index_b = 0
            for j in range(group_num):
                if adaptive[index_b] < adaptive[j]:
                    index_b = j
            parent_b = population[index_b]
            adaptive[index_b] = 0

            # 遗传，杂交得两个孩子
            childs = genetic_reproduce(parent_a, parent_b)

            # 变异
            child1 = genetic_mutate(childs[0])
            child2 = genetic_mutate(childs[1])

            # 将两个孩子加入新的种群中
            new_population.append(child1)
            new_population.append(child2)

        # 更新种群
        population = new_population

        # 更新适应值
        for i in range(group_num):
            adaptive[i] = genetic_cal_adaptive(population[i])
        count_genetic += 1  #迭代次数增加


def genetic_Queen():
    '''遗传算法'''
    global N, Queen, count_genetic, is_success_genetic
    N = int(entry_input.get())  #获取entry内容
    genetic_reset()  #初始化全局变量
    t_start = time.time()  #开始计时
    genetic_single()
    t_end = time.time()  #结束计时
    print_one_canvas(Queen)  #画布打印情况
    if not is_success_genetic:  #没有找到最优解
        info = "迭代到达最大次数" + str(
            max_iter_genetic) + "次退出，只输出当前最优解" + "\n使用时间：" + str(t_end -
                                                                 t_start) + "s"
    else:
        info = "迭代次数：" + str(count_genetic) + "\n使用时间：" + str(t_end -
                                                              t_start) + "s"
    showinfo(title="信息", message=info)  #弹出信息框


# 模拟退火算法函数
def anneal_reset():
    '''模拟退火法 初始化'''
    global Queen, temperature, is_success_anneal
    is_success_anneal = False  #模拟退火算法是否成功
    Queen = [0 for i in range(N)]  #皇后位置
    temperature = max_temperature
    canvas.delete("oval", "line", "rectangle")  #清空画布
    window.update_idletasks()  #窗口刷新


def anneal_cal_conflict(x):
    '''模拟退火法 计算冲突值'''
    conflict = 0  #冲突值，每遇到冲突就加1
    for i in range(N):
        for j in range(i + 1, N):
            if x[i] == x[j] or abs(x[i] - x[j]) == j - i:  #冲突
                conflict += 1
    return conflict  #返回冲突值


def anneal_select_next(status):
    '''模拟退火法 选择最好的邻居状态'''
    global temperature
    # 邻域变换，此处邻域定义为变换一位
    status_copy = copy.deepcopy(status)
    index = random.randint(0, N - 1)  #随机选取位置
    value = random.randint(0, N - 1)  #将该位置替换为随机下标
    status_copy[index] = value
    conflict_next = anneal_cal_conflict(status_copy)  #替换后的冲突数
    conflict_now = anneal_cal_conflict(status)  #当前皇后冲突数

    # 如果后继元素优于前一个，则直接选取；如果差于，就根据温度概率选取
    E = conflict_next - conflict_now
    if E < 0 or math.exp((-1) * E / temperature) > random.random():
        status[index] = value
    temperature = temperature * nt_multiple
    return status


def anneal_single():
    global N, Queen, temperature, is_success_anneal
    # 初始化Queen
    for i in range(N):
        Queen[i] = i

    # 当存在冲突时，循环求解最佳后继
    is_success_anneal = False
    while temperature > min_temperature:
        Queen = anneal_select_next(Queen)
        if not anneal_cal_conflict(Queen):
            is_success_anneal = True
            break


def anneal_Queen():
    '''模拟退火法'''
    global N, Queen, temperature, is_success_anneal
    N = int(entry_input.get())  #获取entry内容
    anneal_reset()  #初始化全局变量
    t_start = time.time()  #开始计时
    anneal_single()
    t_end = time.time()  #结束计时
    print_one_canvas(Queen)  #画布打印情况
    if not is_success_anneal:  #没有找到最优解
        info = "温度达到最小值" + str(
            min_temperature) + "退出，只输出当前最优解" + "\n使用时间：" + str(t_end -
                                                               t_start) + "s"
    else:
        info = "当前温度：" + str(temperature) + "\n使用时间：" + str(t_end -
                                                            t_start) + "s"
    showinfo(title="信息", message=info)  #弹出信息框


# 爬山法函数
def climb_reset():
    '''爬山法 初始化'''
    global Queen, is_success_climb, count_climb
    count_climb = 0  #迭代次数计数
    is_success_climb = False  #爬山法是否成功
    Queen = [0 for i in range(N)]  #皇后位置
    canvas.delete("oval", "line", "rectangle")  #清空画布
    window.update_idletasks()  #窗口刷新


def climb_cal_conflict(x):
    '''爬山法 计算冲突值'''
    conflict = 0  #冲突值，每遇到冲突就加1
    for i in range(N):
        for j in range(i + 1, N):
            if x[i] == x[j] or abs(x[i] - x[j]) == j - i:  #冲突
                conflict += 1
    return conflict  #返回冲突值


def climb_select_next(status):
    '''爬山法 选择最好的邻居状态'''
    convert = {}
    length = len(status)
    # 邻域变换，此处邻域定义为变换一位
    for col in range(length):
        for row in range(length):
            if status[col] == row:
                continue
            status_copy = copy.deepcopy(status)
            status_copy[col] = row
            convert[(col, row)] = climb_cal_conflict(status_copy)

    answers = []  #最佳后继集合
    conflict_now = climb_cal_conflict(status)  #当前皇后冲突对数

    # 遍历存储所有可能后继的字典，找出最佳后继
    for key, value in convert.items():
        if value < conflict_now:
            conflict_now = value
    for key, value in convert.items():
        if value == conflict_now:
            answers.append(key)

    # 如果最佳后继集合元素大于一个 随机选择一个
    if len(answers) > 0:
        x = random.randint(0, len(answers) - 1)
        col = answers[x][0]
        row = answers[x][1]
        status[col] = row
    return status


def climb_single():
    global N, Queen, is_success_climb, count_climb
    # 初始化Queen
    for i in range(N):
        Queen[i] = i

    # 当存在冲突时，循环求解最佳后继
    count_climb = 0
    is_success_climb = True
    while climb_cal_conflict(Queen):
        if count_climb == max_iter_climb:
            is_success_climb = False
            break
        Queen = climb_select_next(Queen)
        count_climb += 1


def climb_Queen():
    '''爬山法'''
    global N, Queen, is_success_climb
    N = int(entry_input.get())  #获取entry内容
    climb_reset()  #初始化全局变量
    t_start = time.time()  #开始计时
    climb_single()
    t_end = time.time()  #结束计时
    print_one_canvas(Queen)  #画布打印情况
    if not is_success_climb:  #没有找到最优解
        info = "迭代到达最大次数" + str(
            max_iter_climb) + "次退出，只输出当前最优解" + "\n使用时间：" + str(t_end -
                                                               t_start) + "s"
    else:
        info = "迭代次数：" + str(count_climb) + "\n使用时间：" + str(t_end -
                                                            t_start) + "s"
    showinfo(title="信息", message=info)  #弹出信息框


def compare_back(n):
    '''获取回溯法时间'''
    global N
    N = n
    back_reset()
    t_start = time.time()  #开始计时
    back_single()  #回溯法递归算法
    t_end = time.time()  #结束计时
    return (True, t_end - t_start)


def compare_genetic(n):
    '''获取遗传算法时间'''
    global N, is_success_genetic
    N = n
    genetic_reset()
    t_start = time.time()  #开始计时
    genetic_single()  #回溯法递归算法
    t_end = time.time()  #结束计时
    if is_success_genetic:
        return (True, t_end - t_start)
    else:
        return (False, t_end - t_start)


def compare_anneal(n):
    '''获取模拟退火算法时间'''
    global N, Queen, is_success_anneal
    N = n
    anneal_reset()  #初始化全局变量
    t_start = time.time()  #开始计时
    anneal_single()
    t_end = time.time()  #结束计时
    if is_success_anneal:
        return (True, t_end - t_start)
    else:
        return (False, t_end - t_start)


def compare_climb(n):
    '''获取爬山法时间'''
    global N, Queen, is_success_climb
    N = n
    climb_reset()  #初始化全局变量
    t_start = time.time()  #开始计时
    climb_single()
    t_end = time.time()  #结束计时
    if is_success_climb:
        return (True, t_end - t_start)
    else:
        return (False, t_end - t_start)


def compare_Queen():
    '''算法比较'''
    global compare_times, compare_min, compare_max
    back_ave_t = [0 for _ in range(compare_max + 1)]  #回溯法平均时间
    genetic_ave_t = [0 for _ in range(compare_max + 1)]  #遗传算法平均时间
    anneal_ave_t = [0 for _ in range(compare_max + 1)]  #模拟退火算法平均时间
    climb_ave_t = [0 for _ in range(compare_max + 1)]  #爬山法平均时间
    genetic_nf = [0 for _ in range(compare_max + 1)]  #遗传算法没有找到的次数
    anneal_nf = [0 for _ in range(compare_max + 1)]  #模拟退火算法没有找到的次数
    climb_nf = [0 for _ in range(compare_max + 1)]  #爬山法没有找到的次数
    sttr = "每种算法每种情况的测试次数：%d次" % compare_times
    print(sttr)
    sttr = "皇后数   回溯ave_t   遗传false 遗传ave_t   退火false 退火ave_t   爬山false 爬山ave_t"
    print(sttr)
    for i in range(compare_min, compare_max + 1):  #测试区间最小到最大依次测试
        for j in range(compare_times):  #测试compare_times次算法，求平均
            back_ave_t[i] += compare_back(i)[1]

            genetic_s = compare_genetic(i)
            genetic_ave_t[i] += genetic_s[1]
            if not genetic_s[0]:
                genetic_nf[i] += 1

            anneal_s = compare_anneal(i)
            anneal_ave_t[i] += anneal_s[1]
            if not anneal_s[0]:
                anneal_nf[i] += 1

            climb_s = compare_climb(i)
            climb_ave_t[i] += climb_s[1]
            if not climb_s[0]:
                climb_nf[i] += 1

        back_ave_t[i] /= compare_times
        genetic_ave_t[i] /= compare_times
        anneal_ave_t[i] /= compare_times
        climb_ave_t[i] /= compare_times
        sttr = " %2d       %.4fs      %2d次     %.4fs      %2d次     %.4fs      %2d次     %.4fs" % (
            i, back_ave_t[i], genetic_nf[i], genetic_ave_t[i], anneal_nf[i],
            anneal_ave_t[i], climb_nf[i], climb_ave_t[i])
        print(sttr)


# 窗口
window = Tk()
window.title("N皇后问题")
window.geometry("820x660")

# 控件
frame = Frame(window)
canvas = Canvas(frame, scrollregion=(0, 0, 1600, 20000))
image_queen = PhotoImage(file='queen.png')
xbar = Scrollbar(frame, orient=HORIZONTAL)
ybar = Scrollbar(frame, orient=VERTICAL)
label_input = Label(window, text='数量：')
entry_input = Entry(window, width=10)
btn_back_every = Button(window,
                        text="回溯法(全部情况)",
                        width=15,
                        command=back_every_Queen)
btn_back_single = Button(window,
                         text="回溯法(一种情况)",
                         width=15,
                         command=back_single_Queen)
btn_genetic = Button(window, text="遗传算法", width=15, command=genetic_Queen)
btn_anneal = Button(window, text="模拟退火算法", width=15, command=anneal_Queen)
btn_climb = Button(window, text="爬山法", width=15, command=climb_Queen)
btn_compare = Button(window, text="算法比较(命令行)", width=15, command=compare_Queen)

# 显示控件
frame.grid(row=0, column=0, columnspan=8)
xbar.pack(side=BOTTOM, fill=X)
xbar.config(command=canvas.xview)
ybar.pack(side=RIGHT, fill=Y)
ybar.config(command=canvas.yview)
canvas.config(width=800, height=600)
canvas.config(yscrollcommand=ybar.set)
canvas.pack(side=LEFT, expand=True, fill=BOTH)
label_input.grid(row=1, column=0)
entry_input.grid(row=1, column=1)
btn_back_every.grid(row=1, column=2)
btn_back_single.grid(row=1, column=3)
btn_genetic.grid(row=1, column=4)
btn_anneal.grid(row=1, column=5)
btn_climb.grid(row=1, column=6)
btn_compare.grid(row=1, column=7)

# 运行
window.mainloop()
