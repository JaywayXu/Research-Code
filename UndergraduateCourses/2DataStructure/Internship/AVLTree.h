#include <iostream>
#include "stack.h"

using namespace std;

template <typename T>
struct AVLNode {
    int bf;
    T data;
    AVLNode<T> *left, *right;
    AVLNode(): left(NULL), right(NULL), bf(0) {}
    AVLNode(T x, AVLNode<T> *l=NULL, AVLNode<T> *r=NULL)
        :data(x), left(l), right(r), bf(0) {}
};

template <typename T>
class AVLTree {
public:
    AVLTree(): root(NULL) {}
    ~AVLTree() {destory(root);}
    void Init(); // 初始化树
    bool Search(const T x) {return Search(x, root)? true: false;} // 查找
    bool Insert(T el) {return Insert(root, el);} // 插入
    bool Remove(T x) {return Remove(root, x);}  //删除
    void Print() {Print(root);}  // 输出

protected:
    AVLNode<T> *root;
    void destory(AVLNode<T> *&ptr);
    AVLNode<T> *Search(T x, AVLNode<T> *&ptr);
    bool Insert(AVLNode<T> *&ptr, T el);
    bool Remove(AVLNode<T> *&ptr, T x);
    void Print(AVLNode<T> *ptr);
    void RotateL(AVLNode<T> *&ptr);
    void RotateR(AVLNode<T> *&ptr);
    void RotateLR(AVLNode<T> *&ptr);
    void RotateRL(AVLNode<T> *&ptr);
    int getLevel(AVLNode<T> *current);
    AVLNode<T> *Parent(AVLNode<T> *ptr, AVLNode<T> *current);
};

template <typename T>
void AVLTree<T>::Init() {
    destory(root); root = NULL;
    T item; T ref;
    cout << "Your ref(To end input): ";
    cin >> ref;
    cout << "Input data(End with ref): ";
    cin >> item;
    while(item != ref) {
        Insert(item);
        cout << "Input data(End with ref): ";
        cin >> item;
    }
};

template <typename T>
void AVLTree<T>::destory(AVLNode<T> *&ptr) {
    if (ptr) {
        destory(ptr->left);
        destory(ptr->right);
        delete ptr;
    }
};

template <typename T>
AVLNode<T> *AVLTree<T>::Search(T x, AVLNode<T> *&ptr) {
    if (!ptr) return NULL;
    else if (x < ptr->data) return Search(x, ptr->left);
    else if (x > ptr->data) return Search(x, ptr->right);
    else return ptr;
};

template <typename T>
bool AVLTree<T>::Insert(AVLNode<T> *&ptr, T el) {
    AVLNode<T> *pr = NULL, *p = ptr, *q; int d;
    stack<AVLNode<T> *> st;
    while (p) {
        if (el == p->data) return false;
        pr = p; st.push(pr);
        if (el < p->data) p = p->left;
        else p = p->right;
    }
    p = new AVLNode<T>(el);
    if (!p) {cout << "no space!" << endl; exit(1);}
    if (!pr) {ptr = p; return true;}
    if (el < pr->data) pr->left = p;
    else pr->right = p;
    while (!st.empty()) {
        pr = st.top(); st.pop();
        if (p == pr->left) pr->bf--;
        else pr->bf++;
        if (pr->bf == 0) break;
        if (pr->bf == 1 || pr->bf == -1) p = pr;
        else {
            d = (pr->bf < 0)? -1: 1;
            if (p->bf == d) {
                if (d == -1) RotateR(pr);
                else RotateL(pr);
            } else {
                if (d == -1) RotateLR(pr);
                else RotateRL(pr);
            }
            break;
        }
    }
    if (st.empty()) ptr = pr;
    else {
        q = st.top();
        if (q->data > pr->data) q->left = pr;
        else q->right = pr;
    }
    return true;
};


