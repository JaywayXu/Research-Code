#include<iostream>
using namespace std;
int find_max(int a, int b) {
	return a > b ? a : b;
}

int main()
{
	int m, n;
	cin >> m >> n;
	cout<<find_max(m, n);
	return 0;
}
