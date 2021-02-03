#include <iostream>
#include <string>
using namespace std;
int main()
{
    string x;
    string arr[100][100];
    int i = 0;
    int i_arr[100];
    int one = 0;
    while (cin >> x && !x.compare("START"))
    {
        getline(cin,arr[one][i]);
        // int ch[100];
        // cin.getline(ch,100);
        // arr[one][i].copy(ch,100,0); 
        // cin>>arr[one][i];
        while(arr[one][i].compare("END"))
        {
            i++;
            getline(cin,arr[one][i]);
            // int ch[100];
            // cin.getline(ch,100);
            // arr[one][i].copy(ch,100,0);
        }
        i -= 1;
        for (int j=0; j<=i; j++)
        {
            for(string::iterator it = arr[one][j].end(); it>=arr[one][j].begin(); it--)
            {
                if ((int)*it>=70 && (int)*it<=90)
                {
                    char h = *it;
                    *it = char((int)h-5);
                }
                else if((int)*it>=65 && (int)*it<70)
                {
                    char h = *it;
                    *it = char((int)h+21);
                }
            }
        }
        // for (int j=0; j<=i; j++)
        // {
        //     if (j == i) cout << arr[one][j] <<endl;
        //     else cout << arr[one][j] << " ";
        // }
        i_arr[one] = i;
        i = 0;
        one++;
    }
    for (int q = 0; q<=one; q++)
    {
        // if (q == one)
        // {
        //     for (int j=0; j<=i_arr[q]; j++)
        //     {
        //         cout << arr[q][j];
        //     }
        // }
        // else 
        // {
            for (int j=1; j<=i_arr[q]; j++)
            {
                cout << arr[q][j] << endl;
            }
        // }
    }
    return 0;
}