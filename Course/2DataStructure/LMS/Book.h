#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    int key; // 书号关键字
    string name; // 书名
    string author; // 著者
    int amountNow; // 现存量
    int amountSum; // 总库存量

    Book() :key(0), name("none"), author("none"), amountNow(0), amountSum(0) {}
    Book(int k) :key(k) {}
    Book(int k, string n, string a, int an, int as) 
        :key(k), name(n), author(a), amountNow(an), amountSum(as) {}

    Book &operator=(Book &t);
    bool operator>(Book &t);
    bool operator<(Book &t);
    bool operator==(Book &t);

    friend ostream &operator<<(ostream& out, Book& t)
    { out << t.key << "; " << t.name << "; " << t.author << "; "
        << t.amountNow << "/" << t.amountSum; return out;}
};

Book &Book::operator=(Book &t) {
    if (this != &t) {
        this->key = t.key;
        this->name = t.name;
        this->author = t.author;
        this->amountNow = t.amountNow;
        this->amountSum = t.amountSum;
    }
    return *this;
}

bool Book::operator>(Book &t) {
    if(key > t.key) {
        return true;
    }
    return false;
}

bool Book::operator<(Book &t) {
    if(key < t.key) {
        return true;
    }
    return false;
}

bool Book::operator==(Book &t) {
    if(key == t.key) {
        return true;
    }
    return false;
}

#endif // BOOK_H