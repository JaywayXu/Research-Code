// 
// #include <iostream>
// using namespace std;
// int f(int a,int b,unsigned long long n)
// {
//     if (n == 1) return 1;
//     else if (n == 2) return 1;
//     else return (a*f(a,b,n-1) + b*f(a,b,n-2)) % 7;
// }
// int main()
// {
//     int a,b;
//     unsigned long long n;
//     while(cin>>a>>b>>n)
//     {
//         if (a==0 && b==0 && n==0) break;
//         cout << f(a,b,n) << endl;
//     }
//     return 0;
// }

#include<iostream>

using namespace std;

int main()
{
	int a, b, c;
	int arr[48];
	while (cin >> a >> b >> c)
	{
		if (a == 0 && b == 0 && c == 0)break;
		arr[0] = 1; arr[1] = 1;
		for (int i = 2; i < 48; i++)
		{
			arr[i] = ((a * arr[i - 1] + b * arr[i - 2]) % 7);
		}
		cout << arr[(c-1)%48] << endl;
	}
	return 0;
}