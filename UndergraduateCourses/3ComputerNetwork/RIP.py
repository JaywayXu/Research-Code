
def inputRouterGraph():
    '''从命令行获取路由器连接图'''
    graph = []
    print("输入路由器连接图：")
    getInput = input()
    while getInput != 'end':
        graph.append(getInput.split(' '))  # 按照空格分割，加入图
        getInput = input()
    return graph


def inputInitTable():
    '''从命令行获取初始路由器连接的网络'''
    table = []
    print("输入初始路由器连接的网络：")
    getInput = input()
    while getInput != 'end':
        table.append(getInput.split(' '))  # 按照空格分割，加入图
        getInput = input()
    return table


def readRouterGraph(fileName):
    '''从文件读取路由器连接图'''
    graph = []
    with open(fileName, 'r') as of:
        for line in of:
            line = line.replace('\n', '')  # 去掉换行符
            graph.append(line.split(' '))  # 按照空格分割，加入图
    of.close()
    return graph


def readInitTable(fileName):
    '''从文件读取初始路由器连接的网络'''
    table = []
    with open(fileName, 'r') as of:
        for line in of:
            line = line.replace('\n', '')  # 去掉换行符
            table.append(line.split(' '))  # 按照空格分割，加入图
    of.close()
    return table


class RouterTable:
    '''路由表'''

    def __init__(self):
        '''路由表初始化'''
        self.table = []  # 路由表数组，每项由[net,dist,nextRouter]组成
        self.isConnect = -1  # 直接连接的网络的路由器标志
        self.maxDist = 16  # 路径的最大长度

    def addInitTable(self, nets):
        '''添加最初的路由表项'''
        self.table.append([nets, 1, self.isConnect])

    def updateTable(self, nbTable, nbIndex):
        '''根据传进的表更新当前表'''
        tableFirstCol = [i[0] for i in self.table]  # 通过numpy转换取第一列net
        for i in nbTable.getTable():  # 遍历邻居表
            if i[0] in tableFirstCol:  # 已经有该net的路由表项
                index = tableFirstCol.index(i[0])  # 获取当前表中该项的下标
                if self.table[index][1] > i[1]+1:  # 比当前距离短
                    self.table[index][1] = i[1]+1
                    self.table[index][2] = nbIndex
            else:
                if i[1]+1 != self.maxDist:  # 到16则放弃添加
                    # 添加路由表项，距离+1，改变下一跳路由器
                    self.table.append([i[0], i[1]+1, nbIndex])

    def getTable(self):
        return self.table


class RIP:
    '''RIP类'''

    def __init__(self, routerGraph, initTable):
        '''RIP初始化'''
        self.routerGraph = routerGraph  # 路由器连接图
        self.routerNum = len(routerGraph)  # 路由器个数
        # 路由表数组
        self.routerTables = [RouterTable() for i in range(self.routerNum)]
        # 构建初始路由表项
        for i in initTable:
            self.routerTables[int(i[0])].addInitTable(i[1])

    def update(self):
        '''运行一次RIP，更新所有路由表'''
        for i in range(self.routerNum):  # 对于每一个路由器
            # 单步调试
            # input()
            # self.printTables()

            # 查找所有相邻的路由器
            for j in range(self.routerNum):
                if int(self.routerGraph[i][j]):
                    # 传递当前路由表
                    self.routerTables[j].updateTable(self.routerTables[i], i)

    def printTables(self):
        '''打印所有路由表'''
        for i in range(self.routerNum):  # 对于每一个路由器
            print("\n路由表%s：" % (i))
            table = self.routerTables[i].getTable()
            if table:
                for x in table:
                    print(x[0], x[1], x[2])
            else:
                print("NULL")


if __name__ == '__main__':
    # rGraph = inputRouterGraph()
    # iTable = inputInitTable()
    rGraph = readRouterGraph('routers.txt')
    iTable = readInitTable('tables.txt')

    rip = RIP(rGraph, iTable)
    rip.printTables()

    while 1:
        input()  # 暂停
        rip.update()
        rip.printTables()
