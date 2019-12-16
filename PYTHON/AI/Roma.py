import queue
import time
from functools import cmp_to_key


N = 0  #节点个数
MIN = 0  #路径最小值
MAX = 1000  #路径最大值
Start = 0  #初始点
End = 0  #结束点
graph = []  #图的临界矩阵
Founation = [
    366, 0, 160, 242, 161, 176, 77, 151, 226, 244, 241, 234, 380, 100, 193,
    253, 329, 80, 199, 374
]
Nation = [
    'Arad', 'Bucharest', 'Craiova', 'Drobeta', 'Eforie', 'Fagaras', 'Giurgiu',
    'Hirsova', 'Iasi', 'Lugoj', 'Mehadia', 'Neamt', 'Oradea', 'Pitesti',
    'RimnicuVilcea', 'Sibiu', 'Timisoara', 'Urzicen', 'Vaslui', 'Zerind'
]


def load_data():
    '''读取数据'''
    with open('D:\CODE\PYTHON\AI\data.txt', 'r') as of:
        for line in of:
            line = line.replace('\n', '')
            linestr = line.split(',')
            graph.append(linestr)
    global N
    N = len(graph[0])


def BFS():
    '''广度优先'''
    father = [-1 for i in range(0, N)]  #记录每个城市的“父节点”的位置
    seek = [False for i in range(0, N)]  #记录此节点是否访问过，访问过就设置成true
    openList = queue.Queue()  #Open表，保存将要访问的节点

    #开始计时
    start = time.perf_counter()

    #初始点加入
    openList.put(Start)
    seek[Start] = True

    #循环查找路径
    while not openList.empty():
        x = openList.get()
        if x == End:
            break
        for i in range(0, N):
            if int(graph[x][i]) > MIN and int(
                    graph[x][i]) < MAX and seek[i] == False:
                openList.put(i)
                father[i] = x
                seek[i] = True

    #结束计时
    end = time.perf_counter()

    #打印
    cost = 0
    road = []
    x = End
    while True:
        cost += int(graph[x][father[x]])
        road.append(x)
        x = father[x]
        if x == Start:
            road.append(x)
            break
    road.reverse()
    print("起始点：" + Nation[Start])
    print("终止点：" + Nation[End])
    print("访问顺序：")
    for i in road:
        print("->" + str(Nation[i]))
    print("访问节点数：" + str(len(road)))
    print("访问路径长度：" + str(cost))
    print("运行时间：" + str((end - start) * 1000) + " ms")


def DFS():
    '''深度优先'''
    father = [-1 for i in range(0, N)]  #记录每个城市的“父节点”的位置
    from_to = [[False] * N for i in range(0, N)]
    openList = queue.Queue()  #Open表，保存将要访问的节点

    #开始计时
    start = time.perf_counter()

    #初始点加入
    openList.put(Start)
    n = Start
    from_to[Start][Start] = False

    #循环查找路径
    while not openList.empty():
        x = openList.get()
        if (x == End):
            break
        for i in range(N - 1, -1, -1):
            if int(graph[x][i]) > MIN and int(
                    graph[x][i]) < MAX and from_to[x][i] == False:
                openList.put(i)
                father[i] = x
                from_to[x][i] = True
                from_to[i][x] = True

    #结束计时
    end = time.perf_counter()

    #打印
    cost = 0
    road = []
    x = End
    while True:
        cost += int(graph[x][father[x]])
        road.append(x)
        x = father[x]
        if x == Start:
            road.append(x)
            break
    road.reverse()
    print("起始点：" + Nation[Start])
    print("终止点：" + Nation[End])
    print("访问顺序：")
    for i in road:
        print("->" + str(Nation[i]))
    print("访问节点数：" + str(len(road)))
    print("访问路径长度：" + str(cost))
    print("运行时间：" + str((end - start) * 1000) + " ms")


