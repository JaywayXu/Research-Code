/**
 * Tick and Tick
 * 
 * Problem Description:
 * The three hands of the clock are rotating every second and meeting each other many times everyday.
 * Finally, they get bored of this and each of them would like to stay away from the other two.
 * A hand is happy if it is at least D degrees from any of the rest.
 * You are to calculate how much time in a day that all the hands are happy.
 * 
 * Input:
 * The input contains many test cases.
 * Each of them has a single line with a real number D between 0 and 120, inclusively.
 * The input is terminated with a D of -1.
 * 
 * Output:
 * For each D,
 * print in a single line the percentage of time in a day that all of the hands are happy,
 * accurate up to 3 decimal places.
 * 
 * Sample Input:
 * 0
 * 120
 * 90
 * -1
 * 
 * Sample Output:
 * 100.000
 * 0.000
 * 6.251
 */

#include<iostream>
#include<cmath>

using namespace std;

class Hand
{
public:
	int v;
	int single = 0;
	Hand(int a) { v = a; }
	void move(int t,int &single)
	{
		single = (v * t)%(360*120);
	}
};

int main()
{
	int D;
	Hand one(1), two(12), three(6*120);
	while (cin >> D) 
	{
		int x = 0;
		if (D == -1)break;
		for (int t = 0; t < 24 * 60 * 60; t++)
		{
			int a=0, b=0, c=0;
			one.move(t,one.single); two.move(t,two.single); three.move(t,three.single);
			if (abs(one.single - two.single) > 180 * 120) a = 360 * 120 - abs(one.single - two.single);
			else a = abs(one.single - two.single);
			if (abs(one.single - three.single) > 180 * 120) b = 360 * 120 - abs(one.single - three.single);
			else b = abs(one.single - three.single);
			if (abs(two.single - three.single) > 180 * 120) c = 360 * 120 - abs(two.single - three.single);
			else c = abs(two.single - three.single);
			if (a >= (D * 120) && b >= (D * 120) && c >= (D * 120))x++;
		}
		cout << x/(60.0*60.0*24.0)*100.0 << endl;
	}
	return 0;
}

