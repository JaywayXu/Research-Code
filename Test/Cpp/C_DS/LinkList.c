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
int ReverseLinkList (LinkList *L) {
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
    ReverseLinkList(&l);

    PrintList(l);
    printf("length: %d\n", GetLength(l));
    DestoryLinkList(&l);
    return 0;
}