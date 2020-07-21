#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d", &a, &b);
    if (a+b>20) {
        c = a*a-b*b;
    } else {
        c = (a-b)*(a-b);
    }
    printf("%d", c);
    return 0;
}
