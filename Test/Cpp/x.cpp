#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1000
using namespace std;

struct node
{
	int to;	  //边连接的下一个节点
	int next; //记录前一条边（用于回溯）
	int w;
} edge[maxn * 2];

struct point
{
	int gra;
	int v;
} extra[maxn], defic[maxn];

int head[maxn * 2]; //每个点所在的边号（每条边连续出现2次u->v,v->u）
int fath[maxn];		//节点的父节点
int gran[maxn];		//节点的倒数第二个的祖先节点（所在树的第二层的节点）
int dis[maxn];		//节点到根节点的距离
int arm[maxn];		//军队所在城市点
int cal[maxn], tim[maxn], b[maxn];
int n;		 //节点个数
int m;		 //军队数
int tot = 0; //树的第二层节点的个数
int cnt = 0; //边号（每条边连续出现2次u->v,v->u）
int sum = 0, na = 0, nc = 0;

bool comp(const point &a, const point &b)
{
	return a.v > b.v;
}

void add(int, int, int); //建图
void dfs(int);			 //处理出要被覆盖的点和已被覆盖的点
void cal_tim(int);		 //处理出每个军队的能力，能到，不能到
void cal_extra(int);	 //能到的还有多少剩余
void cal_defic();		 //不能到的还差多少
bool remedy();			 //能到的能不能补齐不能到的
bool ok(int);			 //二分的时间是否够（其实就是调用以上四个函数）
void conn_anc(int);		 //处理出各个城市所属的直辖市，根节点的儿子
int erfen();			 //二分时间

int main()
{
	cin >> n;
	memset(head, 0, sizeof(head));
	//输入边
	for (int i = 1; i < n; i++)
	{
		int x, y, ww;
		cin >> x >> y >> ww;
		//每次插入两条反向边，目的是为了回溯
		//edge边数的逻辑是（单数：父->子；双数：子->父）
		add(x, y, ww);
		add(y, x, ww);
		if (x == 1 || y == 1)
			tot++;
	}

	cin >> m;
	if (tot > m) //判断军队数量是否小于第二层节点数量（小于则无解）
	{
		cout << -1;
		return 0;
	}

	//遍历获取所有节点的父节点、第二层祖先节点、到根节点的距离
	conn_anc(1);

	//输入军队
	for (int i = 1; i <= m; i++)
		cin >> arm[i];
	sort(arm + 1, arm + 1 + m);

	cout << erfen();
	return 0;
}

void add(int u, int v, int ww)
{
	cnt++;
	edge[cnt].to = v;		  //边的下一个点
	edge[cnt].next = head[u]; //存储回溯的边
	edge[cnt].w = ww;		  //距离
	head[u] = cnt;			  //更新u点的最后插入的边
}

void conn_anc(int x)
{
	for (int i = head[x]; i; i = edge[i].next) //初始：带x点的最后插入的边；结束条件：没有回溯；迭代：回溯找上一条边
	{
		int vv = edge[i].to; //这条边连着的下一个点
		if (fath[x] != vv)	 //是否子节点（如果没有遇到则回溯父节点）
		{
			if (x == 1)		   //根节点，这时vv就是根节点的子节点（第二层的节点）
				gran[vv] = vv; //第二层祖先节点等于本身
			else
				gran[vv] = gran[x];		  //根据父节点存储的更新当前节点的第二层祖先节点
			fath[vv] = x;				  //更新父节点
			dis[vv] = dis[x] + edge[i].w; //当前节点到根节点的距离
			conn_anc(vv);				  //继续深度优先下一个点
		}
	}
}

void dfs(int root)
{
	int maxx = -1, now1 = 0, now2 = 0;
	for (int i = head[root]; i; i = edge[i].next) //初始：带x点的最后插入的边；结束条件：没有回溯；迭代：回溯找上一条边
	{
		int vv = edge[i].to;  //这条边连着的下一个点
		if (fath[root] != vv) //是否为子节点
		{
			dfs(vv); //继续深度优先子节点
			if (tim[vv] == -1)
				now2 = 1; //该点尚未被覆盖
			if (tim[vv] >= edge[i].w)
				now1 = 1; //该点可以被覆盖
			maxx = max(maxx, tim[vv] - edge[i].w);
		}
	}
	if (root != 1 && edge[head[root]].next) //当前点不是根节点 且 当前的边查找完需要回溯
	{
		if (now1)
			tim[root] = max(tim[root], maxx);
		else if (now2)
			tim[root] = max(tim[root], -1);
		else
			tim[root] = max(tim[root], 0);
	}
}

void cal_tim(int ti)
{
	for (int i = 1; i <= m; i++)
		if (dis[arm[i]] >= ti) //军队到根节点的距离大于所给的时间
			tim[arm[i]] = ti;
	dfs(1);
}

void cal_extra(int ti)
{
	for (int i = 1; i <= m; i++)
	{
		if (dis[arm[i]] < ti)
		{
			extra[++na].gra = gran[arm[i]];
			extra[na].v = ti - dis[arm[i]];
		}
	}
	sort(extra + 1, extra + na + 1, comp);
	for (int i = 1; i <= na; i++)
	{
		if (!cal[extra[i].gra])
			cal[extra[i].gra] = i;
		else if (extra[cal[extra[i].gra]].v > extra[i].v)
			cal[extra[i].gra] = i;
	}
}

void cal_defic()
{
	for (int i = head[1]; i; i = edge[i].next)
	{
		int vv = edge[i].to;
		if (tim[vv] == -1)
		{
			defic[++nc].gra = vv;
			defic[nc].v = edge[i].w;
		}
	}
	sort(defic + 1, defic + nc + 1, comp);
}

bool remedy()
{
	if (na < nc)
		return false;
	memset(b, 0, sizeof(b));
	int i = 1, j = 1;
	for (; i <= nc; i++)
	{
		if (!b[cal[defic[i].gra]] && cal[defic[i].gra])
			b[cal[defic[i].gra]] = 1;
		else
		{
			while (j <= na && b[j])
				j++;
			if (j > na || extra[j].v < defic[i].v)
				return false;
			b[j] = 1, j++;
		}
	}
	return true;
}

bool ok(int ti)
{
	memset(cal, 0, sizeof(cal));
	na = nc = 0;
	memset(tim, -1, sizeof(tim));
	cal_tim(ti);
	cal_extra(ti);
	cal_defic();
	return remedy();
}

int erfen()
{
	int l = -1, r = 999999999;
	//二分法，时间从0-999999999，每次对半分，直到找到符合的最小解
	while (l + 1 < r)
	{
		int mid = (l + r) / 2;
		if (ok(mid))
			r = mid;
		else
			l = mid;
	}
	return r;
}
