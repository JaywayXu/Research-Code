#include <iostream>
using namespace std;

typedef int ElemType;

int Partition(ElemType A[], int low, int high) {
    ElemType pivot = A[low];
    while (low < high) {
        while (low < high && A[high] > pivot) high--;
        A[low] = A[high];
        while (low < high && A[low] < pivot) low++;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

void QuickSort(ElemType A[], int low, int high) {
    if (low < high) {
        int p = Partition(A, low, high);
        QuickSort(A, low, p-1);
        QuickSort(A, p+1, high);
    }
}

int main () {
    ElemType A[] = {5,6,7,8,3,4,2,1,9,10};
    int N = sizeof(A)/sizeof(ElemType);
    QuickSort(A, 0, N-1);
    for (int i=0; i<N; i++) cout << A[i] << " ";
    cout << endl;
    return 0;
}
