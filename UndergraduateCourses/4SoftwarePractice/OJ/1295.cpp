#include <iostream>
using namespace std;

int jc(int n) {
    if (n==0 || n==1) return 1;
    else return n*jc(n-1);
}
int main () {
    int n;
    cin >> n;
    cout << jc(n);
    return 0;
}