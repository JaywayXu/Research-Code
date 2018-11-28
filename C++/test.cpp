#include<iostream>

class Papa
{
public:
	Papa* a;
	Papa(); 
	virtual void Do();
};

Papa::Papa()
{
	a = this;
}

void Papa::Do()
{
	std::cout<<"Papa";
}

class Son : public Papa
{
public:
	void Do();
};

void Son::Do()
{
	std::cout<<"Son";
}

Son son;

int main()
{
	son.a->Do();
	return 0;
}