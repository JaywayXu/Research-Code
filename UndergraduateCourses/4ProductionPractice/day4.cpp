#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <iomanip>
#include <map>
using namespace std;
//求去掉空格之后的子串
int trimSpace(const char *str, char *outbuf);
int trimSpace(const char *str, char *outbuf)
{
	if (NULL == str || NULL == outbuf)
	{
		return -1;
	}
	const char *p = str;
	int i = 0;
	int j = strlen(str) - 1;
	while (isspace(p[i]) && p[i] != '\0')
	{
		i++;
	}
	while (isspace(p[j]) && p[j] != '\0')
	{
		j--;
	}
	int count = 0;
	count = j - i + 1;
	strncpy(outbuf, str + i, count);
	outbuf[count] = '\0';
	return 0;
}
/**
*功能：统计个数；计算行数
*参数：char *str,char a
*说明：str是字符串，a是要计算次数的字符
**/
int count(char *str, char a)
{
	int count = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == a)
			count++;
	}
	return count;
}
/**
*功能：得到分割后的字符串
*参数：char *str,int len
*说明：str是字符串，len为分割后的字符串长度
**/
char *getnext(char *str, int len)
{
	char *re = (char *)malloc(20);
	strncpy(re, str + 1, len);
	re[len] = '\0';
	return re;
}
/**
*功能：将字符串存放到二维数组；输出数组和行数
*参数：char *str,char**me_array
*说明：str是字符串，me_array是二维数组
**/
int my_array(char *str, char **me_array)
{
	char *tmp = str;
	if (NULL == str)
		return -1;

	int row = count(str, ',');

	tmp = strchr(str, '{') + 1;
	for (int i = 0; i < row; i++)
	{
		char *p = strchr(tmp, '"'); ////找到第一次出现"的位置
		char *tmp3 = p;
		char *q = strchr(tmp3 + 1, '"');
		//int a = q - p;
		int len = (q - p) - 1;
		char *tmp2 = p;
		me_array[i] = getnext(tmp2, len);
		/*me_array[strlen(me_array) + 1] = '\0';*/
		tmp = p;
		tmp += q - p + 1;
	}
	//cout << *me_array[0] << me_array[1];
	for (int i = 0; i < row; i++)
	{
		cout << me_array[i] << endl;
	}
	cout << "个数为" << row << endl;
	cout << "行数为" << row << endl;
	return 0;
}
/*
测试用例
1."{"abcedf","dddddd","eeeee","yyyyy",}"
2."{"abcedf","ddd ddd","eeeee","yyyyy",}"
3."{"abcedf", "ddd ddd", "eeeee", "yyyyy",}"
*/
void test()
{
	char *str = "{\"ab cedf\",   \"dddddd\",  \"eeeee\" ,  \"yyyyy\",}";
	int row = count(str, ',');
	if (NULL == str)
		return;
	char **me_array = (char **)malloc(sizeof(char *) * row);
	for (int i = 0; i < row; i++)
	{
		me_array[i] = (char *)malloc(sizeof(char) * 1024);
	}
	my_array(str, me_array);
}
int main()
{
	test();
	system("pause");
	return 0;
}
