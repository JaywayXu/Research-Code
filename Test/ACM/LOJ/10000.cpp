#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
    int s;
    int e;
};

bool cmp(Node a, Node b)
{
    return (a.e < b.e);
}

int main()
{
    int n;
    cin >> n;
    Node list[1000];
    for (int i=0; i<n; i++)
    {
        cin >> list[i].s >> list[i].e;
    }
    sort(list,list+n,cmp);
    Node tmp = list[0];
    int out = 1;
    for (int i=1; i<n; i++)
    {
        if (list[i].s >= tmp.e)
        {
            out++;
            tmp = list[i];
        }
    }
    cout << out << endl;
    return 0;
}