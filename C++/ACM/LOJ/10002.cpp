#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Node
{
public:
    double s;
    double e;
};

bool cmp(Node a, Node b)
{
    return (a.s < b.s);
}

Node list[15000];
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n; double l, w;
        cin >> n >> l >> w;
        int num = 0;
        for (int i=0; i<n; i++)
        {
            double x, r;
            cin >> x >> r;
            if (r >= w/2)
            {
                list[num].s = x - sqrt(r*r - (w/2)*(w/2));
                list[num].e = x + sqrt(r*r - (w/2)*(w/2));
                num++;
            }
        }

        sort(list,list+num,cmp);

        int asr = 0; bool can = true;
        double temp = 0;
        while (temp < l)
        {
            asr++;
            double s = temp;
            for (int i=0; list[i].s<=s && i<=num; i++)
                if (temp<list[i].e) temp = list[i].e;
            if (s==temp && s<l)
            {
                can = false;
                cout << "-1" << endl;
                break;
            }
        }
        if (can) cout << asr << endl;
    }
    return 0;
}