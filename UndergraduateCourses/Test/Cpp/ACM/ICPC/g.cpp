#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
    string getString;
    while (cin >> getString) {
        string out;
        stack<char> st;
        if (getString.size() <= 0) continue;
        for (int i=0; i<getString.size(); i++) {
            if (getString[i] != ']') {
                st.push(getString[i]);
                //cout << getString[i];
            } else {
                string str = "";
                char x;
                x = st.top();
                st.pop();
                while(x != '[') {
                    str = x + str;
                    x = st.top();
                    st.pop();
                }
                //cout << str<<endl;
                char number = st.top();
                //cout << number <<endl;
                st.pop();
                int numberi = int(number) - int('0');
                //reverse(str.begin(),str.end());
                //cout << str << endl;
                //string strx;
                if (str.size() > 0 && numberi > 0) {
                    for (int j=0; j<numberi; j++) {
                        for (int x=0; x<str.size(); x++) {
                            st.push(str[x]);
                        }
                    }
                }
                // for (int j=0; j<strx.size(); j++) {
                //     st.push(strx[j]);
                // }
            }
        }
        if (!st.empty()) {
        while (!st.empty()) {
            char a = st.top();
            out = a + out;
            st.pop();
        }}
        //reverse(out.begin(), out.end());
        cout <<out<<endl;
    }
    return 0;
}