#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    while(1) {
        float x;
        int e,j=0,ne,o; //尾数、阶码、数符、输出
        cin >> x;

        x<0 ? ne=1 : ne=0;
        x = fabs(x);

        while(x<1||x>=2) { //移至IEEE标准规定的位置
            if(x<1) {x*=2;j--;}
            if(x>=2) {x/=2;j++;}
        }

        j += pow(2,7); //移码运算

        x -= 1;
        x *= pow(2,23); //左移至去掉小数点
        e = x;
        ne *= pow(2,31); //左移31位
        j *= pow(2,23); //左移23位
        o = ne + j + e;
        cout << hex << o << endl << endl;
    }
    return 0;
}