#include <iostream>
using namespace std;

#define N 1010

int min(int i, int j)
{
    return i<j?i:j;
}

int main()
{
    int n;
    int a[N], b[N];
    cin >> n;
    for (int i=0; i<n; i++)
    {
        cin >> a[i];
    }
    for (int i=0; i<n; i++)
    {
        cin >> b[i];
    }

    int m[N];
    int x[N];
    for (int i=0; i<n; i++)
    {
        m[i] = min(a[i], b[i]);
        x[i] = i; 
    }
    for (int i=0; i<n-1; i++)
    {
        for (int j=i; j<n; j++)
        {
            if (m[i]>m[j])
            {
                int t = m[j];
                m[j] = m[i];
                m[i] = t;

                t = x[j];
                x[j] = x[i];
                x[i] = t;
            }
        }
    }
    int asr[N], j=0, k=n-1;
    for (int i=0; i<n; i++)
    {
        if (m[i] == a[x[i]])
        {
            asr[j] = x[i];
            j++;
        }
        else
        {
            asr[k] = x[i];
            k--;
        }
    }
    
    int q=0, t=0;
    for (int i=0; i<n; i++)
    {
        q += a[asr[i]];
        if (t<q) t = q;
        t += b[asr[i]];
    }

    cout << t << endl;
    for (int i=0; i<n; i++)
    {
        if (i == n-1) cout << asr[i]+1 << '\n';
        else cout << asr[i]+1 << " ";
    }
    return 0;
}