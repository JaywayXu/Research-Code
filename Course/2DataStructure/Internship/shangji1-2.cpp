#include <iostream>
#include "stack.h"
using namespace std;

struct xnode { // 结点结构体
    int x;
    xnode *link;
    xnode(xnode *ptr = NULL) {link = ptr; x = 0;}
    xnode(const int& item, xnode *ptr = NULL) {
        x = item;
        link = ptr;
    }
    void operator=(xnode &d) {
        x = d.x;
        link = d.link;
    }
};

class big_number { //大数类
public:
    big_number() {head = new xnode; head->link = new xnode(1);};
    ~big_number() {destory();};
    void destory();
    xnode *get_head() {return head;};
    void factorial(int n);
    friend ostream &operator<<(ostream &output, big_number &b);
private:
    xnode *head;
};

void big_number::factorial(int n) { //阶乘功能函数
    int flow; //储存溢出数据
    for (int i=1; i<=n; i++) { //将大数链表从1乘到n
        xnode *p = head->link;
        flow = 0;
        while (p) { //大数乘法
            p->x = i * p->x + flow;
            if (p->x >= 10 && !p->link) { //最后结点溢出，新建节点
                p->link = new xnode();
            }
            flow = p->x/10;
            p->x %= 10;
            p = p->link;
        }
    }
}

ostream &operator<<(ostream &out, big_number &b) { //重载友元输出函数，反转链表输出
    stack<int> st;
    xnode *p = b.get_head();
    while (p->link) { //链表数据成员入栈
        st.push(p->link->x);
        p = p->link;
    }
    while (!st.empty()) { //链表数据成员出栈
        out << st.top();
        st.pop();
    }
    return out;
}

void big_number::destory() { //删除链表申请的空间
    xnode *p;
    while (head != NULL) {
        p = head;
        head = head->link;
        delete p;
    }
}

int main() {
    int n;
    while (cin >> n && n > 0) {
        big_number out;
        out.factorial(n);
        cout << out << endl;
    }
    return 0;
}
