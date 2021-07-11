/**
 * 求阶乘的位数
 * 斯特林公式：
 * log10(n!) = log10(sqrt(2?pi?n))+n?log10(n/e)
 */

#include <iostream>
#include <math.h>
using namespace std;

long long f(long long n)
{
    double PI = acos(double(-1));
    double e = exp(double(1));
    return (floor)(log10(sqrt(2*PI*n))+n*log10(n/e))+1;
}

int main()
{
    int  x;
    cin >> x;
    for (int i = 0; i<x; i++)
    {
        long long num;
        cin >> num;
        cout << f(num) <<endl;
    }
    return 0;
}