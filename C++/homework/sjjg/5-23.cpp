#include <iostream>
#include <vector>
#include "BinTree.h"
using namespace std;

int main() {
    BinTree<char> a;
    a.CreateBinTree_1();
    a.Print();

    // cout << a.Height() << endl;
    // cout << a.Size() << endl;

    // a.preOrder();
    // a.inOrder();
    // a.postOrder();

    // cout << a.LeafNodeNum() << endl;

    // a.Conversion();
    // a.Print();
    
    // a.Find_PrintAncestor('d');

    return 0;
}
