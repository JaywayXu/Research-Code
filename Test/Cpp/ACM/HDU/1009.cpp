#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;

class Point
{
public:
    double j;
    double f;
    double per;
    void set(double a,double b)
    {j = a;f = b;per = a/b;}
};

int main()
{
    double M;int N;
    while (cin>>M>>N)
    {
        if (M==EOF&&N==EOF) break;
        else
        {
            Point arr[1000];
            double j,f;
            for (int i = 0; i<N; i++)
            {
                cin >> j >> f;
                arr[i].set(j,f);
            }
            for (int i = 0; i<N; i++)
            {
                for (int j = 0; j<N-i-1; j++)
                {
                    if (arr[j].per<arr[j+1].per)
                    {
                        Point tempp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = tempp;
                    }
                }
            }
            double sum = 0;
            for (int i = 0; i<N; i++)
            {
                if (M<arr[i].f)
                {
                    sum += (M/arr[i].f)*arr[i].j;
                    M = 0;
                    break;
                }
                else
                {
                    M -= arr[i].f;
                    sum += arr[i].j;
                }
            }
            printf("%.3f\n",sum);
        }
    }
    return 0;
}