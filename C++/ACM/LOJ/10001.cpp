#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
    int s;
    int e;
    int v;
};

bool cmp(Node a, Node b)
{
    return (a.e < b.e);
}

int set[30000];
int main()
{
    int x, n;
    cin >> x >> n;
    Node list[5000];
    for (int i=0; i<n; i++)
    {
        cin >> list[i].s >> list[i].e >> list[i].v;
    }
    sort(list,list+n,cmp);
    
    int asr = 0;
    for (int i=0; i<n; i++)
    {
        int k = 0;
        for (int j=list[i].s; j<=list[i].e; j++)
            if (set[j]) k++;
        if (k >= list[i].v) continue;
        for (int j=list[i].e; j>=list[i].s; j--)
        {
            if (!set[j])
            {
                set[j] = 1;
                k++;
                asr++;
                if (k == list[i].v) break;
            }
        }
    }
    cout << asr << endl;
    return 0;
}