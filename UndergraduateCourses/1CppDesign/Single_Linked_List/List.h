typedef int Datatype;

#include<iostream>

class Point
{
public:
	Datatype num;
	Point *next;
};

class List
{
public:
	List();
	~List();
	void add(int);
	void add(int,int);
	void del(int);
	int len();
	void sort();
	void print();
private:
	Point *first = new Point();
};

List::List()
{
	std::cout<<"创建了一个单链表\n";
}

List::~List()
{
	Point *p,*q;
	p = first->next;
	while(p != NULL)
	{
		q = p;
		p = p->next;
		std::cout<<"析构了元素"<<q->num<<"\n";
		delete q;
	}
	std::cout<<"析构了一个单链表\n";
}

void List::add(Datatype number)
{
	Point *temp = first;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new Point();
	temp->next->num = number;
	std::cout<<"加入了元素"<<temp->next->num<<"\n";
}

void List::add(Datatype number,int addr)
{
	Point *temp = first;
	Point *add;
	for(int i=1;;i++)
	{
		if(temp->next == NULL)
		{
			std::cout<<"插入元素的位置超出了表的长度！"<<"\n";
			break;
		}
		if(i==addr)
		{
			add = temp->next;
			temp->next = new Point();
			temp->next->num = number;
			temp->next->next = add;
			std::cout<<"在第"<<addr<<"个位置插入了"<<temp->next->num<<"\n";
			break;
		}
		temp = temp->next;
	}
}

void List::del(int addr)
{
	Point *temp = first;
	Point *del_te;
	for(int i=1;;i++)
	{
		if(temp->next == NULL)
		{
			std::cout<<"删除元素的位置超出了表的长度！！"<<"\n";
			break;
		}
		if(i==addr)
		{
			del_te = temp->next;
			temp->next=temp->next->next;
			delete del_te;
			std::cout<<"删除第"<<addr<<"位的元素成功！"<<"\n";
			break;
		}
		temp = temp->next;
	}
}

int List::len()
{
	int i = 0;
	Point *temp = first;
	while(temp->next != 0)
	{
		temp = temp->next;
		i++;
	}
	return i;
}

void List::sort()
{
	Point *temp = first;
	Point *q,*p;
	for(int i=0;i<len();i++)
	{
		for(int j=0;j<len()-i-1;j++)
		{
			if(temp->next->num > temp->next->next->num)
			{
				q = temp->next;
				p = temp->next->next;
				temp->next = p;
				q->next = p->next;
				p->next = q;
			}
			temp = temp->next;
		}
		temp = first;
	}
	std::cout<<"排序成功！\n";
}

void List::print()
{
	std::cout<<"当前单链表为：";
	Point *temp = first;
	while(temp->next != NULL)
	{
		std::cout<<temp->next->num<<" ";
		temp = temp->next;
	}
	std::cout<<"\n";
}
