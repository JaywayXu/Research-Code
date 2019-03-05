#ifndef LMS_H
#define LMS_H

#include "BTree.h"
#include "Book.h"

class LMS {
public:
    LMS();
    ~LMS();

    void insert(); // 采编入库
    void remove(); // 清楚库存
    void lend(); // 借阅
    void back(); // 归还
    void show(); // 显示

    void showAuthor(); // 列出某著者全部著作
    void showBook(); // 列出某书状态
    void subscribe(); // 预约借书

private:
    BTree<Book> *lms;
};

LMS::LMS() {
    lms = new BTree<Book>();
}

LMS::~LMS() {
    delete lms;
}

void LMS::insert() {

}

void LMS::remove() {

}

void LMS::lend() {

}

void LMS::back() {

}

void LMS::show() {

}

void LMS::showAuthor() {

}

void LMS::showBook() {

}

void LMS::subscribe() {

}

#endif // LMS_H