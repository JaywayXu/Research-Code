#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define pi 3.1415926535
double findGao(double Yuanzhu[][3], int n, int &x) {
    // x
    double a,b,c;
    a = Yuanzhu[0][0];
    b = Yuanzhu[1][0];
    for(int i=2; i<n*2; i++) {
        c = Yuanzhu[i][0];
        if (abs(a - b) <= 10e-10) {
            if (abs(c - a) > 10e-10) {
                a = c;
            } else {
                continue;
            }
        } else {
            if (abs(c - a) > 10e-10 && abs(c-b) >10e-10) {
                break;
            } else {
                if (i == n*2-1) {
                    x = 0;
                    return abs(a-b);
                }
            }
        }
    }
    // y
    a = Yuanzhu[0][1];
    b = Yuanzhu[1][1];
    for(int i=2; i<n*2; i++) {
        c = Yuanzhu[i][1];
        if (abs(a - b) <= 10e-10) {
            if (abs(c - a) > 10e-10) {
                a = c;
            } else {
                continue;
            }
        } else {
            if (abs(c - a) > 10e-10 && abs(c-b) >10e-10) {
                break;
            } else {
                if (i == n*2-1) {
                    x = 1;
                    return abs(a-b);
                }
            }
        }
    }
    // z
    a = Yuanzhu[0][2];
    b = Yuanzhu[1][2];
    for(int i=2; i<n*2; i++) {
        c = Yuanzhu[i][2];
        if (abs(a - b) <= 10e-10) {
            if (abs(c - a) > 10e-10) {
                a = c;
            } else {
                continue;
            }
        } else {
            if (abs(c - a) > 10e-10 && abs(c-b) >10e-10) {
                break;
            } else {
                if (i == n*2-1) {
                    x = 2;
                    return abs(a-b);
                }
            }
        }
    }
    return 0;
}

double getLength(double x1,double y1,double x2, double y2) {
    double e=x1-x2;  
    double d=y1-y2;  
    double l=sqrt(e*e+d*d); 
    return l;
}

double findS(double YuanZhu[][3], int n, int x) {
    int a,b;
    switch (x) {
    case 0:
        a = 1;
        b = 2;
        break;
    case 1:
        a = 0;
        b = 2;
        break;
    case 2:
        a = 0;
        b = 1;
    }
    double length = 0;
    double x1 = YuanZhu[0][a];
    double y1 = YuanZhu[0][b];
    for (int i=1; i<n; i++) {
        double x2 = YuanZhu[i][a];
        double y2 = YuanZhu[i][b];
        double dist = getLength(x1,y1, x2, y2);
        if (dist > length) {
            length = dist;
        }
    }
    double r = length/2;
    return r*r*pi;
}


int main() {
    int num;
    //while(cin>>num) {
        cin >> num;
        for(int nu=0; nu<num; nu++) {
            int n = 0;
            cin >> n;
            double YuanZhu[1000][3];
            for(int i=0; i<n*2; i++) {
                for (int j=0; j<3; j++) {
                    cin >> YuanZhu[i][j];
                }
            }
            int x;
            double Gao = findGao(YuanZhu, n, x);
            //cout << Gao<<endl;
            double S = findS(YuanZhu, n, x);
            //cout << S<<endl;
            //cout << Gao*S << endl;
            cout<<setiosflags(ios::fixed)<<setprecision(6)<< Gao*S << endl;
        }
        
    //}
    return 0;
}



