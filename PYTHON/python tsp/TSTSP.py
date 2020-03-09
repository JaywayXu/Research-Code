"""

@author: zll

description：

禁忌搜索算法求解TSP

"""

import random

import copy

import time

 

def tabu_solve(inst, start_time):

   #函数功能：随机生成一个输出路径（初始解）

   #子函数：初始化路径
   def initial_route():

       route = []

       #range函数：返回从0-n-1的列表
       unvisited = list(range(n))

       count = n

       #随机生成0-n-1的乱序序列，表示初始解。
       while(count != 0):

           index = random.randint(0, count - 1)

           current = unvisited[index]

           route.append(current)
           
           unvisited.pop(index)

           count -= 1

       return route

   #函数功能：输出路径的目标值
   def cal_distance(route):

       distance = 0.0

       for i in range(n - 1):
           #从0号城市到n-1号城市
           distance += get_edge(i, i+1, route)
       #n-1号城市返回0号城市
       distance += get_edge(n-1, 0, route)

       return distance

   #函数功能：获取两点之间的边距
   def get_edge(index_i, index_j, route):

       if index_i == n : index_i = 0

       if index_j == n : index_j = 0

       return edge[route[index_i]][route[index_j]]

   #函数功能：计算邻域（按Swap算子）
   def cal_neighbor(nid_i, nid_j, route):

       #i，j表示点的编号，index_i、j表示点在路径中的序号

       #.index（n）函数用于返回n在列表中的索引值
       index_i = route.index(nid_i)

       index_j = route.index(nid_j)

       delta = 0

       #去重优化
       if(index_i == index_j - 1 or index_i == index_j + n - 1):

           delta += get_edge(index_i, index_j + 1, route) + get_edge(index_i - 1,index_j, route)

           delta -= get_edge(index_i - 1, index_i, route) + get_edge(index_j,index_j + 1, route)

       elif(index_i == index_j + 1 or index_j == index_i + n -1):

           delta += get_edge(index_j, index_i + 1, route) + get_edge(index_j - 1,index_i, route)

           delta -= get_edge(index_j - 1, index_j, route) + get_edge(index_i,index_i + 1, route)

       else:

           delta += get_edge(index_j, index_i - 1, route) + get_edge(index_j,index_i + 1, route)

           delta += get_edge(index_i, index_j - 1, route) + get_edge(index_i,index_j + 1, route)

           delta -= get_edge(index_i, index_i - 1, route) + get_edge(index_i,index_i + 1, route)

           delta -= get_edge(index_j, index_j - 1, route) + get_edge(index_j,index_j + 1, route)

       return delta

           
   #输出路径
   def output_route(info, route, distance):

       print(info, ', tour:', route, ', distance:', distance)

   

   eplison = 0.000001

   iteration = 500 #最大迭代次数

   n= inst.n #城市数量

   tabu_length= int(n * 0.2) #禁忌长度——这里设置为节点数的20%

   points = inst.points

   dist = inst.dist

   edge = [([0] * n) for i in range(n)] #保存点到点直接的距离，二维表

   for j in range(n):

       for i in range(j + 1, n):

           edge[i][j] = edge[j][i] = dist.get((i,j))

   tabu_list = [([0] * n) for i in range(n)] #定于禁忌表，二维表

   #best用于存储搜索最优目标值，local用于存储搜索当前目标值
   best = float('inf')

   best_route = list()

   local = 0.0

   
   #获取初始解
   ini_route = initial_route()
   #当前满意解
   local = cal_distance(ini_route)

   best = min(best, local)

   
   #初始化最优解
   route = copy.copy(ini_route)

   best_route = copy.copy(ini_route)

   #计算初始邻域
   #初始化邻域为哈希表
   neighbors = dict()

   for i in range(n):

       for j in range(i + 1, n):
           #[i,j:i,j,route]
           neighbors[str(i) + ',' + str(j)] = cal_neighbor(i, j, route)

   

   #搜索开始

   for k in range(iteration):

       sorted_neighbors = sorted(neighbors.items(), key = lambda item :item[1])

       #print('sort_neighbors', sorted_neighbors)

       nid_i = nid_j = 0

       flag = 0

       for neighbor in sorted_neighbors:

           nids = neighbor[0].split(',')

           nid_i = int(nids[0])

           nid_j = int(nids[1])

           delta = neighbor[1]

           temp_local = local + delta

           # 破禁准则
           #最优解
           if(temp_local < best):

                local = temp_local

                best = local

                flag = 1

           else:

                #禁忌表数值非零时，跳过当前邻域
                if(tabu_list[nid_i][nid_j] !=0):

                    continue

                else:

                   local = temp_local

           break

       # 根据上述邻域选择的结果，更新路径（按swap交换两个节点）

       index_i = route.index(nid_i)

       index_j = route.index(nid_j)

       route.pop(index_i)

       route.insert(index_i, nid_j)

       route.pop(index_j)

       route.insert(index_j, nid_i)

       if(flag == 1):

           best_route = copy.copy(route)

       # 更新禁忌表

       for i in range(n):

           for j in range(n - i):

                if(tabu_list[i][j] != 0):

                    tabu_list[i][j] -= 1

       tabu_list[nid_i][nid_j] += tabu_length

       # 更新邻域

       for i in range(n):

           for j in range(i + 1, n):

                neighbors[str(i) + ',' +str(j)] = cal_neighbor(i, j, route)
       
       print("迭代次数",k,"\t当前满意解",best)

   #将TS结果按字典形式返回

   result = dict()

   result['tour'] = str(best_route)

   result['cost'] = best

   return result           


import math

import random

 
#Instance类的定义方式

class Instance:

   def __init__(self):

       self.n = 52 # 结点数量

       self.points = [
[ 565,575 ],[ 25,185 ],[ 345,750 ],[ 945,685 ],[ 845,655 ],
[ 880,660 ],[ 25,230 ],[ 525,1000 ],[ 580,1175 ],[ 650,1130 ],
[ 1605,620 ],[ 1220,580 ],[ 1465,200 ],[ 1530,5 ],
[ 845,680 ],[ 725,370 ],[ 145,665 ],
[ 415,635 ],[ 510,875 ],[ 560,365 ],[ 300,465 ],[ 520,585 ],[ 480,415 ],
[ 835,625 ],[ 975,580 ],[ 1215,245 ],[ 1320,315 ],[ 1250,400 ],[ 660,180 ],
[ 410,250 ],[ 420,555 ],[ 575,665 ],[ 1150,1160 ],[ 700,580 ],[ 685,595 ],
[ 685,610 ],[ 770,610 ],[ 795,645 ],[ 720,635 ],[ 760,650 ],[ 475,960 ],
[ 95,260 ],[ 875,920 ],[ 700,500 ],[ 555,815 ],[ 830,485 ],[ 1170,65 ],
[ 830,610 ],[ 605,625 ],[ 595,360 ],[ 1340,725 ],[ 1740,245 ]
	];
       self.dist = {(i, j) : math.sqrt(sum((self.points[i][k] -self.points[j][k])**2 \

                for k in range(2))) for i in range(self.n) for j in range(i)} # 点之间的距离

       

def main():

   #初始化算例并输出
   inst = Instance() 

   #开始禁忌搜索
   start_time = time.time()

   tabu_result = tabu_solve(inst, start_time) #调用tabuSearch求解

   end_time = time.time()

   tabu_time = end_time - start_time

   tabu_result['time'] = tabu_time

   #输出结果
   print(tabu_result)

if __name__ == '__main__':
    main()