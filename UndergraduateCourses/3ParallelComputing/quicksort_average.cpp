#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int quickSort(int *data, int start, int end);
int partition(int *data, int start, int end);

int main(int argc, char *argv[])
{
	int DataSize;
	int *data = NULL;
	int i, j;
	double starttime, endtime;

	MPI_Init(&argc, &argv);

	// 读取文件
	FILE *finput;
	finput = fopen("input.txt", "r");
	if (finput == NULL)
	{
		printf("Data file not found\n");
		return (-1);
	}
	fscanf(finput, "%d", &DataSize);
	data = (int *)malloc(DataSize * sizeof(int));
	int input;
	for (j = 0; j < DataSize; j++)
	{
		fscanf(finput, "%d", &input);
		data[j] = input;
	}

	starttime = MPI_Wtime();

	// 快排
	quickSort(data, 0, DataSize - 1);

	// 输出
	for (i = 0; i < DataSize; i++)
	{
		printf("%10d", data[i]);
	}
	printf("\n");

	endtime = MPI_Wtime();
	MPI_Finalize();
	printf("all run time is %lf ms\n", (endtime - starttime) * 1000);
	return 0;
}

int quickSort(int *data, int start, int end)
{ // 递归快速排序
	int r;
	int i;
	if (start < end)
	{
		r = partition(data, start, end);
		quickSort(data, start, r - 1);
		quickSort(data, r + 1, end);
	}
	return 0;
}

int partition(int *data, int start, int end)
{ // 根据枢纽元素划分数组
	int pivo;
	int i, j;
	int tmp;
	pivo = data[end];
	i = start - 1;
	for (j = start; j < end; j++)
		if (data[j] <= pivo)
		{
			i++;
			tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
	tmp = data[i + 1];
	data[i + 1] = data[end];
	data[end] = tmp;
	return i + 1;
}
