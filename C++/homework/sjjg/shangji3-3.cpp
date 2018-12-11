#include <iostream>
#include "AVLTree.h"

using namespace std;

int main() {
    AVLTree<int> avl;
    int num;
    while (1) {
        system("cls");
        cout << "1: Initial tree;   2: Insert data;\n"
             << "3: Search data;    4: Remove data;\n"
             << "5: Print tree;     0: Exit;\nInput: ";
        cin >> num;
        if (num == 0) break;
        switch (num) {
            case 1: avl.Init();cout<<"Succeed!\n"; break;
            case 2: {
                int x; cout << "Input data: "; cin >> x;
                avl.Insert(x)? cout<<"Succeed\n": cout<<"Failed\n";
            };break;
            case 3: {
                int x; cout << "Input data: "; cin >> x;
                avl.Search(x)? cout<<"True\n": cout<<"False\n";
            };break;
            case 4: {
                int x; cout << "Input data: "; cin >> x;
                avl.Remove(x)? cout<<"Succeed\n": cout<<"Failed\n";
            }break;
            case 5: avl.Print();break;
        }
        system("pause");
    }
    return 0;
}