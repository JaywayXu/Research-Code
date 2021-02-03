#include <iostream>
#include <string>
using namespace std;

string f(string s)
{
    int len = s.length();
    int sum = 0;
    for (int i = 0; i<len; i++)
    {
        sum += (int)(s[i]-'0');
    }
    return to_string(sum);
}

int main()
{
    string s;
    while (cin>>s && s.compare("0"))
    {
        while (s.length()!=1)
        {
            s = f(s);
        }
        cout << s <<endl;
    }
    return 0;
}