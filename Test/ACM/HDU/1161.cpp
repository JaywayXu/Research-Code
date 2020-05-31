#include <iostream>
#include <string>
using namespace std;

int main()
{
    string eachline;
    while (getline(cin,eachline))
    {
        for (int i = 0; i<eachline.length(); i++)
        {
            if ((int)eachline[i] >= (int)'A' && (int)eachline[i] <= 'Z')
            {
                int i_s = (int)eachline[i] - (int)'A' + (int)'a';
                eachline[i] = i_s;
            }
        }
        cout << eachline << endl;
    }
    return 0;
}