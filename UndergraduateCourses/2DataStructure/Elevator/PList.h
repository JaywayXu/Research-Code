#ifndef PLIST_H
#define PLIST_H

#include "Passenger.h"

class Node {
public:
	Passenger data;
	Node* next;
};

class PList {
private:
	Node *head;
	Node *tail;

public:
	PList();
	~PList();

	Node *getHead() {return head;}
	Node *getTail() {return tail;}

	bool empty() {return (!head->next)? true: false;}
	void append(Passenger data);
	void remove(int id);
};

PList::PList() {
	head = new Node();
	tail = head;
}

PList::~PList() {
	Node *p;
    while (head != NULL) {
        p = head;
        head = head->next;
        delete p;
    }
}

void PList::append(Passenger data) {
	Node *pnew = new Node();
	pnew->data = data; pnew->next = NULL;
	if (head == NULL) {
		head = pnew;
		tail = pnew;
	} else {
		tail->next = pnew;
		tail = pnew;
	}
}

void PList::remove(int id) { //data为节点所存储的数据，查到就删除
	Node *ptemp = head->next;
	if (ptemp->data.getID() == id) {
		if (ptemp == tail) { //如果就一个节点
			head->next = ptemp->next;
			tail = head;
			delete ptemp;
			ptemp = NULL;
			return;
		} else { //如果是多个节点
			head->next = ptemp->next;
			delete ptemp;
			ptemp = NULL;
			return;
		}
	}
	while (ptemp->next != NULL) {
		if (ptemp->next->data.getID() == id) {
			if (ptemp->next == tail) {
				delete ptemp->next;
				ptemp->next = NULL;
				tail = ptemp;
				return;
			} else {
				Node *t = ptemp->next;
				ptemp->next = ptemp->next->next;
				delete t;
				return;
			}
		}
		ptemp = ptemp->next;
	}
}

#endif // PLIST_H