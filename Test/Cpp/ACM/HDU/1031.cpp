#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, m, k;
    while (cin>>n>>m>>k)
    {
        double arr[100][100];
        for (int i = 0; i<n; i++)
        {
            for (int j = 0; j<m; j++)
            {
                cin >> arr[i][j];
            }
        }
        vector<double> dlist;
        vector<int> ilist;
        for (int j = 0; j<m; j++)
        {
            double sum = 0;
            for (int i = 0; i<n; i++)
            {
                sum += arr[i][j];
            }
            // cout << sum << endl;
            dlist.push_back(sum);
            ilist.push_back(j+1);
        }
        for (int j = 0; j<m; j++)
        {
            for (int z = 0; z<m-j-1; z++)
            {
                if (dlist[z]<dlist[z+1])
                {
                    double dtemp = dlist[z];
                    dlist[z] = dlist[z+1];
                    dlist[z+1] = dtemp;
                    int itemp = ilist[z];
                    ilist[z] = ilist[z+1];
                    ilist[z+1] = itemp;
                }
            }
        }
        vector<int>::iterator it = ilist.begin();
        vector<int> out;
        for (int j = 0; j<k; j++)
        {
            out.push_back(*it);
            it++;
        }
        sort(out.begin(),out.end());
        vector<int>::iterator iter=out.end();
        iter--;
        for (; iter>=out.begin();iter--)
        {
            if (iter == out.begin())
                cout << *iter << endl;
            else
                cout << *iter << " ";
        }
    }
    return 0;
}
