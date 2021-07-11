#include <iostream>
using namespace std;
int main()
{
    int x;
    while(cin>>x)
    {
        int arr[100];
        int sum = 0;
        for (int i = 0;i <100;i++)
        {
            arr[i] = 0;
        }
        for (int i = 0;i <x;i++)
        {
            cin>>arr[i];
        }
        for (int i = 0;i <x;i++)
        {
            if (arr[i]!=0)
            {
                sum += arr[i];
            }
        }
        cout <<sum<<endl;
    }
    return 0;
}