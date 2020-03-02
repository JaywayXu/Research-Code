/**
 * Max Sum
 * 
 * Problem Description:
 * Given a sequence a[1],a[2],a[3]......a[n], your job is to calculate the max sum of a sub-sequence.
 * For example, given (6,-1,5,4,-7), the max sum in this sequence is 6 + (-1) + 5 + 4 = 14.
 * 
 * Input:
 * The first line of the input contains an integer T(1<=T<=20) which means the number of test cases.
 * Then T lines follow, each line starts with a number N(1<=N<=100000),
 * then N integers followed(all the integers are between -1000 and 1000).
 * 
 * Output:
 * For each test case, you should output two lines.
 * The first line is "Case #:", # means the number of the test case.
 * The second line contains three integers, the Max Sum in the sequence,
 * the start position of the sub-sequence, the end position of the sub-sequence.
 * If there are more than one result, output the first one.
 * Output a blank line between two cases.
 * 
 * Sample Input:
 * 2
 * 5 6 -1 5 4 -7
 * 7 0 6 -1 1 -6 7 -5
 * 
 * Sample Output:
 * Case 1:
 * 14 1 4
 * 
 * Case 2:
 * 7 1 6
 */

#include<iostream>
using namespace std;
int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int M;
		int obj[100000] = { NULL };
		cout << "Case " << i +1<< ":"<<endl;
		cin >> M;
		int sum, max,j,mx=1,my=1;
		int n = 0;
		for (sum = 0, max = -1111, j = 0; j < M; j++) {
			cin >> obj[j];
			sum += obj[j];
			if (max < sum)
			{
				max = sum;
				my = j + 1;
			}
			if (sum < 0)
			{
				sum = 0;
			}
		}
		int cy = my;
		int t = 0;
		while (1) {
			t=obj[cy - 1] + t;
			if (t == max) {
				mx = cy;
				break;
			}
			cy--;
		}
		cout << max << ' ' << mx << ' ' << my << endl;
		if (i != N - 1)cout << endl;
	}
	return 0;
}

// #include <iostream>
// using namespace std;

// int main()
// {
//     int g;
//     cin>>g;
//     // while (cin>>g && g!=EOF)
//     // {
//         int arr[21][20000];
//         //int sum[21][1000][3],s = 0;
//         int max[21][3];
//         for (int j = 0;j<g;j++) max[j][0] = 0;
//         for (int j = 0;j<g;j++)
//         {
//             int x;
//             cin>>x;
//             for (int i = 0;i <x;i++)
//             {
//                 cin>>arr[j][i];
//             }
//             for (int i = 0; i<x; i++)
//             {
//                 for (int z = i; z<x; z++)
//                 {
//                     int sum_b = 0;
//                     for (int t = 0; t<z-i+1; t++)
//                     {
//                         sum_b += arr[j][i+t];
//                     }
//                     if (sum_b > max[j][0])
//                     {
//                         max[j][0] = sum_b;
//                         max[j][1] = i+1;
//                         max[j][2] = z+1;
//                     }
//                     // sum[j][s][0] = sum_b;
//                     // sum[j][s][1] = i+1;
//                     // sum[j][s][2] = z+1;
//                     // s++;
//                 }
//             }
//             // for (int z = 0;z<s;z++)
//             // {
//             //     if (sum[j][z][0] > max[j][0])
//             //     {
//             //         max[j][0] = sum[j][z][0];
//             //         max[j][1] = sum[j][z][1];
//             //         max[j][2] = sum[j][z][2];
//             //     }
//             // }
//         }

//         for (int j = 0;j<g;j++)
//         {
//             if(j == g-1)
//             {
//                 cout << "Case " << j+1 << ":" << endl;
//                 cout<<max[j][0]<<" "<<max[j][1]<<" "<<max[j][2]<<endl;
//             }
//             else
//             {
//                 cout << "Case " << j+1 << ":" << endl;
//                 cout<<max[j][0]<<" "<<max[j][1]<<" "<<max[j][2]<<endl<<endl;
//             }
//         }
//     // }
//     return 0;
// }