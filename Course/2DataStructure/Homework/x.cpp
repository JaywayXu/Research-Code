#include<iostream>
#include<cmath>
using namespace std;
typedef char ElemType;
typedef struct
{
	ElemType *base;//指向栈底
	ElemType *top;//指向栈顶
	int StackSize = 20;
}sqStack;//声明一个结构对象
void InitStack(sqStack *s)//初始化栈
{
	s->base = (ElemType *)malloc(20 * sizeof(ElemType));
	s->top = s->base;
}
void Push(sqStack *s, ElemType e)
{
	*(s->top) = e;
	s->top++;//栈顶指针加一
}
void Pop(sqStack *s, ElemType *e)
{
	*e = *(s->top);
	s->top--;
}
int main()
{
	ElemType c;
	sqStack s;
	int n = 0, sum = 0;
	InitStack(&s);
	cout << "" << 
	endl;
	cin >> c;
	while (c != '#') {
		Push(&s, c);
		n++;
		cin >> c;
	}
	for (int i = 0; i < n; i++) {
		Pop(&s, &c);
		cout << c << endl;
	}
	cout << sum;
	return 0;
}