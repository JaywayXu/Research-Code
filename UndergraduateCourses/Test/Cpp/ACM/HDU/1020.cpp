#include <iostream>
#include <string>
using namespace std;

string f(string s)
{
    int num = 1;
    string outs;
    for (int i = 0; i<s.length(); i++)
    {
        if (i == s.length()-1)
        {
            if (num == 1)
            {
                outs = outs + s[i];
            }
            else
            {
                outs = outs + to_string(num) + s[i];
            }
        }
        else
        {
            if (s[i] == s[i+1])
            {
                num++;
            }
            else
            {
                if (num == 1)
                {
                    outs = outs + s[i];
                }
                else
                {
                    outs = outs + to_string(num) + s[i];
                }
                num = 1;
            }
        }
    }
    return outs;
}

int main()
{
    string l;
    getline(cin,l);
    int x = stoi(l);
    for (int i = 0; i<x; i++)
    {
        string line;
        getline(cin,line);
        cout << f(line) << endl;
    }
    return 0;
}