def Seek(x, seek):
    '''查找当前点距离最近的点'''
    min = 0
    a = []
    count = 0
    for i in range(0, N):
        if int(graph[x][i]) > MIN and int(
                graph[x][i]) < MAX and seek[x][i] == False:
            count += 1
            a.append(i)
            seek[x][i] = True
            seek[i][x] = True
    if a:
        min = a[0]
    for i in range(0, count):
        if int(graph[x][a[i]]) < int(graph[x][min]):
            min = a[i]
    if count == 0:
        return -1
    return min


def Greedy():
    '''贪婪算法'''
    father = [-1 for i in range(0, N)]  #记录每个城市的“父节点”的位置
    seek = [[False] * N for i in range(0, N)]  #记录此节点是否访问过，访问过就设置成true
    openList = []  #Open表，保存将要访问的节点

    #开始计时
    start = time.perf_counter()

    #初始点加入
    for i in range(0, N):
        if int(graph[Start][i]) > MIN and int(
                graph[Start][i]) < MAX and seek[Start][i] == False:
            openList.append(i)
            father[i] = Start
            seek[Start][i] = True
            seek[i][Start] = True
    openList.sort(reverse=True)

    #循环查找路径
    while openList:
        x = openList.pop(0)
        t = Seek(x, seek)
        while t != -1:
            if x == End:
                break
            father[t] = x
            x = t
            t = Seek(x, seek)

    #结束计时
    end = time.perf_counter()

    #打印
    cost = 0
    road = []
    x = End
    while True:
        cost += int(graph[x][father[x]])
        road.append(x)
        x = father[x]
        if x == Start:
            road.append(x)
            break
    road.reverse()
    print("起始点：" + Nation[Start])
    print("终止点：" + Nation[End])
    print("访问顺序：")
    for i in road:
        print("->" + str(Nation[i]))
    print("访问节点数：" + str(len(road)))
    print("访问路径长度：" + str(cost))
    print("运行时间：" + str((end - start) * 1000) + " ms")


class Data:
    '''节点'''
    location = 0
    cost = 0

    def __init__(self, lo, co):
        self.location = lo
        self.cost = co


def Astar():
    '''A*算法'''
    father = [-1 for i in range(0, N)]  #记录每个城市的“父节点”的位置
    seek = [False for i in range(0, N)]  #记录此节点是否访问过，访问过就设置成true
    openList = []  #Open表，保存将要访问的节点

    #开始计时
    start = time.perf_counter()

    #初始点加入
    openList.append(Data(Start, Founation[Start]))
    seek[Start] = True

    #循环查找路径
    while openList:

        def f(a, b):
            return a.location - b.location

        openList.sort(key=cmp_to_key(f))
        x = openList.pop(0)
        if (x.location == End):
            break
        for i in range(0, N):
            if int(graph[x.location][i]) > MIN and int(
                    graph[x.location][i]) < MAX and seek[i] == False:
                openList.append(
                    Data(i,
                         int(graph[x.location][i]) + int(Founation[i])))
                father[i] = x.location
                seek[i] = True

    #结束计时
    end = time.perf_counter()

    #打印
    cost = 0
    road = []
    x = End
    while True:
        cost += int(graph[x][father[x]])
        road.append(int(x))
        x = father[x]
        if x == Start:
            road.append(x)
            break
    road.reverse()
    print("起始点：" + Nation[Start])
    print("终止点：" + Nation[End])
    print("访问顺序：")
    for i in road:
        print("->" + str(Nation[i]))
    print("访问节点数：" + str(len(road)))
    print("访问路径长度：" + str(cost))
    print("运行时间：" + str((end - start) * 1000) + " ms")


if __name__ == "__main__":
    Start = 4
    End = 12
    print("--加载数据--")
    load_data()
    print("\n--广度优先算法--")
    BFS()
    print("\n--深度优先算法--")
    DFS()
    print("\n--贪婪算法--")
    Greedy()
    print("\n--A*算法--")
    Astar()