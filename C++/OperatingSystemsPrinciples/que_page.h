#include <iostream>
#include <vector>
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
