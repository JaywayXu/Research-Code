#include<iostream>
#include<math.h>

using namespace std;
int reverse(int a) {
	int reverse_a = 0;
	if (a <= 0) {
		return 0;
	}
	else {
		int weishu = 0;
		int temp = a;
		while (temp > 0) {
			temp = temp / 10;
			weishu++;
		}
		//cout << weishu << endl;
		while (a > 0) {
			reverse_a += (a % 10) * int(pow(10, weishu - 1));
			weishu--;
			a = a / 10;
		}
	}
	return reverse_a;
}

int main()
{
	int n;
	cin >> n;
	cout << reverse(n) << endl;
	return 0;
}
