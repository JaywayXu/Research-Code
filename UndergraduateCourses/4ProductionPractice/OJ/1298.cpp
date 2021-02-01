#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;
    n = n*2-1;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int ni, nj;
            if (i >= n/2) ni = n-i;
            else ni = i+1;
            if (j >= n/2) nj = n-j;
            else nj = j+1;
            int min = ni>nj?nj:ni;
            cout << min << " ";
        }
        cout << endl;
    }
    return 0;
}
