#include <iostream>
#include <stack>
using namespace std;

void fun(int N, int B, stack<int>& st) {
    while (1) {
        if (N < B) {
            st.push(N);
            return;
        }
        else {
            st.push(N%B);
            N /= B;
        }
    }
}

int main(){
    stack<int> o;
    int n, b;
    while (cin >> n >> b) {
        fun(n, b, o);
        while (!o.empty()) {
            cout << o.top();
            o.pop();
        }
        cout << endl;
    }
    return 0;
}