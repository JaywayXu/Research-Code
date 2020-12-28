#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct T
{
    int num;
    char neme[6];
    float score;
} a, b;

int f(struct T a) {
    printf("%d\n",&a.neme);
    strcpy(a.neme, "567");
}

int main() {
    // int a[2] = {1,2};
    // int *p = a;
    // int a;
    // a+=a+=a=9;
    // double x=3;
    // int c = (int)(x)%2;
    // int d = (int)x%2;
    // printf("%d %d", c, d);
    // char a[5] = "1234";
    // printf("%s\n", a);
    // strcpy(a, "54321");
    // printf("%s\n", a);
    // struct T c = {0, "123", 10};
    // printf("%d\n",&c.neme);
    // printf("%s\n", c.neme);
    // f(c);
    // printf("%d\n",&c.neme);
    // printf("%s\n", c.neme);
    int a; float b;
    scanf("%2d%f", &a, &b);
    printf("%2d %f", a, b);
    return 0;
}