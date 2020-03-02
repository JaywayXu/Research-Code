/**
 * ’ª¿‡
 */

#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node<T>* link;
    node(node<T> *ptr = NULL) {link = ptr;}
    node(const T &item, node<T> *ptr = NULL) {
        data = item;
        link = ptr;
    }
};

template <typename T>
class stack {
public:
    stack():top_node(NULL) {};
    stack(T x) {top_node = new node<T>(x, top_node);};
    ~stack() {make_empty();};

    void make_empty();
    void push(const T &x);
    bool pop();
    T top();
    bool empty()const;

private:
    node<T> *top_node;
};

template <typename T>
void stack<T>::make_empty() {
    node<T> *p;
    while (top_node != NULL) {
        p = top_node;
        top_node = top_node->link;
        delete p;
    }
};

template <typename T>
void stack<T>::push(const T &x) {
    top_node = new node<T>(x, top_node);
};

template <typename T>
bool stack<T>::pop() {
    if (empty()) return false;
    node<T> *p = top_node;
    top_node = top_node->link;
    delete p;
    return true;
};

template <typename T>
T stack<T>::top() {
    return top_node->data;
};

template <typename T>
bool stack<T>::empty()const {
    return (NULL == top_node)? true : false;
};
