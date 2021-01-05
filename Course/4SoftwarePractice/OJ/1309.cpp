#include <iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
int factors(int num, int k) {
	bool flag = true;
	if (num % k != 0) {
		flag = false;
		return 0;
	}
	else {
		if (flag == true) {
			return factors(num / k, k) + 1;
		}
		else {
			return 0;
		}
	}
}

int main() {
	int num, k;
	cin >> num >> k;
	cout << factors(num, k) << endl;
	return 0;
}
