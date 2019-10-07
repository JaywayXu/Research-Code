#include <stdio.h>
#include <mpi.h>
int main(int argc, char * argv[])
{
  int myrank;

  // 初始化MPI环境
  //从这里可以看到，一般MPI指令是MPI_跟一个大写字母
//开始的单词，后面都是小写字母。
  MPI_Init(&argc, &argv);



  // 获取当前进程在通信器MPI_COMM_WORLD中的进程号
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    printf("myrank = %d: Hello, world!\n", myrank);

  MPI_Finalize();
  return 0;
}
