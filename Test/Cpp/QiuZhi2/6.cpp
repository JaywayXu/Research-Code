#include <iostream>

using namespace std;

int main() {
    int n;
    while (cin>>n) {
        int arr[1000000];
        for (int i=0; i<n; i++) cin >> arr[i];
        int l=-1,r=-1;
        for (int i=0; i<n; i++) {
            l=-1,r=-1;
            for (int lj = i-1; lj>=0; lj--) {
                if (arr[lj] < arr[i]) {
                    l=lj;
                    break;
                }
            }
            for (int rj = i+1; rj<n; rj++) {
                if (arr[rj] < arr[i]) {
                    r=rj;
                    break;
                }
            }
            cout << l << ' ' << r << endl;
        }
    }
    return 0;
}