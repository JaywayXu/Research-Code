#include <iostream>
#include <vector>
#include "BinTree.h"
using namespace std;

int main() {
    BinTree<char> a;
    vector<char> x,y,z;
    a.CreateBinTree_1();
    a.preOrder(x);
    for (int i=0; i<x.size(); i++) cout << x[i];
    cout << endl;
    a.inOrder(y);
    for (int i=0; i<y.size(); i++) cout << y[i];
    cout << endl;
    a.postOrder(z);
    for (int i=0; i<z.size(); i++) cout << z[i];
    cout << endl;
    a.Print();
    return 0;
}
