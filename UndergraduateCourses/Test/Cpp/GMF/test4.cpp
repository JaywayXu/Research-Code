#include <stdio.h>
#include <math.h>

int main()
{
    float a,b,c,s,area;
    printf("Please input 3 numbers:\n");
    scanf("%f%f%f",&a,&b,&c);
    if (a+b>c&&b+c>a&&a+c>b)
    {
        s = (a+b+c)/2;
        area = sqrt(s*(s-a)*(s-b)*(s-c));
        printf("area is %.2f\n", area);
    }
    else {
        printf("error.\n");
    }
}