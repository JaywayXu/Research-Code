#include <iostream>
#include <stdlib.h>
using namespace std;

/* 功能：字符串反转
 * 参数：char* 字符串指针, int 字符串长度
 * 返回值：void
 * 作者：李延炽20171002448
 */
void reverseStr(char *s, int len) {
    if(!s) return;
    int low=0, high=len-1;
    while (low<high) {
        char c = s[low];
        s[low] = s[high];
        s[high] = c;
        low++; high--;
    }
}

/* 功能：字符串输出
 * 参数：char* 字符串指针
 * 返回值：void
 * 作者：李延炽20171002448
 */
void printStr(char *s) {
    cout << s;
}

/* 功能：字符反转测试
 * 参数：无
 * 返回值：void
 * 作者：李延炽20171002448
 */
void test() {
    char s[10];
    for (int test_num=0; test_num<20; test_num++) {
        printf("--第 %d 次测试--\n", test_num);
        
        for (int i=0; i<10; i++) { //随机生成字符串
            int a = rand()%80 + 33; //随机生成ascii里33-113的字符当第一个
            s[i] = char(a);
        }
        int len = sizeof(s)/sizeof(char);
        
        cout << "old str： ";
        printStr(s);
        reverseStr(s, len);
        cout << "reversed str： ";
        printStr(s);
        cout <<endl;
    }
}

int main () {
    test();
    return 0;
}
