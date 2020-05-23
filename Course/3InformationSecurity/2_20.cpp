#include <iostream>
using namespace std;

int main()
{
    string s = "sendmoremoney";
    //cin >> s;
    int x[100] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    string sa = "cashnotneeded";
    int xa[100];
    for (int i = 0; i < 13; i++)
    {
        //cin >> x[i];
        cout << int(s[i]) - int('a') + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < s.size(); i++)
    {
        s[i] = (int(s[i]) + 1 - int('a') + x[i]) % 26 + int('a') - 1;
        if (int(s[i]) - int('a') == -1)
            s[i] = 'z';
        cout << int(s[i]) - int('a') + 1 << " ";
    }
    cout << endl
         << s << endl;
    for (int i = 0; i < s.size(); i++)
    {
        if (int(sa[i]) - int(s[i]) < 0)
        {
            xa[i] = int(sa[i]) + 26 - int(s[i]);
        }
        else
        {
            xa[i] = int(sa[i]) - int(s[i]);
        }
        cout << xa[i] << ' ';
    }
    return 0;
}