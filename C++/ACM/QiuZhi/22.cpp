#include <iostream>
#include <vector>
using namespace std;

void fun(vector<string> &v, string s, string x) {
    if (s.length() == 0) {
        //cout << x << ',';
        v.push_back(x);
        return;
    }
    for (int i=0; i<s.length(); i++) {
        if (s[i] == s[i+1]) continue;
        string xx = x+s[i];
        string scopy = s;
        string ss = scopy.erase(i,1);
        fun(v,ss,xx);
    }
}

int main() {
    string a;
    while(cin >> a) {
        int size = a.length();
        for(int i=0; i<size-1; i++) {
            for (int j=0; j<size-i-1; j++) {
                if (a[j] > a[j+1]) {
                    char x = a[j];
                    a[j] = a[j+1];
                    a[j+1] = x;
                }
            }
        }
        vector<string> v;
        string x("");
        fun(v,a,x);
        for (int i=0; i<v.size()-1; i++) cout << v[i] << ",";
        cout << v[v.size()-1] << endl;
    }
}