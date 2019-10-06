#include <iostream>
using namespace std;

class Node {
public:
    int num;
    Node *next;
};

class List {
public:
    Node *head;
    List(int);
    ~List();
    bool search_pre(int, Node *&);
};

List::List(int a) {
    head = new Node();
	Node *p = head,*q;
	for(int i=1;i<=a;i++)
	{
		q = new Node();
		q->num = i;
		p->next = q;
		p = q;
	}
}

List::~List() {
    Node *temp;
	while(head != head->next)
	{
		temp = head->next;
		head->next = temp->next;
		delete(temp);
		head = head->next;
	}
}

bool List::search_pre(int x, Node *&get) {
    Node *pre = head;
    while (pre->next != NULL) {
        if (pre->next->num == x) {
            get = pre;
            return true;
        }
        pre = pre->next;
    }
    return false;
}

int main() {
    List *x = new List(10); Node *get;
    x->search_pre(4, get);
    cout << get->num << endl;
    return 0;
}