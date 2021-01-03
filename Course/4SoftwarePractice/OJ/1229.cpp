#include <iostream>
using namespace std;

int main () {
    int a,b,c;
    cin>>a>>b>>c;
    int max=a;
    if(b>max)
        max=b;
    if(c>max)
        max=c;
    cout<<max;
    return 0;
}