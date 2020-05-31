#include <iostream>
#include <vector>
using namespace std;

bool f(int num)
{
    int count = 0;
    for(int j = 2; j<num; j++)
    {
        if (num%j == 0) count = 1;
    }
    if (count == 0) return 1;
    else return 0;
}

int main()
{
    int x,jishu = 1;
    while(cin>>x)
    {
        cout << "Case " << jishu << ":" <<endl;
        vector<int> arr;
        for (int i = 2; i<=x; i++)
        {
            arr.push_back(i);
        }
        vector<int> last(1,1);
        vector<int> temp = arr;
        bool can;
        for (int j = 0; j<x; j++)
        {
            for (int i = 0; i<x; i++)
            {
                can = true;
                vector<int>::iterator it = temp.begin();
                while (!temp.empty())
                {
                    if (it == temp.end())
                    {
                        can = false;
                        break;
                    }
                    if (f(last[i]+*(it)))
                    {
                        last.push_back(*(it));
                        temp.erase(it);
                        it = temp.begin();
                    }
                    else
                    {
                        it++;
                    }
                }
                // for (vector<int>::iterator it = temp.end()-1; it!=temp.begin()-2; it--)
                // {
                //     if (it == temp.begin())
                //     {
                //         can = false;
                //     }
                //     else if (f(last[i]+*(it)))
                //     {
                //         last.push_back(*(it));
                //         temp.erase(it);
                //     }
                // }
                if (can == false) break;
            }
            if (can == true)
            {
                for (vector<int>::iterator it = last.begin(); it!=last.end(); it++)
                {
                    if (it==last.end()-1)
                        cout << *(it) <<endl;
                    else
                        cout << *(it) << " ";
                }
            }
        }
        jishu++;
    }
    return 0;
}