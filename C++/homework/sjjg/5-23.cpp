#include <iostream>
#include "BinTree.h"
using namespace std;

int main() {
    BinTree<char> a;

    // a.CreateBinTree_PreIn();
    // a.Print_CinPre();
    // a.preOrder();
    // a.Print_CinIn();
    // a.inOrder();
    // a.postOrder();
    // a.Print();

    a.CreateBinTree_PostIn();
    a.Print_CinPost();
    a.postOrder();
    a.Print_CinIn();
    a.inOrder();
    a.preOrder();
    a.Print();

    // a.CreateBinTree_List();
    // a.Print();

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
