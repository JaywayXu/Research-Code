#include<iostream>
#include"List.h"

int main()
{
	List list;
	for(int i=20;i>0;i--)list.add(i);
	list.print();
	list.add(14,5);
	list.print();
	list.sort();
	list.print();
	list.del(14);
	list.print();
	std::cout<<list.len()<<"\n";
	return 0;
} 