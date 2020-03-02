#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
    string x;
    while (cin>>x)
    {
        if (x[0]!='-')
            cout << x << endl;
        else
        {
            string s = x.substr(1,x.size()-1);
            int max = -1;
            int size = s.size();
            string o;
            if (s[size-2]>s[size-1])
            {
                o = s.substr(0,size-2) + s.substr(size-1,1);
            }
            else
            {
                o = s.substr(0,size-1);
            }
            if (atoi(o.c_str())==0)
                cout << o << endl;
            else    
                cout << "-" << o << endl;
            // for (int i = 0; i<size; i++)
            // {
            //     if (s[i]>max) max = s[i];
            // }
            // string out;
            // for (int i = 0; i<size; i++)
            // {
            //     if (s[size-i-1]==max)
            //     {
            //         out = s.substr(0,size-i-1) + s.substr(size-i,i);
            //         break;
            //     }
            // }
            // string out2;
            // for (int i=0; i<size-1; i++)
            // {
            //     if (s[i]>s[i+1])
            //     {
            //         out2 = s.substr(0,i) + s.substr(i+1,size-i);
            //         break;
            //     }
            // }
            // if (atoi(out.c_str())>atoi(out2.c_str()))
            // {
            //     cout <<atoi(out.c_str())<<" "<<atoi(out2.c_str());
            //     out = out2;
            // }
            // if (atoi(out.c_str())==0)
            //     cout << out << endl;
            // else    
            //     cout << "-" << out << endl;
        }
    }
    return 0;
}