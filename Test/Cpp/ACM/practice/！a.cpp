// ³¬Ê±

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

#define N 1000000

int main()
{
    bool prime[N];
    memset(prime, true, sizeof(prime));
    prime[0] = false;
    prime[1] = false;
    for (int i = 2; i*i<=N; i++)
    {
        if (prime[i])
        {
            int j = 2*i;
            while (j <= N)
            {
                prime[j] = false;
                j += i;
            }
        }
    }
    vector<int> list;
    for (int i = 0; i<N; i++)
        if (prime[i])
            list.push_back(i);
    map<int,int> maplist;
    int i = 1;
    for (vector<int>::iterator it=list.begin(); it!=list.end(); it++)
    {
        maplist.insert(make_pair(*it,i));
        i++;
    }
    int cint;
    while (cin>>cint)
    {
        if (1 == cint)
            cout << "0" << endl;
        else if (!prime[cint])
            cout << "1"  << endl;
        else
            cout << maplist[cint] << endl;
    }
    return 0;
}