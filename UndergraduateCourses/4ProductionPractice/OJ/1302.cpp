#include<iostream>
using namespace std;
void find_maan(int **a) {
	int i, j, k;
	//行中最大， 列中最小
	int min = 32767;
	int max = -32767;
	int min_row = -1;
	int max_col = -1;
	for (i = 0; i < 4; i++) {
		max_col = -1;
		for (j = 0; j < 4; j++) {
			if (a[i][j] > max) {     //找第i行中最大的元素
				max = a[i][j];
				max_col = j;
			}
		}
		for (k = 0; k < 4; k++) {
			if (a[k][max_col] < min) {
				min = a[k][max_col];
				min_row = k;
			}
		}
		
		if (min_row == i) {
			cout << "马鞍点在" << min_row << "行" << max_col << "列:" <<a[min_row][max_col]<<endl;
			break;
		}
		else {
			cout << "这个矩阵中没有马鞍点！" << endl;
			break;
		}
	}
}

int main()
{
	int i, j;
	int **matrix;
	matrix = new int* [4];
	for (i = 0; i < 4; i++) {
		matrix[i] = new int[4];
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			cin >> matrix[i][j];
		}
	}
	find_maan(matrix);
	return 0;
}