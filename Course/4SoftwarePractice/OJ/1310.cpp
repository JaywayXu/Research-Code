#include <iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
int get_total(int k) {
	int count = 0;
	int temp = k;
	int sum = 0;
	while (count != 10 && temp > 0) {
		if (temp % 13==0 || temp % 17 == 0) {
			sum += temp;
			count++;
		}
		temp--;
	}
	return sum;
}

int main() {
	int n;
	cin >> n;
	cout<<get_total(n)<<endl;
	return 0;
}
