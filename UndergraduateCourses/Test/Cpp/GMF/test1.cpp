#include <stdio.h>

int main() {
    int m[9] = {2,23,34,45,56,11,8,55,0};
    int max = -1;
    for(int i=0; i<9; i++) {
        if (m[i] > max) {
            max = m[i];
        }
    }
    printf("%d", max);
    return 0;
}
