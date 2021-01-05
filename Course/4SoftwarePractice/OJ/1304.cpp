#include<iostream>
#include<iomanip>
using namespace std;
void get_average(double a, double b) {
	if (a == 0 || b == 0) {
		cout << "NO" << endl;
	}
	else {
		cout<< setprecision(7) <<2.0 * a * b / (a + b);
	}
}

int main()
{
	double m, n;
	cin >> m >> n;
	get_average(m, n);
	return 0;
}
