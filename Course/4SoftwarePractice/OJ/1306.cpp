#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;
double get_dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main()
{
	double x1, y1;
	double x2, y2;
	cin >> x1 >> y1;
	cin >> x2 >> y2;
	double dist = get_dist(x1, y1, x2, y2);
	cout << "¾àÀëÎª£º"<<setprecision(7) << dist << endl;
	return 0;
}
