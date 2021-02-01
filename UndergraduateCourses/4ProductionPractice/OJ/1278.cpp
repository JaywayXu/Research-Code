#include <iostream>
#include<math.h>
using namespace std;

int main () {
    for(int i=2;i<100;i++){
        int m=int(sqrt(i));
        int j;
        for(j=2;j<=m;j++){
            if(i%j==0)break;
        }
        if(j>m){
            cout<<i<<" ";
        }
    }
    return 0;
}