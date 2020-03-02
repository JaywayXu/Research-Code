/**
 * 操作系统上机第一题：作业调度
 * 1. 假设系统中可同时运行两道作业，给出每道作业的到达时间和运行时间，如下表所示：
 * 作业名	A	B	C	D	E	F	G	H	I	J
 * 到达时间	0	2	5	7	12	15	4	6	8	10
 * 运行时间	7	10	20	30	40	8	8	20	10	12
 * 2. 分别用先来先服务算法、短作业优先和响应比高者优先三种算法给出作业的调度顺序；
 * 3. 计算每一种算法的平均周转时间及平均带权周转时间并比较不同算法的优劣。
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class node
{
public:
    char name;
    int arr_t; //到达时间
    int run_t; //运行时间
    int in_t;  //开始运行的时间

    node() : name('*'), arr_t(0), run_t(0), in_t(0){};
    node(char n, int a, int r) : name(n), arr_t(a), run_t(r), in_t(0){};
    void operator=(const node &d)
    {
        this->name = d.name;
        this->arr_t = d.arr_t;
        this->run_t = d.run_t;
        this->in_t = d.in_t;
    }
};

class que
{
public:
    vector<node> v;
    void push(char, int, int);
    node pop();
    void sort_fcfs();
    void sort_sjf();
    void sort_hrrn(int);
};

void que::push(char n, int a, int r)
{
    v.push_back(node(n, a, r));
}

node que::pop()
{
    node d = v[0];
    v.erase(v.begin());
    return d;
}

void que::sort_fcfs()
{ //先来先服务排序
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (v[j].arr_t > v[j + 1].arr_t)
            {
                node d = v[j];
                v[j] = v[j + 1];
                v[j + 1] = d;
            }
        }
    }
}

void que::sort_sjf()
{ //短作业优先排序
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (v[j].run_t > v[j + 1].run_t)
            {
                node d = v[j];
                v[j] = v[j + 1];
                v[j + 1] = d;
            }
        }
    }
}

void que::sort_hrrn(int now_t)
{ //响应比高排序
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            double i1 = (double)(now_t - v[j].arr_t) / (double)(v[j].run_t) + 1;
            double i2 = (double)(now_t - v[j + 1].arr_t) / (double)(v[j + 1].run_t) + 1;
            if (i1 < i2)
            {
                node d = v[j];
                v[j] = v[j + 1];
                v[j + 1] = d;
            }
        }
    }
}

class work
{
private:
    int N;
    int now_t;
    que waitq;
    que readyq;
    node *r1, *r2;

    double zz_t;
    double dzz_t;

    node d1;
    node d2;

public:
    work();
    void run(int);
};

work::work()
{
    N = 10;
    char name[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}; //作业名字
    int arr_t[N] = {0, 2, 5, 7, 12, 15, 4, 6, 8, 10};                  //到达时间
    int run_t[N] = {7, 10, 20, 30, 40, 8, 8, 20, 10, 12};
    for (int i = 0; i < N; i++)
    {
        waitq.push(name[i], arr_t[i], run_t[i]);
    }
}

void work::run(int type)
{
    r1 = NULL;
    r2 = NULL;
    zz_t = 0;
    dzz_t = 0;
    now_t = 0;
    waitq.sort_fcfs();
    for (now_t = 0; waitq.v.size() || readyq.v.size() || r1 || r2; now_t++)
    {
        //已完成的进程退出
        if (r1)
        {
            if (r1->in_t + r1->run_t <= now_t)
            {
                int zz = now_t - r1->arr_t;
                zz_t += (double)zz;
                dzz_t += (double)zz / (double)r1->run_t;
                cout << setw(2) << now_t << "s" << setw(5) << r1->name << "     Finished Finished Finished Finished" << endl;
                r1 = NULL;
            }
        }
        if (r2)
        {
            if (r2->in_t + r2->run_t <= now_t)
            {
                int zz = now_t - r2->arr_t;
                zz_t += (double)zz;
                dzz_t += (double)zz / (double)r2->run_t;
                cout << setw(2) << now_t << "s" << setw(5) << r2->name << "     Finished Finished Finished Finished" << endl;
                r2 = NULL;
            }
        }

        //等待队列满足时间的进入就绪队列
        if (waitq.v[0].arr_t == now_t)
        {
            node d = waitq.pop();
            readyq.push(d.name, d.arr_t, d.run_t);
            cout << setw(2) << now_t << "s" << setw(5) << d.name << "     start to Wait" << endl;
        }

        //就绪队列排序
        switch (type)
        {
        case 0:
            readyq.sort_fcfs();
            break;
        case 1:
            readyq.sort_sjf();
            break;
        case 2:
            readyq.sort_hrrn(now_t);
            break;
        default:
            break;
        }

        //就绪队列作业进入运行
        if (readyq.v.size())
        {
            if (!r1)
            { //r1进程空闲
                d1 = readyq.pop();
                r1 = &d1;
                r1->in_t = now_t;
                cout << setw(2) << now_t << "s" << setw(5) << r1->name << "     run with process 1" << endl;
                //两个进程都有空闲且就绪队列有数据
                if (readyq.v.size())
                {
                    if (!r2)
                    {
                        d2 = readyq.pop();
                        r2 = &d2;
                        r2->in_t = now_t;
                        cout << setw(2) << now_t << "s" << setw(5) << r2->name << "     run with process 2" << endl;
                    }
                }
            }
            else if (!r2)
            { //r2进程空闲
                d2 = readyq.pop();
                r2 = &d2;
                r2->in_t = now_t;
                cout << setw(2) << now_t << "s" << setw(5) << r2->name << "     run with process 2" << endl;
            }
        }
    }
    zz_t /= N;
    dzz_t /= N;
    cout << "周转时间:      " << zz_t << endl
         << "带权周转时间:  " << dzz_t << endl;
}

int main()
{
    while (1)
    {
        int type;
        cout << "0: 先来先服务" << endl
             << "1: 短作业优先" << endl
             << "2: 响应比高优先" << endl
             << "3: 退出" << endl
             << "输入要使用的方法：";
        cin >> type;
        if (type == 3)
            return 0;
        work w;
        w.run(type);
    }
    return 0;
}
