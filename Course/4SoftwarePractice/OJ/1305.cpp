#include<iostream>
using namespace std;
void swap_1(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int m, n;
	cin >> m >> n;
	swap_1(m, n);
	cout << m << endl;
	cout << n << endl;
	return 0;
}