// 错误
// template <typename T>
// bool AVLTree<T>::Remove(AVLNode<T> *&ptr, T x) {
//     AVLNode<T> *pr = NULL, *p = ptr, *q, *ppr; int d, dd = 0;
//     stack<AVLNode<T> *> st;
//     while (p) {
//         if (x == p->data) break;
//         pr = p; st.push(pr);
//         if (x < p->data) p = p->left;
//         else p = p->right;
//     }
//     if (!p) return false;
//     if (p->left && p->right) {
//         pr = p; st.push(pr);
//         q = p->left;
//         while (q->right) {
//             pr = q; st.push(pr);
//             q = q->right;
//         }
//         p->data = q->data;
//         p = q;
//     }
//     if (p->left) q = p->left;
//     else q = p->right;
//     if (!pr) ptr = q;
//     else {
//         if (pr->left == p) pr->left = q;
//         else pr->right = q;
//         while (!st.empty()) {
//             pr = st.top(); st.pop();
//             if (!pr->left && !pr->right) {
//                 pr->bf = 0;
//                 continue;
//             }
//             if (pr->right == q) pr->bf--;
//             else pr->bf++;
//             if (!st.empty()) {
//                 ppr = st.top();
//                 dd = (ppr->left == pr)? -1: 1;
//             }
//             else dd = 0;
//             if (pr->bf == 1 || pr->bf == -1) break;
//             if (pr->bf != 0) {
//                 if (pr->bf < 0) {d = -1; q = pr->left;}
//                 else {d = 1; q = pr->right;}
//                 if (q->bf == 0) {
//                     if (d == -1) {
//                         RotateR(pr); 
//                         pr->bf = 1; pr->left->bf = -1;
//                     } else {
//                         RotateL(pr);
//                         pr->bf = -1; pr->right->bf = 1;
//                     }
//                     if (dd == -1) ppr->left = pr;
//                     else if (dd == 1) ppr->right = pr;
//                     break;
//                 }
//                 if (q->bf == d) {
//                     if (d == -1) RotateR(pr);
//                     else RotateL(pr);
//                 } else {
//                     if (d == -1) RotateLR(pr);
//                     else RotateRL(pr);
//                 }
//                 if (dd == -1) ppr->left = pr;
//                 else if (dd == 1) ppr->right = pr;
//             }
//             q = pr;
//         }
//         if (st.empty()) ptr = pr; 
//     }
//     delete p; return true;
// };

