#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int step,mod;
    string str("    Good Choice");
    string bad("    Bad Choice");
    while (cin >> step >> mod)
    {
        vector<int> arr;
        int temp;
        temp = (step)%mod;
        arr.push_back(temp);
        for (int i = 1; i<mod; i++)
        {
            temp = (arr[i-1]+step)%mod;
            arr.push_back(temp);
        }
        vector<int> count(arr.size(), 0);
        for (int i = 0; i<arr.size(); i++)
        {
            if (count[arr[i]] == 1) str = bad;
            count[arr[i]] = 1;
        }
        cout << setiosflags(ios::right) << setw(10) << step
            << setiosflags(ios::right) << setw(10) << mod
            << setiosflags(ios::left)  << str << endl << endl;
    }
    return 0;
}