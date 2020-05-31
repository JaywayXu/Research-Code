#include <iostream>
#include "BinTree.h"

using namespace std;

int main() {
    BinTree<int> bt;
    bt.CreateBinTree_PreIn();
    bt.Print();
    cout << bt.IsBst() << endl;
    return 0;
}
