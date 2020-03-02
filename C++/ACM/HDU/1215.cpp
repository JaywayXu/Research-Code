#include <iostream>
using namespace std;
int list[500001];
int main()
{
    list[0] = list[1] = 1;
    for(int i=1; i<=500000/2; i++)
		for(int j=i*2; j<=500000; j+=i)
			list[j]+=i;
    int x;
    cin >> x;
    for (int i=0; i<x; i++)
    {
        int a;
        cin >> a;
        cout << list[a] << endl;
    }
    return 0;
}
