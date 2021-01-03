#include <iostream>
using namespace std;

#define N 10
#define M 10

int main () {
    int n,m;
    cin >> n >> m;
    int max=-99999, min = 99999, t;
    int arr[N][M];
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++) {
            cin >> arr[i][j];
        }
    //row
    for (int i=0; i<n; i++) {
        max=-99999;
        for (int j=0; j<m; j++) {
            if (arr[i][j] > max) max = arr[i][j];
        }
        cout << max << " ";
    }
    cout << endl;
    //column
    for (int j=0; j<m; j++) {
        min = 99999;
        for (int i=0; i<n; i++) {
            if (arr[i][j] < min) min = arr[i][j];
        }
        cout << min << " ";
    }
    cout << endl;
    return 0;
}
