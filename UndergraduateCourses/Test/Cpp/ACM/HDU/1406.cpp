#include <iostream>
#include <vector>
using namespace std;

bool f(int num)
{
    vector<int> yinshu;
    for (int i = 1; i<num; i++)
        if (0 == num%i)
            yinshu.push_back(i);
    int sum = 0;
    for (vector<int>::iterator it = yinshu.begin(); it<yinshu.end(); it++)
        sum += *it;
    if (sum == num) return true;
    else return false;
}

int main()
{
    int x;
    cin >> x;
    for (int i = 0; i<x; i++)
    {
        int num1,num2;
        cin >> num1 >> num2;
        int min,max;
        if (num1 < num2)
        {
            min = num1;
            max = num2;
        }
        else
        {
            min = num2;
            max = num1;
        }
        int out = 0;
        for (int j = min; j <= max; j++)
            if (f(j))
                out++;
        cout << out << endl;
    }
    return 0;
}