#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string list[10];
    ifstream ifile;
    ifile.open("copycat.in");
    int t;
    ifile >> t;
    for (int i=0; i<t; i++)
    {
        ifile >> list[i];
    }
    ifile.close();

    ofstream ofile;
    ofile.open("copycat.out");
    for (int i=0; i<t; i++)
    {
        if (i == t-1) ofile << list[i];
        else ofile << list[i] << endl;
    }
    return 0;
}