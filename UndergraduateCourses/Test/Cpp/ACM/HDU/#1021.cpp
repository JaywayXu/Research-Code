#include <iostream>
#include <string>
using namespace std;

bool f(int n)
{
    int f1 = 4, f2 = 7, t;
    while (n--)
    {
        t = f2;
        f2 = (f1+f2)%3;
        f1 = t;
    }
    return f2 ? false : true;
}

int main()
{
    int cint;
    while (cin>>cint)
    {
        string s("no");
        if (f(cint))
                s = "yes";
        cout << s << endl;
    }
    return 0;
}
