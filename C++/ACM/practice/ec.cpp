#include <iostream>
#include <string>

using namespace std;

int main()
{
    int x;
    cin >> x;
    for (int j = 0; j<x; j++)
    {
        string c; int ing;
        cin >> c >> ing;
        int h1, h2;
        int weight;
        weight = (ing/6)+1;
        if (ing%2 == 0)
        {
            h1 = (ing/2)-2;
            h2 = (ing/2)-1;
        }
        else
        {
            h1 = (ing/2)-1;
            h2 = h1;
        }
        int num = h2;
        string sw(""), sn(""), aw(""), an("");
        for (int i=0; i<weight; i++)
        {
            sw = sw + " ";
            aw = aw + c;
        }
        for (int i=0; i<num; i++)
        {
            sn = sn + " ";
            an = an + c;
        }
 
        cout << sw << an << endl;
        for (int i=0; i<h1; i++)
        {
            cout << aw << sn << aw << endl;
        }
        cout << sw << an << endl;
        for (int i=0; i<h2; i++)
        {
            cout << aw << sn << aw << endl;
        }
        cout << sw << an << endl;
        if (j != x-1)
        {
            cout << endl;
        }
    }
    return 0;
}