#include<iostream>
#include"Clist.h"

int main()
{
	int n = 41;
	int m = 3;
	Clist *list = new Clist(n);
	list->run(n,m);
	return 0;
}