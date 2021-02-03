#include <iostream>
#include <string>
#include <string.h>

using namespace std;

bool fun(string s)
{
    int size = s.size();
    int num = size/2;
    for (int i = 0; i<num; i++)
    {
        if (s[i] != s[size-1-i])
        {
            return false;
        }
    }
    return true;
}

string fanzhuan(string str)
{
    string temp(str);
    int size = str.size();
    for (int i = 0; i<size; i++)
    {
        temp[i] = str[size-i-1];
    }
    return temp;
}

void add(const char *a,const char *b,char *back)
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
    string str;
    while (cin>>str)
    {
        string out(str);
        int i = 0;
        while (!fun(str))
        {
            char ad[32];
            add(str.c_str(),fanzhuan(str).c_str(),ad);
            str = ad;
            out = out + "--->";
            out = out + ad;
            i++;
        }
        cout << i << endl;
        cout << out << endl;
    }
    return 0;
}