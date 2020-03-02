#ifndef LINFO_H
#define LINFO_H

#include <iostream>

using namespace std;

class Info {
public:
    int key;
    int number;
    int ldate;
    int rdate;
    Info *next;

    Info() :key(0), number(0),ldate(0), rdate(0), next(NULL) {}
    Info(int k, int n, int l, int d, Info *ptr)
        :key(k), number(n), ldate(l), rdate(d), next(ptr) {}
};

class LInfo {
public:
    LInfo() :first(NULL), size(0) {}
    ~LInfo() {makeEmpty();}

    void makeEmpty();
    void add(int k, int n, int l, int d);
    bool del(int n);
    void sort();
    bool empty();
    bool search(int n, Info *&get);
    bool contain(int k);
    bool contain(int k, int n);
    int getSize() {return size;}
    void print();
    void infoOut(int k, int datenow);
    int subAmount(int k, int l);
    bool getDeleteFirst(int k, Info *&get);

private:
    Info *first;
    int size;
};

void LInfo::makeEmpty() {
    Info *p;
    while (first != NULL) {
        p = first;
        first = first->next;
        delete p;
    }
    size = 0;
}

void LInfo::add(int k, int n, int l, int d) {
    first = new Info(k, n, l, d, first);
    size ++;
}

bool LInfo::del(int n) {
    Info *p = first;
    if (n == p->number) {
        first = p->next;
        delete p;
        size--;
        return true;
    }
    while (p->next) {
        if (n == p->next->number) {
            Info *pd = p->next;
            p->next = p->next->next;
            delete pd;
            size--;
            return true;            
        } else {
            p = p->next;
        }
    }
    return false;
}

void LInfo::sort() {
    Info *f, *p, *x, *y;
	f = NULL;
	if (first == NULL || first->next == NULL) return;
    add(0,-1,0,0);
	while(f != first->next->next) {
		for(p = first; p -> next -> next != f; p = p -> next) {
			if(p -> next -> rdate > p -> next -> next ->rdate) {
				x = p -> next;
				y = p -> next -> next;
				p -> next = y;
				x -> next = y -> next;
				y -> next = x;
			}
		}
		f = p -> next;
    }
    del(-1);
}

bool LInfo::empty() {
    return (NULL == first)? true : false;
}

bool LInfo::search(int n, Info *&get) {
    Info *p = first;
    while (p) {
        if (n == p->number) {
            get = p;
            return true;
        } else {
            p = p->next;
        }
    }
    return false;
}

bool LInfo::contain(int k) {
    Info *p = first;
    while (p) {
        if (k == p->key) {
            return true;
        } else {
            p = p->next;
        }
    }
    return false;
}

bool LInfo::contain(int k, int n) {
    Info *p = first;
    while (p) {
        if (k == p->key && n == p->number) {
            return true;
        } else {
            p = p->next;
        }
    }
    return false;
}

void LInfo::print() {
    sort();
    Info *p = first;
    while (p) {
        cout << p->key << ";" << p->number << ":" << p->ldate << "-" << p->rdate << endl;
        p = p->next;
    }
}

void LInfo::infoOut(int k ,int datenow) {
    sort();
    Info *p = first;
    while (p) {
        if (k == p->key) {
            if (p->rdate < datenow) {
                cout << "图书证号：" << p->number << "; 时间：" << p->ldate << "-" << p->rdate
                    << "（已逾期" << datenow - p->rdate << "天！）" << endl;
            } else {
                cout << "图书证号：" << p->number << "; 时间：" << p->ldate << "-" << p->rdate << endl;
            }
        }
        p = p->next;
    }
}

int LInfo::subAmount(int k, int l) {
    sort();
    int amount = 0;
    Info *p = first;
    while (p && p->rdate <= l) {
        if (k == p->key) {
            amount++;
        }
        p = p->next;
    }
    return amount;
}

bool LInfo::getDeleteFirst(int k, Info *&get) {
    sort();
    Info *p = first;
    if (k == p->key) {
        first = p->next;
        get = p;
        size--;
        return true;
    }
    while (p->next) {
        if (k == p->next->key) {
            Info *pd = p->next;
            p->next = p->next->next;
            get = pd;
            size--;
            return true;            
        } else {
            p = p->next;
        }
    }
    return false;
}

#endif // LINFO_H