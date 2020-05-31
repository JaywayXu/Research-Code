#include <iostream>
using namespace std;
int main()
{
    int g;
    cin>>g;
    int arr[100][100];
    int sum[100];
    for(int j = 0;j<g;j++)
    {
        int x;
        cin>>x;
        for (int i = 0;i <x;i++)
        {
            cin>>arr[j][i];
        }
        for (int i = 0;i <x;i++)
        {
            if (arr[i]!=0)
            {
                sum[j] += arr[j][i];
            }
        }
    }
    for(int j = 0;j<g;j++)
    {
        cout<<sum[j]<<endl;
    }
    return 0;
}