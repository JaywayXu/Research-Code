#include <iostream>
#include <string>

using namespace std;

int main()
{
    int a,b;
    cin>>a>>b;
    // while (cin>>a>>b)
    // {
        string str("");
        for (int i=0; i<a; i++)
        {
            string temp;
            cin >> temp;
            str = str + temp;
        }
        string no("No key can be found !");
        string y("Found key:");
        bool bo = false;
        for (int i=0; i<b; i++)
        {
            string a,b,c,d;
            cin >> a >> b >> c >> d;
            if (str.find(d) != string::npos)
            {
                bo = true;
                y = y + " " + a + " " + b + " " + c;
            }
        }
        if (bo)
            cout << y;
        else
            cout << no;
    // }
    return 0;
}