#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int mod(char *ch,int num)
{
    int s = 0;
    for(int i=0; ch[i]!='\0'; i++)
        s = (s*10+ch[i]-'0')%num;
    return s;
}

int main()
{
    char a[300];int b;
    while (cin>>a>>b)
    {
        if (b == atoi(a))
        {
            cout << "infinity" << endl;
        }
        else
        {
            int num = 0;
            for (int i=1; i<=atoi(a); i++)
            {
                if (b == mod(a,i)) num++;
            }
            cout << num << endl;
        }
    }
    return 0;
}