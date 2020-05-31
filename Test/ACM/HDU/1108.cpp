#include <iostream>
using namespace std;

int main()
{
    int x, y;
    while (cin>>x>>y)
    {
        int m = x, n = y, c = 1;
        while (c!=0)
        {
            c = m%n;
            m = n;
            n = c;
        }
        cout << x*y/m << endl;
    }
    return 0;
}
