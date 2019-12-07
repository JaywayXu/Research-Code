/**
 * 操作系统上机第四题：进程管理
 * 父进程使用系统调用pipe()建立一个管道，然后使用系统调用fork()创建两个子进程：
 * 子进程1和子进程2
 * 子进程1每隔1秒通过管道向子进程2发送数据：
 *  I send message x times.（x初值为1，以后发送一次后做加一操作）
 * 子进程2从管道读出信息，并显示在屏幕上
 * 父进程用系统调用signal()来捕捉来自键盘的中断信号SIGINT（即按Ctrl+C键,）
 * 当捕捉到中断信号后，父进程用系统调用kill()向两个子进程发出信号
 * 子进程捕捉到信号后分别输出如下信息后终止： 
 *  Child Process 1 is killed by Parent!
 *  Child Process 2 is killed by Parent!
 * 父进程等待两个子进程终止后，释放管道并输出如下的信息后终止
 *  Parent Process is Killed!
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

using namespace std;

int P1;
int P2;

void handler(int signo)
{
    kill(P1, SIGUSR1);
    kill(P2, SIGUSR2);
    sleep(3);
    cout << "Parent Process is Killed!" << endl;
    ;
    exit(0);
}

void kill_exit(int signo)
{
    if (P1 == getpid())
        cout << "Child Process 1 is killed by Parent!" << endl;
    else if (P2 == getpid())
        cout << "Child Process 2 is killed by Parent!" << endl;
    else
        cout << "erroe" << endl;
    exit(0);
}

int main()
{
    int bufsize = 512;
    char rbuffer[bufsize];

    int pid1 = 0;
    int pid2 = 0;

    int fd[2];
    pipe(fd);

    pid1 = fork();

    int i = 0;

    if (pid1 == -1)
    {
        printf("Erro");
    }
    else if (pid1 == 0) //child 1
    {
        P1 = getpid();
        signal(2, SIG_IGN);
        signal(SIGUSR1, kill_exit);
        while (1)
        {
            close(fd[0]);
            i++;
            string str = "I send message " + to_string(i) + " time\n";
            write(fd[1], str.c_str(), strlen(str.c_str()) + 1);
            sleep(1);
        }
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == -1)
        {
            printf("Erro");
        }
        else if (pid2 == 0) //child 2
        {
            P2 = getpid();
            signal(2, SIG_IGN);
            signal(SIGUSR2, kill_exit);
            while (1)
            {
                close(fd[1]);
                read(fd[0], rbuffer, bufsize + 1);
                printf(rbuffer);
                sleep(1);
            }
        }
        else if (pid2 > 0) //parent
        {
            P1 = pid1;
            P2 = pid2;
            signal(2, handler);
            while (1)
            {
            }
        }
    }
    return 0;
}
