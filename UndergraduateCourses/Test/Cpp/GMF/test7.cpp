#include <stdio.h>
int main() 
{
    int i,a,n=0;
    while(n<9)
    {
        do
        {
            scanf("%d", &a);
        } while (a<1&&a>50);
        for (i=0; i<a; i++)
            printf("*");
        printf("\n");
        n++;
    }
    return 0;
}
