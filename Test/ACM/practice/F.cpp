#include <iostream>
using namespace std;

int main()
{
    long long a,b;int num = 0;
    while(cin>>a>>b)
    {
        for (long long i = a+1; i<b; i++)
        {
            if(i%a==0 && b%i==0)
            {
                num++;
            }
        }
        cout <<num <<endl;
        num = 0;
    }
    return 0;
}