#include <iostream>
using namespace std;

int main() {
    int n, d;
    while (cin >>n>>d)
    {
        int alice[100000][2];
        for (int i=0; i<n; i++) {
            cin >> alice[i][0] >> alice[i][1];
        }
        int maxGongJi = 0;
        for (int i=0; i<n; i++) {
            int sumGongJi = alice[i][1];
            if (i!=n-1) {
                for (int j=i+1; j<n; j++) {
                    if (abs(alice[j-1][0] - alice[j][0]) <= d) {
                        sumGongJi += alice[j][1];
                    } else break;
                }
            }
            if (sumGongJi > maxGongJi) {
                maxGongJi = sumGongJi;
            }
            // if (i!=0) {
            //     for (int j=i-1; j>=0; j--) {
            //         if (abs(alice[j][0] - alice[j+1][0]) <= d) {
            //             sumGongJi += alice[j][1];
            //         } else break;
            //     }
            // }
            // if (sumGongJi > maxGongJi) {
            //     maxGongJi = sumGongJi;
            // }
        }
        cout << maxGongJi << endl;
    }
    
    return 0;
}
