#include <iostream>
#include "BTree.h"

using namespace std;

int main() {
    BTree<int> *ptr = new BTree<int>();
    int x;
    while (cin>>x && x!=-1) {
        ptr->insert(x);
        ptr->display();
    }
    int y;
    while (cin>>y && y!=-1) {
        ptr->remove(y);
        ptr->display();
    }
    return 0;
}