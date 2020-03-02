#include <iostream>
#include <string>
using namespace std;

bool f(unsigned int tar,char ca,char cb,char cc,char cd,char ce)
{
    int a = (int)ca - 65 + 1;
    int b = (int)cb - 65 + 1;
    int c = (int)cc - 65 + 1;
    int d = (int)cd - 65 + 1;
    int e = (int)ce - 65 + 1;
    // cout << a <<endl<< b<<endl<<c<<endl<<d<<endl<<e<<endl;
    // int v; cin >>v;
    if ((a - b*b + c*c*c - d*d*d*d + e*e*e*e*e) == tar) return true;
    else return false;
}

int main()
{
    unsigned int x;
    while (cin>>x)
    {
        string str;
        cin >> str;
        if (x == 0 && !str.compare("END"))
        {
            break;
        }
        else
        {
            string s = "00000";
            for (int i=0; i<str.length(); i++)
            {
                for (int j=0; j<str.length(); j++)
                {
                    for (int k=0; k<str.length(); k++)
                    {
                        for (int l=0; l<str.length(); l++)
                        {
                            for (int n=0; n<str.length(); n++)
                            {
                                if (i!=j&&i!=k&&i!=l&&i!=n&&j!=k&&j!=l&&j!=n&&k!=l&&k!=n&&l!=n)
                                {
                                    if (f(x,str[i],str[j],str[k],str[l],str[n]))
                                    {
                                        if ((int)str[i]>(int)s[0])
                                        {
                                            s[0] = str[i];
                                            s[1] = str[j];
                                            s[2] = str[k];
                                            s[3] = str[l];
                                            s[4] = str[n];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (s.compare("00000")) cout << s <<endl;
            else cout << "no solution" << endl;
        }
    }
    return 0;
}