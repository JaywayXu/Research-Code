#ifndef LMS_H
#define LMS_H

#include <iostream>
#include "BTree.h"
#include "Book.h"
#include "LInfo.h"

using namespace std;

const int LEND_TIME = 7;

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
    LInfo *subLinfo;
    int datenow;
};

LMS::LMS() {
    bt = new BTree<Book>();
    linfo = new LInfo();
    subLinfo = new LInfo();
    datenow  = 0;
}

LMS::~LMS() {
    delete bt;
    delete linfo;
    delete subLinfo;
}

void LMS::setTime() {
    cout << "请输入当前时间：";
    cin >> datenow;
    cout << "Success!" << endl;
}

void LMS::insert() {
    int input = 1;
    int k; string n; string a; int as;
    while (input != 0) {
        cout << "请输入要入库的书的书号、书名、著者、数量：";
        cin >> k >> n >> a >> as;
        Book *t = new Book(k,n,a,as,as);
        Book *b;
        if (bt->get(*t, b)) {
            if (b->name != n || b->author != a) {
                cout << "与库存信息不符！" << endl << "Faild!" << endl;
                continue;
            }
            b->amountNow += as;
            b->amountSum += as;
            cout << "Success!" << endl;
            return;
        }
        bt->insert(*t)? cout << "Success!" << endl: cout << "Faild!" << endl;
        cout << "输入0停止添加，输入1继续添加：";
        cin >> input;
    }
}

void LMS::remove() {
    cout << "请输入要清除库存的书号：";
    int k;
    cin >> k;
    Book b(k);
    bt->remove(b)? cout << "Success!" << endl: cout << "Faild!" << endl;
}

void LMS::lend() {
    cout << "请输入借阅的书号、图书证号：";
    int k, n;
    cin >> k >> n;
    Book b(k);
    if (bt->contain(b)) {
        Book *book;
        bt->get(b, book);
        if (book->amountNow <= 0) {
            cout << "该图书已没有库存！" << endl;
        } else {
            book->amountNow--;
            linfo->add(k, n, datenow, datenow+LEND_TIME);
            cout << "借阅成功！请" << LEND_TIME << "天之内归还，否则要付逾期金（1￥/天）" << endl;
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
                if (datenow > info->rdate) {
                    cout << "已逾期，请付逾期金" << (datenow-info->rdate)*1 << "元。" << endl;
                } else {
                    cout << "归还成功！" << endl;
                }
                linfo->del(n);
                if (book->amountNow == 0) { // 归还前没有库存,进行预约信息查找
                    if (subLinfo->contain(k)) { // 有预定此书的记录
                        Info *get;
                        subLinfo->getDeleteFirst(k, get);
                        linfo->add(get->key, get->number, datenow, datenow+LEND_TIME);
                        cout << endl << "~~系统提示~~" << endl;
                        cout << "借阅证号为‘" << get->number << "’的用户所借书号为‘" << get->key << "’的书已有库存，请取书！" << endl;
                        cout << "借阅成功！请" << LEND_TIME << "天之内归还，否则要付逾期金（1￥/天）" << endl;
                        delete get;
                        return;
                    }
                }
                book->amountNow++;
            }
        }
    }
}

void LMS::show() {
    bt->display();
}

void LMS::showAuthor() {
    cout << "请输入著者名:";
    string input;
    cin >> input;
    bt->printAuthor(input);
}

void LMS::showBook() {
    cout << "请输入要查找的书号：";
    int k;
    cin >> k;
    Book b(k);
    if (!(bt->contain(b))) {
        cout << "仓库没有该书！" << endl;
    } else {
        Book *book;
        bt->get(b, book);
        cout << "书号：" << book->key << endl
            << "书名：" << book->name << endl
            << "著者：" << book->author << endl
            << "库存：" << book->amountNow << "/" << book->amountSum << endl;
        if (book->amountNow == book->amountSum) {
            cout << "该书当前没有借阅记录" << endl;
        } else {
            linfo->infoOut(k, datenow);
        }
    }
}

void LMS::subscribe() {  
    cout << "请输入预定的书号、图书证号：";
    int k, n;
    cin >> k >> n;
    Book b(k);
    if (bt->contain(b)) {
        Book *book;
        bt->get(b, book);
        if (book->amountNow <= 0) { // 没有库存
            subLinfo->add(k, n, datenow, datenow);
            cout << "当前该书已无库存，系统会在有库存时提醒您！" << endl;
        } else {
            book->amountNow--;
            linfo->add(k, n, datenow, datenow+LEND_TIME);
            cout << "当前有库存，借阅成功！请" << LEND_TIME << "天之内归还，否则要付逾期金（1￥/天）" << endl;
        }
    } else {
        cout << "仓库没有该书！" << endl;
    }

    // 此段是我理解错要求
    // cout << "请输入预定的书号、图书证号、预定日期、借阅天数：";
    // int k, n, l, d;
    // cin >> k >> n >> l >> d;
    // Book b(k);
    // if (bt->contain(b)) {
    //     Book *book;
    //     bt->get(b, book);
    //     if (book->amountNow <= 0) { // 没有当前库存
    //         if (book->amountNow + linfo->subAmount(k, l) <= 0) {
    //             cout << "该图书到预定时间仍没有库存！" << endl;
    //         } else {
    //             book->amountNow--;
    //         linfo->add(k, n, l, l+d);
    //         cout << "预定成功！" << endl;
    //         }
    //     } else {
    //         book->amountNow--;
    //         linfo->add(k, n, l, l+d);
    //         cout << "预定成功！" << endl;
    //     }
    // } else {
    //     cout << "仓库没有该书！" << endl;
    // }
}

void LMS::run() {
    cout << "~~~~~~图书管理系统~~~~~~" << endl;
    while(1) {
        cout<< "      1.采编入库" << endl
            << "      2.清除库存" << endl
            << "      3.借阅图书" << endl
            << "      4.归还图书" << endl
            << "      5.显示库存" << endl
            << "      6.著者著作" << endl
            << "      7.图书状态" << endl
            << "      8.预约借书" << endl
            << "      0.设置时间"  << endl
            << "     -1.退出" << endl
            << "请输入要使用的功能：";
        int input;
        cin >> input;
        if(-1 == input) break;
        switch (input)
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