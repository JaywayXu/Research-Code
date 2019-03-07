#ifndef LMS_H
#define LMS_H

#include "BTree.h"
#include "Book.h"
#include "LInfo.h"

class LMS {
public:
    LMS();
    ~LMS();

    void setTime(); // 设置当前时间
    void insert(); // 采编入库
    void remove(); // 清除库存
    void lend(); // 借阅
    void back(); // 归还
    void show(); // 显示

    void showAuthor(); // 列出某著者全部著作
    void showBook(); // 列出某书状态
    void subscribe(); // 预约借书

    void run();

private:
    BTree<Book> *bt;
    LInfo *linfo;
    int datenow;
};

LMS::LMS() {
    bt = new BTree<Book>();
    linfo = new LInfo();
    datenow  = 0;
}

LMS::~LMS() {
    delete bt;
    delete linfo;
}

void LMS::setTime() {
    cout << "请输入当前时间：";
    cin >> datenow;
    cout << "Success!" << endl;
}

void LMS::insert() {
    cout << "请输入要入库的书的书号、书名、著者、数量：";
    int k; string n; string a; int as;
    cin >> k >> n >> a >> as;
    Book *t = new Book(k,n,a,as,as);
    Book *b;
    if (bt->get(*t, b)) {
        if (b->name != n || b->author != a) {
            cout << "与库存信息不符！" << endl << "Faild!" << endl;
            return;
        }
        b->amountNow += as;
        b->amountSum += as;
        cout << "Success!" << endl;
        return;
    }
    bt->insert(*t)? cout << "Success!" << endl: cout << "Faild!" << endl;
}

void LMS::remove() {
    cout << "请输入要清除库存的书号：";
    int k;
    cin >> k;
    Book b(k);
    bt->remove(b)? cout << "Success!" << endl: cout << "Faild!" << endl;
}

void LMS::lend() {
    cout << "请输入借阅的书号、图书证号、归还期限（AABBCC）：";
    int k, n, d;
    cin >> k >> n >> d;
    Book b(k);
    if (bt->contain(b)) {
        Book *book;
        bt->get(b, book);
        if (book->amountNow <= 0) {
            cout << "该图书已没有库存！" << endl;
        } else {
            book->amountNow--;
            linfo->add(k, n, d);
            cout << "借阅成功！" << endl;
        }
    } else {
        cout << "仓库没有该书！" << endl;
    }
}

void LMS::back() {
    cout << "请输入要归还的书号、图书证号：";
    int k, n;
    cin >> k >> n;
    Book b(k);
    if (!bt->contain(b)) {
        cout << "书号错误，仓库没有该书！" << endl;
    } else {
        if (!linfo->contain(k, n)) {
            cout << "归还信息有误（归还表里无此信息）!" << endl;
        } else {
            Book *book;
            bt->get(b, book);
            if (book->amountNow >= book->amountSum) {
                cout << "归还信息有误（该书库存已是上限）！" << endl;
            } else {
                Info *info;
                linfo->search(n, info);
                if (datenow > info->date) {
                    cout << "已逾期，请付逾期金" << (datenow-info->date)*1 << "元。" << endl << "归还成功！";
                } else {
                    cout << "归还成功！" << endl;
                }
                linfo->del(n);
                book->amountNow++;
            }
        }
    }
}

void LMS::show() {
    bt->display();
}

void LMS::showAuthor() {

}

void LMS::showBook() {

}

void LMS::subscribe() {

}

void LMS::run() {
    cout << "《《《图书管理系统》》》" << endl;
    while(1) {
        cout << "1.采编入库 2.清除库存 3.借阅图书 4.归还图书" << endl
            << "5.显示库存 6.著者著作 7.图书状态 8.预约借书" << endl
            << "0.设置时间 -1.退出    请输入要使用的功能：";
        int input1;
        cin >> input1;
        if(-1 == input1) break;
        switch (input1)
        {
            case 0:
                setTime();
                break;
            case 1:
                insert();
                break;
            case 2:
                remove();
                break;
            case 3:
                lend();
                break;
            case 4:
                back();
                break;
            case 5:
                show();
                break;
            case 6:
                showAuthor();
                break;
            case 7:
                showBook();
                break;
            case 8:
                subscribe();
                break;
            default:
                cout << "请输入正确选项！" << endl;
                break;
        }
        system("pause");
    }
}

#endif // LMS_H