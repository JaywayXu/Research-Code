#include "stdio.h"
#include "stdlib.h"

#define InitSize 100

typedef int ElemType;
typedef struct { // 顺序表
    ElemType *data;
    int MaxSize, length;
} SqList;

/* --- 基本操作 --- */

// 初始化顺序表
void InitList(SqList *L) {
    L->length = 0;
    L->data = (ElemType *) malloc (InitSize * sizeof(ElemType));
    L->MaxSize = InitSize;
}

// 析构顺序表
void DestoryList(SqList *L) {
    free(L->data);
    L = NULL;
}

// 顺序表插入
int ListInsert(SqList *L, int i, ElemType e) {
    if(i<1 || i>L->length+1) {
        return 0;
    }
    if (L->length >= L->MaxSize) {
        return 0;
    }
    for (int j=L->length; j>=i; j--) {
        L->data[j] = L->data[j-1];
    }
    L->data[i-1] = e;
    L->length++;
    return 1;
}

// 打印顺序表
void PrintList(SqList *L) {
    if (0 == L->length) {
        printf("the sqlist is empty!\n");
        return;
    }
    for (int i=0; i<L->length; i++) {
        if (L->length-1 == i) {
            printf("%d\n", L->data[i]);
            break;
        }
        printf("%d - ", L->data[i]);
    }
}

/* --- 测试操作 --- */

// 有序表删除s-t之间的元素
int Del_s_t(SqList *L, int s, int t) {
    if (0 == L->length || s>=t) {
        return 0;
    }
    int i, j;
    for(i=0; s > L->data[i]; i++) {
        if (i == L->length-1) return 0;
    }
    for(j=i; t >= L->data[j]; j++) {
        if(j == L->length-1) break;
    }
    while (j<L->length) {
        L->data[i] = L->data[j];
        i++; j++;
    }
    L->length = i;
    return 1;
}

// 有序表删除重复元素
int Del_Same_Elem(SqList *L) {
    if (0 == L->length) {
        return 0;
    }
    int k = 0;
    for(int i=1; i<L->length; i++) {
        if(L->data[k] != L->data[i]) {
            k++;
            L->data[k] = L->data[i];
        }
    }
    L->length = k+1;
    return 1;
}

// 合并两个有序表
SqList Merge_2(SqList *L1, SqList *L2) {
    SqList new_L;
    InitList(&new_L);
    if (0 == L1->length || 0 == L2->length) {
        return new_L;
    }
    int i=0, j=0, k=0;
    while(i<L1->length && j<L2->length) {
        if(L1->data[i] < L2->data[j]) {
            new_L.data[k++] = L1->data[i++];
        } else {
            new_L.data[k++] = L2->data[j++];
        }
    }
    if (L1->length == i) {
        for (; j<L2->length; j++) {
            new_L.data[k++] = L2->data[j];
        }
    } else if(L2->length == j) {
        for (; i<L1->length; i++) {
            new_L.data[k++] = L1->data[i];
        }
    }
    new_L.length = k;
    return new_L;
}

// 顺序表中两个子表互换
void Exchange_SubList(SqList *L, int m) {
    ElemType *copy_data = (ElemType *) malloc (L->length * sizeof(ElemType));
    for(int i=0; i<L->length; i++) {
        copy_data[i] = L->data[i];
    }
    int k=0;
    for(int j=m; j<L->length; j++) {
        L->data[k++] = copy_data[j];
    }
    for(int j=0; j<m; j++) {
        L->data[k++] = copy_data[j];
    }
    free(copy_data);
}

// 查找x，找到和后一个交换，找不到插入
int Find_x_EorI(SqList *L, int x) {
    if (0 == L->length) {
        return 0;
    }
    int low = 0, high = L->length-1;
    int half = (high + low)/2;
    while(low <= high) {
        if(x < L->data[half]) {
            high = half-1;
            half = (high + low)/2;
        } else if(x > L->data[half]) {
            low = half+1;
            half = (high + low)/2;
        } else {
            printf("find it!\n");
            int t = L->data[half];
            L->data[half] = L->data[half+1];
            L->data[half+1] = t;
            return 1;
        }
    }
    printf("can't find it!\n");
    ListInsert(L, half+2, x);
    return 1;
}

