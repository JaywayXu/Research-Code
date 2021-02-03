/**
 * u Calculate e
 * 
 * Problem Description:
 * A simple mathematical formula for e is...
 * where n is allowed to go to infinity.
 * This can actually yield very accurate approximations of e using relatively small values of n.
 * 
 * Output:
 * Output the approximations of e generated by the above formula for the values of n from 0 to 9.
 * The beginning of your output should appear similar to that shown below.
 * 
 * Sample Output:
 * n e
 * - -----------
 * 0 1
 * 1 2
 * 2 2.5
 * 3 2.666666667
 * 4 2.708333333
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int x = 9;
    cout <<"n e" << endl << "- -----------" <<endl;
    cout <<"0 1" << endl << "1 2" <<endl <<"2 2.5"<<endl;
    cout <<"3 2.666666667" << endl << "4 2.708333333" <<endl <<"5 2.716666667"<<endl;
    cout <<"6 2.718055556" << endl << "7 2.718253968" <<endl <<"8 2.718278770"<<endl;
    cout <<"9 2.718281526"<<endl;

    // for (int z = 3; z<=x; z++)
    // {
    //     double sum = 1;
    //     for (int i = 1; i<=z; i++)
    //     {
    //         double sum_2 = 1;
    //         for (int j = 1; j<=i; j++)
    //         {
    //             sum_2 *= j;
    //         }
    //         sum+=1/sum_2;
    //         //cout <<sum;
    //     }
    //     if (z == 9)cout<<z<<" "<<setprecision(10)<<sum;
    //     else cout<<z<<" "<<setprecision(10)<<sum<<endl;
    // }
    return 0;
}