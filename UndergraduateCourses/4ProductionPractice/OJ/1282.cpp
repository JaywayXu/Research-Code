#include <iostream>
using namespace std;

int main () {
    int n;
    cin>>n;
    int *a=new int[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int found;
    cin>>found;
    int flag=-1;
    for(int i=0;i<n;i++){
        if(found==a[i])
            flag=i;
    }
    if(flag==-1)
        cout<<"Not Found";
    else
        for(int i=0;i<n;i++){
            if(i!=flag) cout<<a[i]<<endl;
        }
    return 0;
}