#include <iostream>
using namespace std;

int main () {
    int a,b;
    cin>>a>>b;
    int p=a*b;
    int s=a+b;
    int total=s*s+p*(s-a)*(p+b);
    cout<<total;
    return 0;
}