template<class T>
bool  AVLTree<T>::Remove(AVLNode<T>*&t, T val)
{
	if (t == nullptr) return false;

	AVLNode<T> *tmp = t;
	AVLNode<T> *pre_tmp = nullptr;
	AVLNode<T> *ppre_tmp = nullptr;
	AVLNode<T> *it_tmp = nullptr;
	stack<AVLNode<T>*> st;
	int sign, lable; // 符号标记
	int flag = 0; // 子树标记，下文具体解释

	while (tmp != nullptr) {
		if (tmp->data == val) break; // 找到跳出循环

		pre_tmp = tmp;
		st.push(pre_tmp);

		if (tmp->data > val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	if (tmp == nullptr) return false; // 未找到，返回
	else if (tmp->left!= nullptr && tmp->right != nullptr) {
		pre_tmp = tmp; // 将有两个孩子的节点转化为只有一个孩子的节点，方法是寻找它中序遍历的直接前驱或后继
		st.push(pre_tmp);

		it_tmp = tmp->left;
		while (it_tmp->right!= nullptr) {
			pre_tmp = it_tmp;
			st.push(pre_tmp);
			it_tmp = it_tmp->right;
		}
		tmp->data = it_tmp->data; // 覆盖要删除的节点
		tmp = it_tmp; // tmp指向要删除的节点，函数结束前会delete tmp
	}

	if (tmp->left!= nullptr) {  // 这样的判断方式会导致删除一个节点下两个没有孩子节点的节点时，由于左孩子均为空，直接跳入else
		it_tmp = tmp->left;
	} else {
		it_tmp = tmp->right;
	}

	if (pre_tmp == nullptr)
		t = it_tmp;
	else {
		if (pre_tmp->left== tmp) { // 上面直接跳入else，但我们在此处加上flag，用来识别它到底是pre_tmp的左孩子还是右孩子。
			flag = 0;
			pre_tmp->left= it_tmp;
		} else {
			flag = 1;
			pre_tmp->right = it_tmp;
		}

		while (!st.empty()) {
			pre_tmp = st.top();
			st.pop();

			if (pre_tmp->left == it_tmp && flag == 0) // 此处flag=0，防止pre_tmp的左孩子为空，右孩子同样为空，直接进入else
				pre_tmp->bf++;
			else
				pre_tmp->bf--;

			if (!st.empty())
			{
				ppre_tmp = st.top();
				if (ppre_tmp->left == pre_tmp)
				{
					sign = -1; // sign用来识别是祖父节点的左孩子还是右孩子，下文链接会用上
					flag = 0;
				} else {
					sign = 1;
					flag = 1;
				}
			}
		    else sign = 0; // 栈空，它的祖先节点不存在，pre_tmp即为根节点，但是这里也要写上，否则sign的值会遗留下来

			if (pre_tmp->bf == -1 || pre_tmp->bf == 1)
				break; // 已经平衡，直接跳出
			if (pre_tmp->bf != 0) { //m_bf为+2/-2
				if (pre_tmp->bf < 0) {
					lable = -1; // lable表示父节点符号，下面会用来区分同号异号
					it_tmp = pre_tmp->left;
				} else {
					lable = 1;
					it_tmp = pre_tmp->right;
				}

				if (it_tmp->bf == 0) { // pre_tmp的较高子树的头节点m_bf为0
					if (lable == -1) {
						RotateR(pre_tmp);
						pre_tmp->bf = 1;
						pre_tmp->right->bf = -1;
					} else {
						RotateL(pre_tmp);
						pre_tmp->bf = -1;
						pre_tmp->left->bf = 1;
					}
					break; // 直接跳出，并没有链接，需要下文写上链接
				}

				if (it_tmp->bf == lable) { // 同号 
					lable == 1 ? RotateL(pre_tmp) : RotateLR(pre_tmp);
				} else { // 异号
					lable == -1 ? RotateLR(pre_tmp): RotateRL(pre_tmp);
				}
				if (sign == -1)
					ppre_tmp->left = pre_tmp;
				else if (sign == 1) // else if正确方式
					ppre_tmp->right = pre_tmp;
			}
			it_tmp = pre_tmp; // 回溯
		}
		if (st.empty()) // 栈为空，根节点
			t = pre_tmp;
		else { // 这一段else参考书上没有，书是错的，如果不写此处，break直接跳出while循环，会导致链接不上，数据丢失
			ppre_tmp = st.top();
			if (ppre_tmp->data > pre_tmp->data)
				ppre_tmp->left = pre_tmp;
			else
				ppre_tmp->right = pre_tmp;
		}
	}
	delete tmp;
	tmp = nullptr;
	return true;
}

template <typename T>
void AVLTree<T>::Print(AVLNode<T> *ptr) {
    if (!ptr) return;
    Print(ptr->right);
    int x = getLevel(ptr) - 1;
    while (x--) cout << '\t';
    cout << ptr->data << endl;
    Print(ptr->left);
};

template <typename T>
void AVLTree<T>::RotateL(AVLNode<T> *&ptr) {
    AVLNode<T> *subL = ptr;
    ptr = subL->right;
    subL->right = ptr->left;
    ptr->left = subL;
    ptr->bf = subL->bf = 0;
};

template <typename T>
void AVLTree<T>::RotateR(AVLNode<T> *&ptr) {
    AVLNode<T> *subR = ptr;
    ptr = subR->left;
    subR->left = ptr->right;
    ptr->right = subR;
    ptr->bf = subR->bf = 0;
};

template <typename T>
void AVLTree<T>::RotateLR(AVLNode<T> *&ptr) {
    AVLNode<T> *subR = ptr, *subL = subR->left;
    ptr = subL->right;
    subL->right = ptr->left;
    ptr->left = subL;
    if (ptr->bf <= 0) subL->bf = 0;
    else subL->bf = -1;
    subR->left = ptr->right;
    ptr->right = subR;
    if (ptr->bf == -1) subR->bf = 1;
    else subR->bf = 0;
    ptr->bf = 0;
};

template <typename T>
void AVLTree<T>::RotateRL(AVLNode<T> *&ptr) {
    AVLNode<T> *subL = ptr, *subR = subL->right;
    ptr = subR->left;
    subR->left = ptr->right;
    ptr->right = subR;
    if (ptr->bf >= 0) subR->bf = 0;
    else subR->bf = 1;
    subL->right = ptr->left;
    ptr->left = subL;
    if (ptr->bf == 1) subL->bf = -1;
    else subL->bf = 0;
    ptr->bf = 0;
};

template <typename T>
int AVLTree<T>::getLevel(AVLNode<T> *current) {
    if (root == current) return 1;
    else return 1 + getLevel(Parent(root, current));
};

template <typename T>
AVLNode<T> *AVLTree<T>::Parent(AVLNode<T> *ptr, AVLNode<T> *current) {
    if (!ptr) return NULL;
    if (ptr->left == current || ptr->right == current) return ptr;
    AVLNode<T> *p = Parent(ptr->left, current);
    if (p) return p;
    else return Parent(ptr->right, current);
};
