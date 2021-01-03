#include <iostream>
using namespace std;

int main () {
    int a,b=0;
    cin>>a;
    int old=a;
    while(a!=0){
        int c=a%10;
        b=b*10+c;
        a/=10;
    }
    if(old==b)cout<<"YES!";
    else cout<<"NO!";
    return 0;
}