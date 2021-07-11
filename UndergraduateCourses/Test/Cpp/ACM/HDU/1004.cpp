#include <iostream>
#include <string>
using namespace std;
int main()
{
    int x;
    string arr[1001];
    int count[1001];
    while (cin>>x && x!=0)
    {
        for (int i = 0; i<=x; i++) count[i] = 0;
        for (int i = 0; i<x; i++)
        {
            cin >> arr[i];
        }
        for (int i = 0; i<x; i++)
        {
            string temp = arr[i];
            for (int j = 0; j<x; j++)
            {
                if (!temp.compare(arr[j]))
                {
                    count[i] += 1;
                }
            }
        }
        int max = 0;
        int num = 0;
        for (int i = 0; i<x; i++)
        {
            if (count[i]>max)
            {
                max = count[i];
                num = i;
            }
        }
        cout << arr[num] << endl;
    }
    return 0;
}