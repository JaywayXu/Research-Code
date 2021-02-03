#include <iostream>
#include "BinTree.h"

using namespace std;

int main() {
    BinTree<int> bt;
    bt.Insert(4);
    bt.Insert(4);
    bt.Insert(1);
    bt.Insert(2);
    bt.Insert(7);
    bt.Insert(5);
    bt.Print();
    bt.RemoveMax();
    bt.Print();
    cout << bt.IsBst() << endl;
    return 0;
}