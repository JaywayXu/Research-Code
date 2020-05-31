#include <iostream>
using namespace std;

bool f(int a, int b, int m)
{
    if ((a*a + b*b + m)%(a*b) == 0)
        return true;
    else
        return false;
}

int main()
{
    int x;
    cin >> x;
    for (int i = 0; i<x; i++)
    {
        int n, m;
        int c = 1;
        while(cin>>n>>m)
        {
            if (0 == n && 0 == m) break;
            else
            {
                int out = 0;
                for (int a = 1; a<n-1; a++)
                {
                    for (int b = a+1; b<n; b++)
                    {
                        if (f(a,b,m)) out++;
                    }
                }
                cout << "Case " << c << ": " << out << endl;
                c++;
            }
        }
        if (i != x-1)
            cout << endl;
    }
    return 0;
}