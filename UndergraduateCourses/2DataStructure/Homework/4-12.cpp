#include <iostream>
using namespace std;

#define m 3
#define n 3

class node {
public:
    int x;
    int y;
};

bool fun(int A[m][n], node &out)  {
    for (int i=0; i<m; i++) {
        int min = A[i][0]; int tempj = 0;
        for (int j=1; j<n; j++) {
            if (A[i][j]<min) {
                min = A[i][j];
                tempj = j;
            }
        }
        int max = A[0][tempj]; int tempi = 0;
        for (int k=1; k<m; k++) {
            if (A[k][tempj]>max) {
                max = A[k][tempj];
                tempi = k;
            }
        }
        if(tempi == i) {
            out.x = tempi; out.y = tempj;
            return true;
        }
        else return false;
    }
}

int main() {
    int A[m][n] = {
        7  ,  8 ,   9 ,         
        8 ,   7  ,  3     ,     
        5,    6 ,   7      
    };
    node out;
    if(fun(A,out)) cout << out.x << "," << out.y << endl;
    else cout << "ÎÞ°°µã" << endl;
    return 0;
}