#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
using namespace std;

int main()
{
    int N;
    while (cin>>N && N!=0)
    {
        vector<double> x,y;
        double x_a,y_a;
        for (int i = 0; i<N; i++)
        {
            cin >> x_a >> y_a;
            x.push_back(x_a);
            y.push_back(y_a);
        }
        double min = 10000;
        double r;
        for (int i = 0; i<N-1; i++)
        {
            for (int j = i+1; j<N; j++)
            {
                r = sqrt((y[i]-y[j])*(y[i]-y[j])+(x[i]-x[j])*(x[i]-x[j]))/2;
                if (min > r) min=r;
            }
        }
        printf("%.2f\n",min);
    }
    return 0;
}