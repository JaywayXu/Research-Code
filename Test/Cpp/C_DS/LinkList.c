#include "stdio.h"
#include "stdlib.h"

typedef int ElemType;
typedef struct LNode { // 单链表节点
    ElemType data;
    struct LNode *next;
} LNode;
typedef struct LNode *LinkList; 

/* --- 基本操作 --- */

// 插入后一个结点
int InsertNextNode(LNode *node, ElemType e) {
    if (node == NULL) {
        return 0;
    }
    LNode *temp_node = (LNode *) malloc(sizeof(LNode));
    if (temp_node == NULL) {
        return 0;
    }
    temp_node->data = e;
    temp_node->next = node->next;
    node->next = temp_node;
    return 1;
}

// 删除后一个节点
int DeleteNextNode(LNode *node, ElemType *e) {
    if (node == NULL)  return 0;
    if (node->next == NULL) return 0;
    LNode *temp_node = node->next;
    node->next = node->next->next;
    (*e) = temp_node->data;
    free(temp_node);
    return 1;
}

// 头插建立
LinkList HeadInsert_Init(LinkList *L, ElemType *Array, int n) {
    (*L) = (LinkList) malloc(sizeof(LNode));
    if ((*L) == NULL) {
        return NULL;
    }
    (*L)->next = NULL;
    for (int i=0; i<n; i++) {
        InsertNextNode((*L), Array[i]);
    }
}

// 尾插建立
LinkList RearInsert_Init(LinkList *L, ElemType *Array, int n) {
    (*L) = (LinkList) malloc(sizeof(LNode));
    if ((*L) == NULL) {
        return NULL;
    }
    (*L)->next = NULL;
    LNode *temp_node, *rear=(*L);
    for (int i=0; i<n; i++) {
        if (InsertNextNode(rear, Array[i])) {
            rear = rear->next;
        }
    }
}

// 获取长度
int GetLength(LinkList L) {
    if (L == NULL) return 0;
    int length = 0;
    LNode *temp_node = L;
    while (temp_node->next != NULL) {
        length++;
        temp_node = temp_node->next;
    }
    return length;
}

// 析构单链表
int DestoryLinkList(LinkList *L) {
    if ((*L) == NULL) {
        return 1;
    }
    ElemType e;
    while (DeleteNextNode((*L), &e)) {}
    free((*L));
    return 1;
}

// 打印单链表
void PrintList(LinkList L) {
    if (L == NULL) return;
    LNode *temp_node = L;
    while (temp_node->next != NULL) {
        temp_node = temp_node->next;
        printf("%d ", temp_node->data);
    }
    printf("\n");
}

/* --- 测试操作 --- */

// 单链表逆置
int ReverseLinkList(LinkList *L) {
    if ((*L) == NULL) return 0;
    LNode *new_head = (LNode *) malloc (sizeof(LNode));
    new_head->next = NULL;
    LNode *temp_node;
    while((*L)->next != NULL) {
        temp_node = (*L)->next;
        (*L)->next = (*L)->next->next;
        temp_node->next = new_head->next;
        new_head->next = temp_node;
    }
    temp_node = (*L);
    (*L) = new_head;
    free(temp_node);
    return 1;
}

// 删除所有值为x的结点
int LinkList_Del_X(LinkList L, ElemType x) {
    if (L == NULL) return 0;
    LNode *p = L;
    while(p && p->next) {
        if(p->next->data == x) {
            LNode *tmp = p->next;
            p->next = p->next->next;
            free(tmp);
        }
        p = p->next;
    }
    return 1;
}

// 删除最小值结点
int LinkList_Del_Min(LinkList L) {
    if (!L || !L->next) return 0;
    LNode *p, *pre_min, *min;
    p = L; pre_min = p; min = p->next;
    while(p && p->next != NULL) {
        if (p->next->data < min->data) {
            pre_min = p; min = p->next;
        }
        p = p->next;
    }
    pre_min->next = min->next;
    free(min);
    return 1;
}

// 分解为A、B两个子链表，分别为原来的奇数和偶数位置
int LinkList_Split(LinkList *A, LinkList *B) {
    if (!(*A) || !(*A)->next || !(*A)->next->next) return 0;
    (*B) = (LNode *)malloc(sizeof(LNode));
    LNode *pa = (*A)->next; // pa指向第一个元素
    LNode *b_rear = (*B);
    int flag = 0; // pa的下一个是奇数还是偶数
    while(pa->next != NULL) { 
        if(flag == 0){ // 下一个是偶数，转移
            // A删除
            LNode *tmp = pa->next;
            pa->next = tmp->next;
            tmp->next = NULL;
            // B尾插
            b_rear->next = tmp;
            b_rear = tmp;
        } else {
            pa = pa->next;
        }
        flag = (flag+1)%2;
    }
    return 1;
}

// 合并两个递增有序单链表为一个递减有序单链表
int LinkList_Merge_Reverse(LinkList A, LinkList B) {
    if (!A || !B) return 0;
    LNode *pa=A->next, *pb=B->next, *p;
    A->next = NULL; // 使用A做新链表的头节点
    B->next = NULL; // 置B链表为空
    while (pa && pb) {
        if (pa->data < pb->data) {
            p = pa;
            pa = pa->next;
        } else {
            p = pb;
            pb = pb->next;
        }
        p->next = A->next;
        A->next = p;
    }
    if (!pa) { // A空
        while (pb) {
            p = pb;
            pb = pb->next;
            p->next = A->next;
            A->next = p;
        }
    } else if (!pb) {
        while (pa) {
            p = pa;
            pa = pa->next;
            p->next = A->next;
            A->next = p;
        }
    }
    return 1;
}

int main() {
    int array_num = 10;
    ElemType array[array_num];
    for (int i=0; i<array_num; i++) {
        array[i] = i;
    }
    LinkList l;
    // HeadInsert_Init(&l, array, array_num);
    RearInsert_Init(&l, array, array_num);
    PrintList(l);
    printf("length: %d\n", GetLength(l));

    // 测试

    // ReverseLinkList(&l);

    // LinkList_Del_X(l, 0);
    // LinkList_Del_X(l, 1);
    // LinkList_Del_X(l, 3);
    // LinkList_Del_X(l, 9);

    // LinkList_Del_Min(l);

    LinkList b;
    LinkList_Split(&l, &b);
    PrintList(l);
    printf("length: %d\n", GetLength(l));
    PrintList(b);
    printf("B length: %d\n", GetLength(b));

    LinkList_Merge_Reverse(l,b);
    PrintList(l);
    printf("length: %d\n", GetLength(l));

    DestoryLinkList(&l);
    DestoryLinkList(&b);    
    return 0;
}