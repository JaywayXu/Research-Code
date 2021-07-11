#include <iostream>
using namespace std;

int gcd(int a,int b)
{
    if (0 == b) return a;
    return gcd(b, a%b);
}

int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        cout << a*b/gcd(a,b) << endl;;
    }
    return 0;
}