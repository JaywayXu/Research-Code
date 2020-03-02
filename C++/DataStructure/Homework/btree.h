#ifndef BTREE_H
#define BTREE_H

const int DEGREE = 4; //B数的度，这里是2-3-4树
const int DATA_MAX = DEGREE - 1;
const int DATA_MIN = 1;
const int CHILD_MAX = DATA_MAX + 1;
const int CHILD_MIN = DATA_MIN + 1;

#include <iostream>

using namespace std;

template <typename T>
class BNode {
public:
    BNode() :isLeaf(true), num(0) {}

    bool isLeaf; //判断是否是叶子节点
    int num; //数据数量
    T bData[DATA_MAX]; //数据数组
    BNode<T> *pChild[DEGREE]; //孩子指针数组
};

template <typename T>
class BTree {
public:
    BTree() {root = NULL;}
    ~BTree() {clear();}
    
    bool insert(T &data);
    bool remove(T &data);
    void display() {displayInConcavo(root, DATA_MAX*10);}
    bool contain(T &data) {return search(root, data);}
    void clear() {recursive_clear(root); root = NULL;}

private:
    bool search(BNode<T> *pNode, T &data);

    void insertNonFull(BNode<T> *pNode, T &data); //非满结点插入
    void recursive_remove(BNode<T> *pNode, T &data);

    void splitChild(BNode<T> *pParent, int nChildIndex, BNode<T> *pChild); //分裂
    void mergeChild(BNode<T> *pParent, int index); //合并
    void deleteNode(BNode<T> *&pNode); 

    void displayInConcavo(BNode<T> *pNode, int count);
    void recursive_clear(BNode<T> *pNode);

    T getPredecessor(BNode<T> *pNode); //找前驱
    T getSuccessor(BNode<T> *pNode); //找后继

    BNode<T> *root;
};

template <typename T>
bool BTree<T>::insert(T &data) {
    if (contain(data)) { //检查该关键字是否已经存在
        return false;
    } else {
        if (root == NULL) { //检查是否为空树
            root = new BNode<T>();
        }
        if (root->num == DATA_MAX) { //检查根节点是否已满
            BNode<T> *pNode = new BNode<T>();  //创建新的根节点
            pNode->isLeaf = false;
            pNode->pChild[0] = root;
            splitChild(pNode, 0, root);
            root = pNode;  //更新根节点指针
        }
        insertNonFull(root, data);
        return true;
    }
}

template <typename T>
bool BTree<T>::remove(T &data) {
    if (!search(root, data)) { //不存在
        return false;
    }
    if (root->num == 1) { //特殊情况处理
        if (root->isLeaf) {
            clear();
            return true;
        } else {
            BNode<T> *pChild1 = root->pChild[0];
            BNode<T> *pChild2 = root->pChild[1];
            if (pChild1->num==DATA_MIN && pChild2->num==DATA_MIN) {
                mergeChild(root, 0);
                deleteNode(root);
                root = pChild1;
            }
        }
    }
    recursive_remove(root, data);
    return true;
}

template <typename T>
bool BTree<T>::search(BNode<T> *pNode, T &data) {
    if (pNode==NULL) { //检测节点指针是否为空，或该节点是否为叶子节点
        return false;
    } else {
        int i;
        for (i=0; i<pNode->num && data>*(pNode->bData+i); ++i); //找到使data<=pNode->bData[i]成立的最小下标i
        if (i<pNode->num && data==pNode->bData[i]) {
            return true;
        } else {
            if (pNode->isLeaf) { //检查该节点是否为叶子节点
                return false;
            } else {
                return search(pNode->pChild[i], data);
            }
        }
    }
}

template <typename T>
void BTree<T>::insertNonFull(BNode<T> *pNode, T &data) {
    int i = pNode->num; //获取节点内关键字个数
    if (pNode->isLeaf) { //pNode是叶子节点
        while (i>0 && data<pNode->bData[i-1]) { //从后往前，查找关键字的插入位置
            pNode->bData[i] = pNode->bData[i-1]; //向后移位
            --i;
        }
        pNode->bData[i] = data; //插入关键字的值
        ++pNode->num; //更新节点关键字的个数
    }
    else { //pNode是内节点
        while(i>0 && data<pNode->bData[i-1]) //从后往前，查找关键字的插入的子树
            --i;
        BNode<T> *pChild = pNode->pChild[i]; //目标子树结点指针 
        if (pChild->num == DATA_MAX) { //子树节点已满
            splitChild(pNode, i, pChild);//分裂子树节点
            if(data>pNode->bData[i])   //确定目标子树
                pChild = pNode->pChild[i+1];
        }
        insertNonFull(pChild, data);  //插入关键字到目标子树节点
    }
}

