#include <iostream>
using namespace std;
int main() {
    int a;
    while(cin >> a) {
        int list[50];
        for (int i=0; i<a; i++){
            cin >> list[i];
            while (list[i]%2 == 0)
            {
                list[i]/=2;
            }
        }
        int x =0;
        for (int i=0; i<a-1; i++){
            if (list[i] != list[i+1]) {
                x = 1;
                break;
            }
        }
        if (x==1) cout <<"NO"<<endl;
        else cout << "YES" << endl;
    }
}