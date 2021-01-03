#include <iostream>
using namespace std;

int main () {
    int n,m;
    cin >> n >> m;
    int max=-1, t;
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++) {
            cin >> t;
            if (t > max) max = t;
        }
    cout << max;
    return 0;
}
