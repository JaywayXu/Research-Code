#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int x;
    while(cin>>x)
    {
        vector<int> v;
        for (int i = 0; i<x; i++)
        {
            int b;
            cin >> b;
            v.push_back(b);
        }
        int min = 222;
        int a = 0;
        int sum = 0;
        for(int i = 0; i<x; i++)
        {
            sum += v[i];
        }
        for(int i = 0; i<x; i++)
        {
            int t;
            if (v[i]) t = 1;
            else t = -1;
            if (a>0) a = 0;
            a += t;
            if (a<min) min = a;
        }
        int j=0;
        for (int i=0;i<x;i++)
        {
            if(v[i]==1)
            {
                j++;
            }
            else break;
        }
        if(x == 1 &&v[0] == 1)
        {
            cout << "0" << endl;
            continue;
        }
        if (j == x) sum--;
        if (min<=0) sum += (-min);
        cout << sum <<endl;
    }
    return 0;
}