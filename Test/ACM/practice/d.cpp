#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    while (getline(cin,str))
    {
        for (int i = 0; i<str.length(); i++)
        {
            if (str[i] == 'b')
                str[i] = ' ';
            else if (str[i] == 'q')
                str[i] = ',';
            else if (str[i] == 't')
                str[i] = '!';
            else if (str[i] == 'm')
                str[i] = 'l';
            else if (str[i] == 'i')
                str[i] = 'e';
            else if (str[i] == 'c')
                str[i] = 'a';
            else if (str[i] == 'a')
                str[i] = 'c';
            else if (str[i] == 'e')
                str[i] = 'i';
            else if (str[i] == 'l')
                str[i] = 'm';
        }
        cout << str << endl;
    }
}