#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(int a, int b){return a>b;}

int main()
{
    int x,y;
    while(cin>>x>>y)
    {
        int min, max;
        if (x<y)
        {
            min = x;
            max = y;
        }
        else
        {
            min = y;
            max = x;
        }
        vector<int> sum;
        for (int i = min; i<=max; i++)
        {
            int n = i;
            int num = 0;
            while (1)
            {
                num++;
                if (n == 1) break;
                else
                {
                    if (n%2 == 1) n = (n*3)+1;
                    else n = n/2;
                }
            }
            sum.push_back(num);
        }
        sort(sum.begin(),sum.end(),compare);
        cout << x << " " << y << " " << *(sum.begin()) << endl;
    }
    return 0;
}