template <typename T>
void BTree<T>::recursive_remove(BNode<T> *pNode, T &data) {
    int i=0;
    while(i<pNode->num && data>pNode->bData[i])
        ++i;
    if (i<pNode->num && data==pNode->bData[i]) { //关键字key在节点pNode中
        if (pNode->isLeaf) { //pNode是个叶节点
            //从pNode中删除k
            --pNode->num;
            for (; i<pNode->num; ++i) {
                pNode->bData[i] = pNode->bData[i+1];
            }
            return;
        } else { //pNode是个内节点
            BNode<T> *pChildPrev = pNode->pChild[i]; //节点pNode中前于key的子节点
            BNode<T> *pChildNext = pNode->pChild[i+1]; //节点pNode中后于key的子节点
            if (pChildPrev->num >= CHILD_MIN) { //节点pChildPrev中至少包含CHILD_MIN个关键字
                T prevKey = getPredecessor(pChildPrev); //获取key的前驱关键字
                recursive_remove(pChildPrev, prevKey);
                pNode->bData[i] = prevKey; //替换成key的前驱关键字
                return;
            } else if (pChildNext->num>=CHILD_MIN) { //节点pChildNext中至少包含CHILD_MIN个关键字
                T nextKey = getSuccessor(pChildNext); //获取key的后继关键字
                recursive_remove(pChildNext, nextKey);
                pNode->bData[i] = nextKey; //替换成key的后继关键字
                return;
            } else { //节点pChildPrev和pChildNext中都只包含CHILD_MIN-1个关键字
                mergeChild(pNode, i);
                recursive_remove(pChildPrev, data);
            }
        }
    } else { //关键字key不在节点pNode中
        BNode<T> *pChildNode = pNode->pChild[i]; //包含key的子树根节点
        if (pChildNode->num == DATA_MIN) { //只有t-1个关键字
            BNode<T> *pLeft = i>0 ? pNode->pChild[i-1] : NULL; //左兄弟节点
            BNode<T> *pRight = i<pNode->num ? pNode->pChild[i+1] : NULL; //右兄弟节点
            int j;
            if (pLeft && pLeft->num>=CHILD_MIN) { //左兄弟节点至少有CHILD_MIN个关键字
                //父节点中i-1的关键字下移至pChildNode中
                for (j=pChildNode->num; j>0; --j) {
                    pChildNode->bData[j] = pChildNode->bData[j-1];
                }
                pChildNode->bData[0] = pNode->bData[i-1];
                
                if (!pLeft->isLeaf) {
                    for (j=pChildNode->num+1; j>0; --j) { //pLeft节点中合适的子女指针移植到pChildNode中
                        pChildNode->pChild[j] = pChildNode->pChild[j-1];
                    }
                    pChildNode->pChild[0] = pLeft->pChild[pLeft->num];
                }
                ++pChildNode->num;
                pNode->bData[i-1]/*这里原本是[i]，现在改正了过来*/ = pLeft->bData[pLeft->num-1]; //pLeft节点中的最大关键字上升到pNode中
                --pLeft->num;
            } else if (pRight && pRight->num>=CHILD_MIN) { //右兄弟节点至少有CHILD_MIN个关键字
                //父节点中i的关键字下移至pChildNode中
                pChildNode->bData[pChildNode->num] = pNode->bData[i];
                ++pChildNode->num;
                pNode->bData[i] = pRight->bData[0]; //pRight节点中的最小关键字上升到pNode中
                --pRight->num;
                for (j=0; j<pRight->num; ++j) {
                    pRight->bData[j] = pRight->bData[j+1];
                }
                if (!pRight->isLeaf) {
                    pChildNode->pChild[pChildNode->num] = pRight->pChild[0]; //pRight节点中合适的子女指针移植到pChildNode中
                    for (j=0; j<=pRight->num; ++j) {
                        pRight->pChild[j] = pRight->pChild[j+1];
                    }
                }
            }
            //左右兄弟节点都只包含CHILD_MIN-1个节点
            else if (pLeft) { //与左兄弟合并
                mergeChild(pNode, i-1);
                pChildNode = pLeft;
            }
            else if (pRight) { //与右兄弟合并
                mergeChild(pNode, i);
            }
        }
        recursive_remove(pChildNode, data);
    }
}

