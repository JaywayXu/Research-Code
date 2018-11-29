#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <typename T>
struct BTNode {
    T data;
    BTNode<T> *lc, *rc;
    BTNode(): lc(NULL), rc(NULL) {}
    BTNode(T x, BTNode<T> *l=NULL, BTNode<T> *r=NULL)
        :data(x), lc(l), rc(r) {}
};

template <typename T>
class BinTree {
public:
    BinTree() {root=NULL; CreateBinTree(root);}
    ~BinTree() {destory(root);}
    bool IsEmpty() {return (NULL==root)?true:false;}
    BTNode<T> *Parent(BTNode<T> *current) {
        return (NULL==root || root==current)?NULL:Parent(root, current);
    }
    BTNode<T> *LeftChild(BTNode<T> *current) {
        return (NULL!=current)?current->lc:NULL;
    }
    BTNode<T> *RightChild(BTNode<T> *current) {
        return (NULL!=current)?current->rc:NULL;
    }
    int Height() {return Height(root);}
    int Size() {return Size(root);}
    BTNode<T> *getRoot()const {return root;}
    void preOrder(vector<T> &out)
        {preOrder(root, out);}
    void inOrder(vector<T> &out)
        {inOrder(root, out);}
    void postOrder(vector<T> &out)
        {postOrder(root, out);}
    void Print() {Print(root);}
    void CreateBinTree_1(){CreateBinTree_1(root);};
protected:
    BTNode<T> *root;
    void CreateBinTree_1(BTNode<T> *&subTree);
    void CreateBinTree(BTNode<T> *&subTree);
    void destory(BTNode<T> *subTree);
    int Height(BTNode<T> *subTree);
    int Size(BTNode<T> *subTree);
    BTNode<T> *Parent(BTNode<T> *subTree, BTNode<T> *current);
    void preOrder(BTNode<T> *subTree, vector<T> &out);
    void inOrder(BTNode<T> *subTree, vector<T> &out);
    void postOrder(BTNode<T> *subTree, vector<T> &out);
    void Print(BTNode<T> *subTree);
    int getLevel(BTNode<T> *current);
};

template <typename T>
void BinTree<T>::destory(BTNode<T> *subTree) {
    if (NULL != subTree) {
        destory(subTree->lc);
        destory(subTree->rc);
        delete subTree;
    }
};

template <typename T>
void BinTree<T>::CreateBinTree(BTNode<T> *&subTree) {
    
};

template <typename T>
void BinTree<T>::CreateBinTree_1(BTNode<T> *&subTree) {
    stack<BTNode<char> *> s;
    subTree = NULL;
    BTNode<char> *p, *t; int k;
    char c;
    cin >> c;
    while (';' != c) {
        switch (c) {
            case '(': s.push(p); k=1; break;
            case ')': t=s.top(); s.pop(); break;
            case ',': k=2; break;
            default: p = new BTNode<char>(c);
                if (NULL == subTree) subTree = p;
                else if (1 == k) {
                    t = s.top(); t->lc = p;
                } else {
                    t = s.top(); t->rc = p;
                }
        }
        cin >> c;
    }
};

template <typename T>
int BinTree<T>::Height(BTNode<T> *subTree) {
    if (NULL == subTree) return 0;
    else {
        int i = Height(subTree->lc);
        int j = Height(subTree->rc);
        return (i<j)? j+1: i+1;
    }
};

template <typename T>
int BinTree<T>::Size(BTNode<T> *subTree) {
    if (NULL == subTree) return 0;
    else return 1+Size(subTree->lc)+Size(subTree->rc);
};

template <typename T>
BTNode<T> *BinTree<T>::Parent(BTNode<T> *subTree, BTNode<T> *current) {
    if (NULL == subTree) return NULL;
    if (subTree->lc == current || subTree->rc == current) return subTree;
    BTNode<T> *p = Parent(subTree->lc,current);
    if (p) return p;
    else return Parent(subTree->rc,current);
};

template <typename T>
void BinTree<T>::preOrder(BTNode<T> *subTree, vector<T> &out) {
    if (NULL != subTree) {
        out.push_back(subTree->data);
        preOrder(subTree->lc, out);
        preOrder(subTree->rc, out);
    }
};

template <typename T>
void BinTree<T>::inOrder(BTNode<T> *subTree, vector<T> &out) {
    if (NULL != subTree) {
        inOrder(subTree->lc, out);
        out.push_back(subTree->data);
        inOrder(subTree->rc, out);
    }
};

template <typename T>
void BinTree<T>::postOrder(BTNode<T> *subTree, vector<T> &out) {
    if (NULL != subTree) {
        postOrder(subTree->lc, out);
        postOrder(subTree->rc, out);
        out.push_back(subTree->data);
    }
};

template <typename T>
void BinTree<T>::Print(BTNode<T> *subTree) {
    if (NULL != subTree) {
        Print(subTree->lc);
        int x = getLevel(subTree) - 1;
        while (x--) cout << '\t';
        cout << subTree->data << endl;
        Print(subTree->rc);
    }
};

template <typename T>
int BinTree<T>::getLevel(BTNode<T> *current) {
    if (root == current) return 1;
    else return 1 + getLevel(Parent(current));
};
