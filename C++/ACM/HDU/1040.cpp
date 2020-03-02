#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int x;
    cin >> x;
    for (int i = 0; i<x; i++)
    {
        int y;
        cin >> y;
        vector<int> list;
        for (int j = 0; j<y; j++)
        {
            int a;
            cin >> a;
            list.push_back(a);
        }
        sort(list.begin(),list.end());
        for (int j = 0; j<y; j++)
        {
            if (j == y-1)
                cout << list[j] << endl;
            else
                cout << list[j] << " ";
        }
    }
    return 0;
}