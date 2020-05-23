/**
 * 操作系统上机第五题：请求分页系统中的置换算法
 * 1.通过如下方法产生一指令序列，共 320 条指令：
 *  A.在[1，32k-2]的指令地址之间随机选取一起点,访问 M；
 *  B.顺序访问M+1；
 *  C.在[0，M-1]中随机选取M1，访问 M1；
 *  D.顺序访问M1+1；
 *  E.在[M1+2，32k-2]中随机选取M2，访问 M2；
 *  F.顺序访问M2+1；
 *  G.重复 A—F，直到执行 320 次指令。
 * 2.指令序列变换成页地址流设：
 *  （1）页面大小为 1K；
 *  （2） 分配给用户的内存页块个数为 4 页到 32 页,步长为1页；
 *  （3）用户虚存容量为 32K。
 * 3.计算并输出下述各种算法在不同内存页块下的命中率。
 *  A.先进先出（FIFO）页面置换算法
 *  B.最近最久未使用（LRU）页面置换算法
 *  C.最佳（Optimal）页面置换算法
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>

using namespace std;

class node
{
public:
    int num;
    int wait_t;

    node() : num(0), wait_t(0){};
    node(int n, int t) : num(n), wait_t(t){};
    void operator=(const node &d)
    {
        this->num = d.num;
        this->wait_t = d.wait_t;
    }
};

class que
{
public:
    vector<node> v;
    void push(int, int);
    void push(int);
    node pop();
    bool is_in(int, int);
    void choose_LRU(int);
    void choose_BEST(que &);
};

void que::push(int n, int t)
{
    v.push_back(node(n, t));
}

void que::push(int n)
{
    v.push_back(node(n, 0));
}

node que::pop()
{
    node d = v[0];
    v.erase(v.begin());
    return d;
}

bool que::is_in(int nu, int now_t)
{ //判断有没有在内存里
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        if (v[i].num == nu)
        {
            v[i].wait_t = now_t;
            return true;
        }
    }
    return false;
}

void que::choose_LRU(int now_t)
{ //最近最久未使用
    int n = v.size();
    int j = 0;
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        int max_now = now_t - v[i].wait_t;
        if (max_now >= max)
        {
            j = i;
            max = max_now;
        }
    }
    node d = v[j];
    v[j] = v[0];
    v[0] = d;
}

void que::choose_BEST(que &waitq)
{ //最佳
    int n = v.size();
    int wn = waitq.v.size();
    int max = 0;
    int x;
    for (int i = 0; i < n; i++)
    {
        int distance = 999;
        for (int j = 0; j < wn; j++)
        {
            if (v[i].num == waitq.v[j].num)
            {
                distance = j;
                break;
            }
        }
        if (distance >= max)
        {
            x = i;
            max = distance;
        }
    }
    node d = v[x];
    v[x] = v[0];
    v[0] = d;
}

class work
{
private:
    que waitq;
    que readyq;
    int mem_size;
    int get_it;
    int now_t;
    int sum;

public:
    work(int);
    void run(int);
};

work::work(int s)
{
    mem_size = s;
    get_it = 0;
    now_t = 0;
    sum = 320;

    //生成320个指令
    int i = 0;
    int m, m1, m2;
    srand((unsigned)time(NULL) * 100);
    while (1)
    {
        if (i <= sum)
        { //A [1,32k-2] choose m
            m = rand() % (32 * 1024 - 1) + 1;
            waitq.push(m / 1024);
            i++;
        }
        else
            break;
        if (i <= sum)
        { //B choose m+1
            waitq.push((m + 1) / 1024);
            i++;
        }
        else
            break;
        if (i <= sum)
        { //C [0,m-1] choose m1
            m1 = rand() % (m - 1);
            waitq.push(m1 / 1024);
            i++;
        }
        else
            break;
        if (i <= sum)
        { //D choose m1+1
            waitq.push((m1 + 1) / 1024);
            i++;
        }
        else
            break;
        if (i <= sum)
        { //E [m1+2,30] choose m2
            m2 = rand() % (32 * 1024 - 2 - (m1 + 2)) + (m1 + 2);
            waitq.push(m2 / 1024);
            i++;
        }
        else
            break;
        if (i <= sum)
        { //F choose m2+1
            waitq.push((m2 + 1) / 1024);
            i++;
        }
        else
            break;
    }
}

void work::run(int type)
{
    while (waitq.v.size())
    {
        int get_num = waitq.pop().num;
        if (readyq.is_in(get_num, now_t))
        { //在内存
            get_it++;
        }
        else
        {
            if (readyq.v.size() <= mem_size)
            { //内存未满
                readyq.push(get_num, now_t);
            }
            else
            {
                //方法
                switch (type)
                {
                case 0:
                    break;
                case 1:
                    readyq.choose_LRU(now_t);
                    break;
                case 2:
                    readyq.choose_BEST(waitq);
                    break;
                default:
                    break;
                }
                readyq.pop();
                readyq.push(get_num, now_t);
            }
        }
        now_t++;
    }
    cout << setw(8) << (double)get_it / sum * 100 << " %";
}

int main()
{
    for (int i = 4; i <= 32; i++)
    {
        cout << "memory size: " << setw(2) << i << "  ";
        work w1(i);
        cout << "   FIFO: ";
        w1.run(0);
        cout << "   ";
        work w2(i);
        cout << "LRU: ";
        w2.run(1);
        cout << "   ";
        work w3(i);
        cout << "BEST: ";
        w3.run(2);
        cout << endl;
    }
    return 0;
}