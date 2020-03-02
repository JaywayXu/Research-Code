#include <iostream>
using namespace std;
int main() {
    int a,b;
    while(cin >> a) {
        int x = 0;
        while (1)
        {
            if (a == 1) {
                break;
            }
            if (a%2 == 0) {
                a = a/2;
            } else {
                a = (3*a + 1)/2;
            }
            x++;
        }
        cout << x << endl;
    }
}