#include <iostream>
#include "LInfo.h"
#include "LMS.h"
#include "Book.h"
#include "BTree.h"

using namespace std;

int main() {
    // LInfo l;
    // l.add(1,1,1);
    // l.add(2,2,2);
    // l.add(3,3,3);
    // l.sort();
    // l.print();
    // Info *inf = new Info();
    // cout << l.search(1, inf) << endl
    //     << l.search(2, inf) << endl
    //     << l.search(3, inf) << endl
    //     << l.search(4, inf) << endl;
    LMS lms;
    lms.run();
    // Book a(1,"1","1",1,1);
    // Book b(1,"2","1",1,1);
    // Book c(3,"3","3",3,3);
    // BTree<Book> *ptr = new BTree<Book>();

    // ptr->insert(a);
    // ptr->insert(b);
    // ptr->insert(c);



    // int x;
    // while (cin>>x && x!=-1) {
    //     ptr->insert(x);
    //     ptr->display();
    // }
    // int y;
    // while (cin>>y && y!=-1) {
    //     ptr->remove(y);
    //     ptr->display();
    // }
    return 0;
}