#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    int x;
    while (cin>>x)
    {
        string o1, o2;
        cin >> o1 >> o2;
        stack<char> s;
        vector<string> v;
        int i1 = 0, i2 = 0;
        while(1)
        {
            if (i2 == x)
            {
                cout << "Yes." << endl;
                for (int i = 0; i<2*x; i++)
                {
                    cout << v[i] << endl;
                }
                break;
            }
            else if (i1 == x && s.top()!=o2[i2])
            {
                cout << "No." << endl;
                break;
            }
            else
            {
                if (o1[i1]==o2[i2])
                {
                    i1++;
                    v.push_back("in");
                    i2++;
                    v.push_back("out");
                }
                else if (!s.empty() && s.top()==o2[i2])
                {
                    s.pop();
                    i2++;
                    v.push_back("out");
                }
                else
                {
                    s.push(o1[i1]);
                    i1++;
                    v.push_back("in");
                }
            }
        }
        cout << "FINISH" << endl;
    }
    return 0;
}