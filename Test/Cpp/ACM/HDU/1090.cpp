#include <iostream>
using namespace std;
int main()
{
    int x;
    cin>>x;
    int arr[100][2];
    for (int i = 0;i<x;i++)
    {
        cin >> arr[i][0] >> arr[i][1];
    }
    for (int i = 0;i<x;i++)
    {
        cout<<arr[i][0]+arr[i][1]<<endl;
    }
    return 0;
}