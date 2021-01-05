#include <stdio.h>
#include <iostream>
using namespace std;
struct student
{
	int age;
	char *name;
};

void printArray(void *arr, int eleSize, int len, void (*pPrint)(void *));
void printInt(void *data)
{
	int *temp = (int *)data;
	printf("%d\n", *temp);
}
void printStudent(void *data)
{
	student *temp = (student *)data;
	printf("%s, %d\n", temp->name, temp->age);
}
void printDouble(void *data)
{
	double *temp = (double *)data;
	printf("%.2lf\n", *temp);
}
void printArray(void *arr, int eleSize, int len, void (*pPrint)(void *))
{
	char *start = (char *)arr;
	for (int i = 0; i < len; i++)
	{
		char *end = start + i * eleSize;
		pPrint(end);
	}
}

void sort(void *arr, int eleSize, int len, int (*p_func)(void *, void *), void (*p_func2)(void *, void *));
void swapInt(void *a, void *b)
{
	int *s = (int *)a;
	int *q = (int *)b;
	int tmp = *s;
	*s = *q;
	*q = tmp;
}
void swapStruct(void *a, void *b)
{
	student *s = (student *)a;
	student *q = (student *)b;
	student tmp = *s;
	*s = *q;
	*q = tmp;
}
void swapDouble(void *a, void *b)
{
	double *s = (double *)a;
	double *q = (double *)b;
	double tmp = *s;
	*s = *q;
	*q = tmp;
}
int compareInt(void *s, void *q)
{
	int *a = (int *)s;
	int *b = (int *)q;
	if (*a < *b)
		return -1;
	if (*a == *b)
		return 0;
	else
		return 1;
}
int compareStruct(void *s, void *q)
{
	student *a = (student *)s;
	student *b = (student *)q;
	if ((*a).age < (*b).age)
		return -1;
	if ((*a).age == (*b).age)
		return 0;
	else
		return 1;
}
int compareDouble(void *s, void *q)
{
	double *a = (double *)s;
	double *b = (double *)q;
	if (*a < *b)
		return -1;
	if (*a == *b)
		return 0;
	else
		return 1;
}

void sort(void *arr, int eleSize, int len, int (*p_func)(void *, void *), void (*p_func2)(void *, void *))
{
	char *start = (char *)arr;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i; j < len - 1 - i; j++)
		{
			char *a = start + j * eleSize;
			char *b = start + j * eleSize + eleSize;
			if (p_func(a, b) == 1)
			{
				p_func2(a, b);
			}
		}
	}
}

void test()
{
	// int
	int arr[] = {8, 4, 5, 6, 7, 1, 2, 12, 34, 12, 15};
	int eleSize = sizeof(arr[0]);
	int len = sizeof(arr) / sizeof(arr[0]);
	sort(arr, eleSize, len, compareInt, swapInt);
	printArray(arr, eleSize, len, printInt);
	cout << endl;

	// struct
	student arr2[4];
	arr2[0] = {10, "aaa"};
	arr2[1] = {9, "bbb"};
	arr2[2] = {8, "ccc"};
	arr2[3] = {3, "ddd"};
	int eleSize2 = sizeof(arr2[0]);
	int len2 = sizeof(arr2) / sizeof(arr2[0]);
	sort(arr2, eleSize2, len2, compareStruct, swapStruct);
	printArray(arr2, eleSize2, len2, printStudent);
	cout << endl;

	// double
	double arr3[10] = {10.0, 9.3, 8.2, 7.1, 6.1, 5.7, 4.8, 3.6, 2.0, 1.1};
	double eleSize3 = sizeof(arr3[0]);
	double len3 = sizeof(arr3) / sizeof(arr3[0]);
	sort(arr3, eleSize3, len3, compareDouble, swapDouble);
	printArray(arr3, eleSize3, len3, printDouble);
	cout << endl;
}
int main()
{
	test();
	return 0;
}