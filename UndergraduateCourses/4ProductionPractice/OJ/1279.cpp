#include <iostream>
using namespace std;

int main () {
    cout<<"公鸡,母鸡,小鸡"<<endl;
    for(int i=0;i<=20;i++){
        for(int j=0;j<=(100-i*5)/3;j++){
            int k=(100-i*5-j*3)*3;
            if((i+j+k)==100)
                cout<<i<<","<<j<<","<<k<<endl;
        }
    }
    return 0;
}