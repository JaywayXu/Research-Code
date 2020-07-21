#include <stdio.h>

int main()
{
    char str[40], a;
    int i = 0, big = 0, small = 0, other = 0;
    scanf("%s", &str);
    a = str[0];
    while (a != '#')
    {
        //大写英文字母
        if ((int)a >= (int)'A' && (int)a <= (int)'Z')
        {
            big++;
        }
        //小写英文字母
        else if ((int)a >= (int)'a' && (int)a <= (int)'z')
        {
            small++;
        }
        //其他符号
        else
        {
            other++;
        }
        a = str[++i];
    }
    printf("大写字母的个数：%d\n小写字母的个数：%d\n其他字母的个数：%d\n", big, small, other);
    return 0;
}