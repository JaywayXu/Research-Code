#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

void paraQuickSort(int* data, int start, int end, int m, int id, int MyID);
int quickSort(int* data, int start, int end);
int partition(int* data, int start, int end);
int pow2(int num);
int log2(int num);

int main(int argc, char* argv[])
{
	int DataSize;
	int* data=NULL;
	int MyID, SumID;
	int i, j;
	int m, r;
	double starttime, endtime;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &SumID);
	MPI_Comm_rank(MPI_COMM_WORLD, &MyID);
	printf("start %d/%d\n", MyID, SumID);

	if (MyID == 0)
	{ // 读取文件
		FILE* finput;
		finput = fopen("input.txt", "r");
		if (finput == NULL)
		{
			printf("Data file not found\n");
			return(-1);
		}
		fscanf(finput, "%d", &DataSize);
		printf("scale=%d\n", DataSize);
		int j;
		data = (int*)malloc(DataSize * sizeof(int));
		int input;
		for (j = 0; j < DataSize; j++)
		{
			fscanf(finput, "%d", &input);
			data[j] = input;
		}

	}
	starttime = MPI_Wtime();
	m = log2(SumID);

	MPI_Bcast(&DataSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	paraQuickSort(data, 0, DataSize - 1, m, 0, MyID);

	if (MyID == 0)
	{ // 输出
		for (i = 0; i < DataSize; i++)
		{
			printf("%10d", data[i]);
		}
		printf("\n");
	}
	endtime = MPI_Wtime();
	MPI_Finalize();
	printf("time of %d is %lf ms\n", MyID, (endtime - starttime) * 1000);
	return 0;
}

void paraQuickSort(int* data, int start, int end, int m, int id, int MyID)
{ //主进程将任务进行划分，不同的进程并行排序
	int i, j;
	int r;
	int MyLength;
	int* tmp=NULL;
	MPI_Status status;
	MyLength = -1;
	if (m == 0)
	{
		if (MyID == id)
			quickSort(data, start, end);
		return;
	}

	if (MyID == id)
	{
		r = partition(data, start, end);
		MyLength = end - r;
		MPI_Send(&MyLength, 1, MPI_INT, id + pow2(m - 1), MyID, MPI_COMM_WORLD);
		if (MyLength != 0)
			MPI_Send(data + r + 1, MyLength, MPI_INT, id + pow2(m - 1), MyID, MPI_COMM_WORLD);

	}

	if (MyID == id + pow2(m - 1))
	{
		MPI_Recv(&MyLength, 1, MPI_INT, id, id, MPI_COMM_WORLD, &status);
		if (MyLength != 0)
		{
			tmp = (int*)malloc(MyLength * sizeof(int));
			if (tmp == 0) perror("Malloc memory error!");
			MPI_Recv(tmp, MyLength, MPI_INT, id, id, MPI_COMM_WORLD, &status);
		}
	}
	j = r - 1 - start;
	MPI_Bcast(&j, 1, MPI_INT, id, MPI_COMM_WORLD);
	if (j > 0)
		paraQuickSort(data, start, r - 1, m - 1, id, MyID);
	j = MyLength;
	MPI_Bcast(&j, 1, MPI_INT, id, MPI_COMM_WORLD);
	if (j > 0)
		paraQuickSort(tmp, 0, MyLength - 1, m - 1, id + pow2(m - 1), MyID);
	if ((MyID == id + pow2(m - 1)) && (MyLength != 0))
		MPI_Send(tmp, MyLength, MPI_INT, id, id + pow2(m - 1), MPI_COMM_WORLD);
	if ((MyID == id) && (MyLength != 0))
		MPI_Recv(data + r + 1, MyLength, MPI_INT, id + pow2(m - 1), id + pow2(m - 1), MPI_COMM_WORLD, &status);
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

int pow2(int num)
{ // 求2的num次方
	int result = 1 << num;
	return result;
}

int log2(int num)
{ // 求num关于2的对数
	int i, j;
	i = 1;
	j = 2;
	while (j < num)
	{
		j = j * 2;
		i++;
	}
	if (j > num)
		i--;
	return i;
}
