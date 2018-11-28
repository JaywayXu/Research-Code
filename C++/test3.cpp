#include <iostream>
using namespace std;

int main()
{
    while(1)
    {
        int x = 0;
        int y = 0;
        int n;
        cin >> n;
        for (int i=1; i<=n; i++)
            for (int j=1; j<=i; j++)
                for (int k=1; k<=j; k++)
                    x++;
        y = (n*n*n+3*n*n+2*n)/6;
        cout << x << endl
            << y << endl;
    }
    return 0;
}