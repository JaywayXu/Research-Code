#include <iostream>
using namespace std;
int main()
{
    int x;
    while(cin >> x)
    {
        unsigned long long sum = 0;
        for (int i = 0; i<x; i++)
        {
            sum += x-i;
        }
        cout << sum << endl << endl;
    }
    return 0;
}
