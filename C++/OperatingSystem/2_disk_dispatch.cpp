/**
 * 操作系统上机第二题：磁盘调度
 * 1、对于如下给定的一组磁盘访问进行调度：
 *  请求服务到达	A	B	C	D	E	F	G	H	I	J	K	L	M	N
 *  访问的磁道号	30	50	100	180	20	90	150	70	80	10	160	120	40	110
 * 2、要求分别采用先来先服务、最短寻道优先以及电梯调度算法进行调度；
 * 3、要求给出每种算法中磁盘访问的顺序，计算出平均移动道数；
 * 4、假定当前读写头在90号，电梯调度算法向磁道号增加的方向移动。
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class node
{
public:
    char name;
    int num;

    node() : name('*'), num(0){};
    node(char na, int nu) : name(na), num(nu){};
    void operator=(const node &d)
    {
        this->name = d.name;
        this->num = d.num;
    }
};

class que
{
public:
    vector<node> v;
    void push(char, int);
    node pop();
    void choose_short(int);
    void choose_elevator(int, int &);
};

void que::push(char na, int nu)
{
    v.push_back(node(na, nu));
}

node que::pop()
{
    node d = v[0];
    v.erase(v.begin());
    return d;
}

void que::choose_short(int now_num)
{ //最短距离优先，把最短距离的磁道放在队列开始
    int n = v.size();
    int j = 0;
    int min = 999;
    for (int i = 0; i < n; i++)
    {
        int min_now = abs(v[i].num - now_num);
        if (min_now <= min)
        {
            j = i;
            min = min_now;
        }
    }
    node d = v[j];
    v[j] = v[0];
    v[0] = d;
}

void que::choose_elevator(int now_num, int &f)
{ //电梯调度选择，选择在运行方向最近的
    int n = v.size();
    if (f == 1)
    {
    f1:
        int j = 0;
        int min = 999;
        int min_t = min;
        for (int i = 0; i < n; i++)
        {
            int min_now = v[i].num - now_num;
            if (min_now >= 0 && abs(min_now) <= abs(min))
            {
                j = i;
                min = abs(min_now);
            }
        }
        if (min == min_t)
        { //改变方向
            f = 0;
            goto f2;
        }
        node d = v[j];
        v[j] = v[0];
        v[0] = d;
    }
    else
    {
    f2:
        int j = 0;
        int min = 999;
        int min_t = min;
        for (int i = 0; i < n; i++)
        {
            int min_now = v[i].num - now_num;
            if (min_now <= 0 && abs(min_now) <= abs(min))
            {
                j = i;
                min = abs(min_now);
            }
        }
        if (min == min_t)
        { //改变方向
            f = 1;
            goto f1;
        }
        node d = v[j];
        v[j] = v[0];
        v[0] = d;
    }
}

class work
{
private:
    int N;
    que waitq;
    node *r;
    int now_num; //当前磁道
    double ave_num;
    int f; //方向

public:
    work();
    void run(int);
};

work::work()
{
    r = NULL;
    N = 14;
    char name[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N'}; //作业名字
    int num[N] = {30, 50, 100, 180, 20, 90, 150, 70, 80, 10, 160, 120, 40, 110};           //到达时间
    for (int i = 0; i < N; i++)
    {
        waitq.push(name[i], num[i]);
    }
}

void work::run(int type)
{
    f = 1; //朝增大的方向移动
    ave_num = 0;
    now_num = 90;
    while (waitq.v.size())
    {
        //选择下一个要到达的磁道
        switch (type)
        {
        case 0:
            break;
        case 1:
            waitq.choose_short(now_num);
            break;
        case 2:
            waitq.choose_elevator(now_num, f);
            break;
        default:
            break;
        }
        node d = waitq.pop();
        r = &d;
        int mov_num = abs(now_num - r->num);
        ave_num += mov_num;
        cout << setw(3) << now_num << " -> " << r->name << setw(5) << r->num
             << "  mov " << setw(3) << mov_num << endl;
        now_num = r->num;
    }
    ave_num /= N;
    cout << "average mov: " << ave_num << endl;
}

int main()
{
    while (1)
    {
        int type;
        cout << "0: 先来先服务" << endl
             << "1: 最近寻道优先" << endl
             << "2: 电梯调度" << endl
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