#include <iostream>
#include <stack>
using namespace std;
int main() {
    int a;
    while(cin >> a) {
        stack<char> s;
        int num=0;
        for (int i=0; i<a; i++) {
            char ch;
            string st;
            cin >> ch >> st;
            if (st[0] == 'c') {
                if (s.empty()){
                    num++;
                } else {
                    s.pop();
                }
            } else {
                s.push('x');
            }
        }
        cout << num << endl;
    }
}