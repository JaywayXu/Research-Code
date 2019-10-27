#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>
#include "que_page.h"

using namespace std;

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