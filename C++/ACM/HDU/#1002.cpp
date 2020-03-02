#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void add(char *a,char *b,char *back)
{
	int i,j,k,up,x,y,z,l;
	char *c;
	if(strlen(a)>strlen(b))  l=strlen(a)+2;//可能有进位
	else l=strlen(b)+2;
	c=(char *) malloc(l*sizeof(char));
	i=strlen(a)-1;j=strlen(b)-1;k=0;   up=0;
	while(i>=0||j>=0)
	{
		if(i<0) x='0';else x=a[i];
		if(j<0) y='0';else y=b[j];
		z=x-'0'+y-'0';//在相同的位置的数相加
		if(up) z+=1;//up表示进位
		if(z>9) {up=1;z%=10;} else up=0;
		c[k++]=z+'0';
		i--;j--;
	}
	if(up) c[k++]='1';
	i=0;c[k]='\0';
	for(k-=1;k>=0;k--)back[i++]=c[k];//保存结果在back[]数组中
	back[i]='\0';
}

int main()
{
	int line,i;
	std::cin >> line;
	// unsigned long long arry[21][2];
	char arry[21][2][10000];
	for (i = 0; i<line; i++)
	{
		std::cin >> arry[i][0];
		std::cin >> arry[i][1];
	}
	for (i = 0;i <line; i++)
	{
		char c[10000];
		add(arry[i][0],arry[i][1],c);
		if (i == line-1)
		{
			std::cout << "Case " << i+1 << ":" << std::endl;
			std::cout << arry[i][0] << " + " << arry[i][1] << " = " << c << std::endl;
		}
		else
		{
			std::cout << "Case " << i+1 << ":" << std::endl;
			std::cout << arry[i][0] << " + " << arry[i][1] << " = " << c << std::endl << std::endl;
		}
	}
	return 0;
}