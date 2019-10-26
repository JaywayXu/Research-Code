#include <iostream>
#include <vector>
#include <iomanip>
#include "que_disk.h"

using namespace std;

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
        if (type == 3) return 0;
        work w;
        w.run(type);
    }
    return 0;
}