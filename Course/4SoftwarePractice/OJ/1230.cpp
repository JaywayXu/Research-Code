#include <iostream>
using namespace std;

int main () {
    double a,b,c;
    cin>>a>>b>>c;
    double avg=(a+b+c)/3.0;
    if(avg>=90)
        cout<<"A";
    else if(avg>=70)
        cout<<"B";
    else if(avg>=50)
        cout<<"C";
    else cout<<"F";
    return 0;
}