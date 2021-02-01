#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

/* 功能：字符串求字串次数
 * 参数：char* 字符串指针, char* 子字符串指针
 * 返回值：int 次数
 * 作者：李延炽20171002448
 */
int countSubStr(char *p, char *sub)
{
    char *q = p;
    int count = 0;
    while (*q != '\0')
    {
        q = strstr(q, sub);
        if (q != NULL)
        {
            count++;
            q += strlen(sub);
        }
        else
            break;
    }
    return count;
}

/* 功能：字符串求子串次数测试
 * 参数：无
 * 返回值：void
 * 作者：李延炽20171002448
 */
void test1()
{
    char p[] = "abcd1111222abcd333444abcd555666aa";
    char sub[] = "abcd";
    cout << "次数：" << countSubStr(p, sub) << endl;
}

/* 功能：字符串中根据key求value
 * 参数：char* 字符串数组指针, int 字符串数组长度, char* key字符串指针, char *value字符串指针
 * 返回值：bool 是否找到
 * 作者：李延炽20171002448
 */
bool getValueStr(char arr[][20], int arr_len, char *key, char *value)
{
    // 去除空格
    for(int num=0; num<arr_len; num++){
        int i=0;
        while(arr[num][i] != '\0') {
            if(arr[num][i] == ' ') {
                int j=i;
                while(arr[num][j] != '\0') {
                    arr[num][j] = arr[num][j+1];
                    j++;
                }
                continue;
            }
            i++;
        }
        //cout << arr[num] << endl;
    }
    
    // 判断value是否相等
    int num=0,i=0,j=0;
    bool flag = false;
    for(num=0; num<arr_len; num++){
        while(arr[num][i] != '=') {
            if(key[j] == arr[num][i]) {
                i++; j++;
            } else {
                i=0; j=0;
                break;
            }
        }
        if(j==strlen(key)) { //success
            flag = true;
            break;
        }
    }
    if(!flag) return false;

    // 返回value
    j=0; i++;
    while(arr[num][i] != '\0') {
        value[j]=arr[num][i];
        i++; j++;
    }
    value[j] = '\0';
    return true;
}

/* 功能：字符串中根据key求value测试
 * 参数：无
 * 返回值：void
 * 作者：李延炽20171002448
 */
void test2()
{
    char arr[][20] = {
        "key1 = value1",
        "key2 =   value2",
        "  key3= value3",
        "key4    = value4"
    };
    int arr_len = sizeof(arr) / sizeof(arr[0]);
    char key[] = "key3";
    char value[10];
    getValueStr(arr, arr_len, key, value);
    cout << "key: " << key << endl;
    cout << "value: " << value << endl;
}

int main()
{
    test1();
    test2();
    return 0;
}
