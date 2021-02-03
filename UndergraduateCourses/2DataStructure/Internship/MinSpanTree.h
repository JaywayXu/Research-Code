#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 10000
#define FILENAME "mst.txt"

struct Graph {
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
};

int InDegree(Graph G, int v) {
	int sum = 0;
	for (int i=0; i<G.numVertexes; i++) {
		if (G.arc[i][v] != INFINITY && G.arc[i][v] != 0)
			sum += 1;
	}
	return sum;
}

struct Edge {
    int begin, end, weight;
};

class MSTree {
protected:
    Graph *G;
	ofstream ofile;
public:
    MSTree();
    ~MSTree();
    void Swapn(Edge *edges,int i, int j);
    void sort(Edge *edges);
    int Find(int *parent, int f);
    void Kruskal();
    void Prim();
    void Print_Graph();
};

MSTree::MSTree() {
	ofile.open(FILENAME, ios::out);
    G = new Graph();
    int i, j;
	int a, b, c; 

    cout << "边数，顶点数：";
    cin >> G->numEdges >> G->numVertexes;

	for (i = 0; i < G->numVertexes; i++) {
		for ( j = 0; j < G->numVertexes; j++) {
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	cout << "输入边集(顶点从0 ~ n-1)：" << endl;
	for (i = 0; i < G->numEdges; i++) {
		cin >> a >> b >> c;
		G->arc[a][b] = c;
	}

	for(i = 0; i < G->numVertexes; i++) {
		for(j = 0; j < G->numVertexes; j++) {
			if (G->arc[i][j]!=0 && G->arc[i][j]!=INFINITY)
				G->arc[j][i] =G->arc[i][j];
		}
	}
	cout << endl;
}

MSTree::~MSTree() {
    delete G;
	ofile.close();
}

void MSTree::Swapn(Edge *edges,int i, int j) {
    int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}

void MSTree::sort(Edge edges[])
{
	int i, j;
	for ( i = 0; i < G->numEdges; i++) {
		for ( j = i + 1; j < G->numEdges; j++) {
			if (edges[i].weight > edges[j].weight) {
				Swapn(edges, i, j);
			}
		}
	}
}

int MSTree::Find(int *parent, int f) {
    while ( parent[f] > 0) {
		f = parent[f];
	}
	return f;
}

void MSTree::Kruskal(){
    int i, j, n, m;
	int k = 0, sum = 0;
	int parent[MAXVEX]; // 定义一数组用来判断边与边是否形成环路
	
	Edge edges[MAXEDGE]; // 定义边集数组,edge的结构为begin,end,weight,均为整型

	// 用来构建边集数组并排序
	for ( i = 0; i < G->numVertexes-1; i++) {
		for (j = i + 1; j < G->numVertexes; j++) {
			if (G->arc[i][j]<INFINITY) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G->arc[i][j];
				k++;
			}
		}
	}
	sort(edges);

	for (i = 0; i < G->numVertexes; i++)
		parent[i] = 0; // 初始化数组值为0

	cout << "最小生成树(Kruskal)：\n";
	for (i = 0; i < G->numEdges; i++) { // 循环每一条边
		n = Find(parent,edges[i].begin);
		m = Find(parent,edges[i].end);
		if (n != m) { // 假如n与m不等，说明此边没有与现有的生成树形成环路
			parent[n] = m;	// 将此边的结尾顶点放入下标为起点的parent中
							// 表示此顶点已经在生成树集合中
			cout << setw(3) << edges[i].begin << setw(3) << edges[i].end << setw(3) << edges[i].weight << endl;
			ofile << setw(3) << edges[i].begin << setw(3) << edges[i].end << setw(3) << edges[i].weight << endl;
            sum += edges[i].weight;
		}
	}
    cout << "总权值："  << sum << endl;
	cout << endl;
	ofile << endl;
}

void MSTree::Prim() {
    int min, i, j, k;
    int sum = 0;
	int adjvex[MAXVEX];		// 保存相关顶点下标
	int lowcost[MAXVEX];	// 保存相关顶点间边的权值 
	lowcost[0] = 0;// 初始化第一个权值为0，即v0加入生成树 
			// lowcost的值为0，在这里就是此下标的顶点已经加入生成树 
	adjvex[0] = 0;			// 初始化第一个顶点下标为0 
	for(i = 1; i < G->numVertexes; i++)	{ // 循环除下标为0外的全部顶点 
		lowcost[i] = G->arc[0][i];	// 将v0顶点与之有边的权值存入数组 
		adjvex[i] = 0;					// 初始化都为v0的下标 
	}
	cout << "最小生成树(Prim)：\n";
	for(i = 1; i < G->numVertexes; i++) {
		min = INFINITY;	// 初始化最小权值为∞
		j = 1;k = 0;
		while(j < G->numVertexes) { // 循环全部顶点
			if(lowcost[j]!=0 && lowcost[j] < min) { // 保存最小权值到min
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		cout << setw(3) << adjvex[k] << setw(3) << k << setw(3) << G->arc[adjvex[k]][k] << endl;// 打印当前顶点边中权值最小的边 
		ofile << setw(3) << adjvex[k] << setw(3) << k << setw(3) << G->arc[adjvex[k]][k] << endl;
        sum += G->arc[adjvex[k]][k];
		lowcost[k] = 0;// 将当前顶点的权值设置为0,表示此顶点已经完成任务 
		for(j = 1; j < G->numVertexes; j++)	{ // 循环所有顶点 
			if(lowcost[j]!=0 && G->arc[k][j] < lowcost[j]) { // 如果下标为k顶点各边权值小于此前这些顶点未被加入生成树权值 
				lowcost[j] = G->arc[k][j];// 将较小的权值存入lowcost相应位置 
				adjvex[j] = k;				// 将下标为k的顶点存入adjvex 
			}
		}
	}
    cout << "总权值：" << sum << endl;
	cout << endl;
}

void MSTree::Print_Graph() {
	cout << "邻接矩阵：" << endl;
    for (int i = 0; i < G->numVertexes; i++) {
		for (int j = 0; j < G->numVertexes; j++) {
            if (G->arc[i][j] == INFINITY)
                cout <<  setw(4) << "**";
            else
			    cout << setw(4) << G->arc[i][j];
		}
        cout << endl;
	}
	cout << endl;
}
