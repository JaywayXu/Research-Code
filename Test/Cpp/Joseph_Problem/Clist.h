#include<iostream>

class Point
{
public:
	int num;
	Point *next;
};

class Clist
{
public:
	Point *there = NULL;

	Clist(int);
	~Clist();
	void run(int,int);
};

Clist::Clist(int x)
{
	Point *head = new Point();
	Point *p = head,*q;
	for(int i=1;i<=x;i++)
	{
		q = new Point();
		q->num = i;
		p->next = q;
		p = q;
	}
	p->next = head->next;
	delete(head);
	this->there = p->next;
}

Clist::~Clist()
{
	Point *temp;
	while(there != there->next)
	{
		temp = there->next;
		there->next = temp->next;
		delete(temp);
		there = there->next;
	}
}

void Clist::run(int n,int m)
{
	Point *temp;
	m %= n;
	while(there != there->next)
	{
		for(int i=1;i<m-1;i++)
		{
			there = there->next;
		}
		std::cout<<there->next->num<<"->";
		temp = there->next;
		there->next = temp->next;
		delete(temp);
		there = there->next;
	}
	std::cout<<there->num<<"\n";
}