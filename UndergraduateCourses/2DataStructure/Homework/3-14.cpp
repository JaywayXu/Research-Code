#include <iostream>
#include <stack>
using namespace std;

int max(int a, int b) {return a>b?a:b;}

int Lmax(int A[], int N) {
    if (N <= 1) {
        return A[0];
    }
    else {
        return max(Lmax(A, N-1), A[N-1]);
    }
}

int Ladd(int A[], int N) {
    if (N <= 1) {
        return A[0];
    }
    else {
        return A[N-1] + Ladd(A, N-1);
    }
}

int Laverage(int A[], int N) {
    static int n = N;
    if (N <= 1) {
        return A[0];
    }
    else if (N == n) {
        return (A[N-1] + Laverage(A, N-1))/n;
    }
    else {
        return A[N-1] + Laverage(A, N-1);
    }
}

int main(){
    int A[5] = {1,4,3,5,2};
    cout << Lmax(A, 5) << endl
         << Ladd(A, 5) << endl
         << Laverage(A, 5) << endl;
    return 0;
}