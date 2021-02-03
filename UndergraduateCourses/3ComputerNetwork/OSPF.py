import collections
import heapq


class OSPF:
    '''OSPF类'''

    def __init__(self):
        '''初始化函数'''
        self.graphDict = collections.defaultdict(list)  # Dict表示的图

    def getInputGraph(self):
        '''从命令行输入构建'''
        getInput = input()
        while getInput != 'end':
            key, num = getInput.split(' ')  # 按照空格分割，加入图
            for i in range(int(num)):
                nbRouter, cost = input().split(' ')  # 按照空格分割，加入图
                self.graphDict[key].append((nbRouter, int(cost)))
            getInput = input()

    def getFileGraph(self, fileName):
        '''从文件读取'''
        with open(fileName, 'r') as of:
            getLine = of.readline()
            while getLine:
                getLine = getLine.replace('\n', '')  # 去掉换行符
                key, num = getLine.split(' ')  # 按照空格分割
                for i in range(int(num)):
                    getLine = of.readline()
                    getLine = getLine.replace('\n', '')  # 去掉换行符
                    nbRouter, cost = getLine.split(' ')  # 按照空格分割
                    self.graphDict[key].append((nbRouter, int(cost)))
                getLine = of.readline()
        of.close()

    def getRouterTableDijkstra(self, from_node):
        '''迪杰斯特拉算法遍历该点到所有节点的最短路径，产生路由表'''
        routerTable = collections.defaultdict(list)  # Dict表示的路由表
        q = [(0, from_node, [])]  # 待找节点最小堆，每个元素元组为(cost, router, path)
        seen = set()  # 已找最短路径的节点集合
        while q:
            (cost, v1, path) = heapq.heappop(q)  # 堆取出cost最小的元组
            if v1 not in seen:  # 该点还没找到最短路径
                seen.add(v1)  # 已找
                # 添加当前路径
                pathcp = path.copy()
                pathcp.append(v1)

                if len(path) > 1:  # 该路由器要经过原点的下一跳路由器
                    routerTable[v1] = [cost, pathcp[1]]  # 添加距离和原点的下一跳路由器
                elif len(path) == 1:  # 该路由器是原点的下一跳路由器
                    routerTable[v1] = [cost, v1]  # 添加距离和原点的下一跳路由器（本点）

                for v2, c in self.graphDict.get(v1):  # 取出相邻节点
                    if v2 not in seen:  # 该点还没找到最短路径
                        heapq.heappush(q, (cost+c, v2, pathcp))  # 插入堆
        return routerTable

    def printAllRouterTable(self):
        '''获取所有节点的路由表'''
        for i in self.graphDict:
            print("\n路由表%s：" % (i))
            getRouterTable = self.getRouterTableDijkstra(i)
            for j in getRouterTable:
                print(j, getRouterTable[j][0], getRouterTable[j][1])


if __name__ == '__main__':
    ospf = OSPF()
    # ospf.getInputGraph()
    ospf.getFileGraph('routerLink.txt')
    ospf.printAllRouterTable()
