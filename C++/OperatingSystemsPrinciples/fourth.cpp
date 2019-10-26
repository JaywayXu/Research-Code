#include <iostream>
#include <string>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>

using namespace std;

int P1;
int P2;

void handler(int signo)
{
    kill(P1,SIGUSR1);
    kill(P2,SIGUSR2);
    sleep(3);
    cout << "Parent Process is Killed!" << endl;;
    exit(0);
}

void kill_exit(int signo)
{
    if (P1 == getpid())
        cout << "Child Process 1 is killed by Parent!" << endl;
    else if (P2 == getpid())
        cout << "Child Process 2 is killed by Parent!" << endl;
    else cout << "erroe" << endl;
    exit(0);
}


int main()
{
    int bufsize = 512;
    char rbuffer[bufsize];

    int pid1=0;
    int pid2=0;

    int fd[2];
    pipe(fd);

    pid1=fork();

    int i = 0;

    if(pid1 == -1)
    { 
        printf("Erro");
    }
    else if(pid1 == 0)
    {
        P1 = getpid();
        signal(2,SIG_IGN);
        signal(SIGUSR1,kill_exit);
        while (1) {
            close(fd[0]);
            i++;
            string str = "I send message "+to_string(i)+" time\n";
            write(fd[1],str.c_str(),strlen(str.c_str())+1);
            sleep(1);
        }
    }
    else if(pid1 > 0)
    {
        pid2=fork();
        if(pid2==-1)
        {
            printf("Erro");
        }
        else if(pid2==0)
        {
            P2 = getpid();
            signal(2,SIG_IGN);
            signal(SIGUSR2,kill_exit);
            while (1) {
                close(fd[1]);
                read(fd[0],rbuffer,bufsize+1);
                printf(rbuffer);
                sleep(1);
            }
        }
        else if(pid2>0)
        {
            P1 = pid1;
            P2 = pid2;            
            signal(2,handler);
            while(1)
            {
            }
        }
    }
    return 0;
}