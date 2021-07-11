#include <stdio.h>

int main() {
    int t=0;
    int i=2;
    while(i <= 100)
    {
        t += i;
        i += 2;
    }
    printf("2+4+5+...+100=%d\n", t);
    return 0;
}
