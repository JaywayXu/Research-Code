#include <iostream>
using namespace std;

int minJi(int *list, int n) {
    int minJ = 999999999;
    for(int i=0; i<n; i++) {
        if (list[i]%2 == 1 && list[i] < minJ) {
            minJ = list[i];
        }
    }
    return minJ;
}

int main() {
    int n;
    int list[100];
    while(cin>>n) {
        int sum=0;
        for(int i=0; i<n; i++) {
            cin >> list[i];
            sum += list[i];
        }
        if (sum%2 == 0) { //Å¼Êı
            cout << sum << endl;
        } else {
            int minj = minJi(list, n);
            cout << sum-minj << endl;
        }
    }
    return 0;
}