// 循环左移p
int List_Left_p(SqList *L, int p) {
    if (L->length == 0 || p >= L->length || p <= 0) {
        return 0;
    }
    ElemType *copy_2 = (ElemType *) malloc(2*L->length * sizeof(ElemType));
    int j = 0;
    for(int i=0; i<2*L->length; i++) {
        if(i == L->length) j = 0;
        copy_2[i] = L->data[j++];
    }
    int k = L->length-p;
    for(int i=0; i<L->length; i++) {
        L->data[i] = copy_2[k++];
    }
    free(copy_2);
    return 1;
}

// 2个等长升序序列求中位数
int Find_Mid_Elem(SqList *L1, SqList *L2, ElemType *mid_e) {
    if(L1->length != L2->length || L1->length == 0) {
        return 0;
    }

    // 时间(O(n))差
    // int length2 = 2*L1->length;
    // int mid_index = (length2+1)/2;
    // int k, i=0, j=0;
    // for (int k=0; k<mid_index; k++) {
    //     if(L1->data[i] < L2->data[j]) {
    //         *mid_e = L1->data[i];
    //         i++;
    //     } else {
    //         *mid_e = L2->data[j];
    //         j++;
    //     }
    // }
    // return 1;

    // 时间O(logn)
    int mid1, mid2;
    int n = L1->length;
    int s1=0, s2=n-1, d1=0, d2=n-1;
    while(s1!=d1 || s2!=d2) {
        mid1 = (s1+d1)/2;
        mid2 = (s2+d2)/2;
        if(L1->data[mid1] < L2->data[mid2]) {
            if((s1+d1) % 2 == 0) {
                s1 = mid1;
                d2 = mid2;
            } else {
                s1 = mid1+1;
                d2 = mid2;
            }
        } else if (L2->data[mid2] < L1->data[mid1]) {
            if((s2+d2) % 2 == 0) {
                d1 = mid1;
                s2 = mid2;
            } else {
                d1 = mid1;
                s2 = mid2+1;
            }
        } else {
            *mid_e = L1->data[mid1];
            return 1;
        }
    }
    *mid_e = L1->data[s1] < L2->data[s2] ? L1->data[s1] : L2->data[s2];
    return 1;
}

int main() {
    SqList alist;
    InitList(&alist);
    int k = 0;
    for (int i=0; i<9; i++) {
        ListInsert(&alist, i+1, k);
        k += 2;
    }
    SqList alist2;
    InitList(&alist2);
    int k2 = 1;
    for (int i=0; i<9; i++) {
        ListInsert(&alist2, i+1, k2);
        k2 += 2;
    }
    // ListInsert(&alist, 1, 0);
    // ListInsert(&alist, 3, 1);
    // ListInsert(&alist, 3, 1);
    // ListInsert(&alist, 3, 1);
    // ListInsert(&alist, 10, 5);
    // ListInsert(&alist, 10, 5);

    PrintList(&alist);
    // printf("list length: %d\n", alist.length);
    PrintList(&alist2);
    // Printf("list2 length: %d\n", alist2.length);
    
    // Del_s_t(&alist, 5, 8);
    // Del_Same_Elem(&alist);
    // SqList new_L = Merge_2(&alist, &alist2);
    // Exchange_SubList(&alist, 2);
    // for (int i=0; i<12; i++) {
    //     Find_x_EorI(&alist, i);
    //     PrintList(&alist);
    // }
    // for (int i=0; i<11; i++) {
    //     List_Left_p(&alist, i);
    //     PrintList(&alist);
    // }
    ElemType e;
    Find_Mid_Elem(&alist, &alist2, &e);
    printf("mid elem: %d\n", e);

    PrintList(&alist);
    // printf("list length: %d\n", alist.length);
    PrintList(&alist2);
    // Printf("list2 length: %d\n", alist2.length);
    // PrintList(&new_L);
    // printf("new_L length: %d\n", new_L.length);

    DestoryList(&alist);
    // DestoryList(&alist2);
    // DestoryList(&new_L);
    return 0;
}