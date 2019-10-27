#include <iostream>
#include <vector>
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