template <typename T>
void BTree<T>::splitChild(BNode<T> *pParent, int nChildIndex, BNode<T> *pChild) {
    //将pChild分裂成pLeftNode和pChild两个节点
    BNode<T> *pRightNode = new BNode<T>(); //分裂后的右节点
    pRightNode->isLeaf = pChild->isLeaf;
    pRightNode->num = DATA_MIN;
    int i;
    for (i=0; i<DATA_MIN; ++i) { //拷贝关键字的值
        pRightNode->bData[i] = pChild->bData[i+CHILD_MIN];
    }
    if (!pChild->isLeaf) { //如果不是叶子节点，拷贝孩子节点指针
        for (i=0; i<CHILD_MIN; ++i) {
            pRightNode->pChild[i] = pChild->pChild[i+CHILD_MIN];
        }
    }
    
    pChild->num = DATA_MIN; //更新左子树的关键字个数

    for (i=pParent->num; i>nChildIndex; --i) { //将父节点中的nChildIndex后的所有关键字的值和子树指针向后移一位
        pParent->pChild[i+1] = pParent->pChild[i];
        pParent->bData[i] = pParent->bData[i-1];
    }
    ++pParent->num; //更新父节点的关键字个数
    pParent->pChild[nChildIndex+1] = pRightNode; //存储右子树指针
    pParent->bData[nChildIndex] = pChild->bData[DATA_MIN]; //把节点的中间值提到父节点
}

template <typename T>
void BTree<T>::mergeChild(BNode<T> *pParent, int index) {
    BNode<T> *pChild1 = pParent->pChild[index];
    BNode<T> *pChild2 = pParent->pChild[index+1];
    //将pChild2数据合并到pChild1
    pChild1->num = DATA_MAX;
    pChild1->bData[DATA_MIN] = pParent->bData[index];//将父节点index的值下移
    int i;
    for (i=0; i<DATA_MIN; ++i) {
        pChild1->bData[i+DATA_MIN+1] = pChild2->bData[i];
    }
    if (!pChild1->isLeaf) {
        for (i=0; i<CHILD_MIN; ++i) {
            pChild1->pChild[i+CHILD_MIN] = pChild2->pChild[i];
        }
    }

    //父节点删除index的key，index后的往前移一位
    --pParent->num;
    for(i=index; i<pParent->num; ++i) {
        pParent->bData[i] = pParent->bData[i+1];
        pParent->pChild[i+1] = pParent->pChild[i+2];
    }
    deleteNode(pChild2);  //删除pChild2
}

template <typename T>
void BTree<T>::deleteNode(BNode<T> *&pNode) {
    if (pNode!=NULL) {
        delete pNode;
        pNode = NULL;
    }
}

template <typename T>
void BTree<T>::displayInConcavo(BNode<T> *pNode, int count) {
    if (pNode!=NULL) {
        int i, j;
        for (i=0; i<pNode->num; ++i) {
            if (!pNode->isLeaf) {
                displayInConcavo(pNode->pChild[i], count-6);
            }
            for (j=count; j>=0; --j) {
                cout<<"-";
            }
            cout<<pNode->bData[i]<<"-"<<endl;
        }
        if (!pNode->isLeaf) {
            displayInConcavo(pNode->pChild[i], count-6);
        }
    }
}

template <typename T>
void BTree<T>::recursive_clear(BNode<T> *pNode) {
    if (pNode!=NULL) {
        if (!pNode->isLeaf) {
            for(int i=0; i<=pNode->num; ++i)
                recursive_clear(pNode->pChild[i]);
        }
        deleteNode(pNode);
    }
}

template <typename T>
T BTree<T>::getPredecessor(BNode<T> *pNode) {
    while (!pNode->isLeaf) {
        pNode = pNode->pChild[pNode->num];
    }
    return pNode->bData[pNode->num-1];
}

template <typename T>
T BTree<T>::getSuccessor(BNode<T> *pNode) {
    while (!pNode->isLeaf) {
        pNode = pNode->pChild[0];
    }
    return pNode->bData[0];
}

#endif // BTREE_H
