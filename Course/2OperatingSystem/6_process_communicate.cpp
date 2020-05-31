/**
 * 操作系统上机第六题：进程通信
 * 编写一主程序可以由用户选择如下三种进程通信方式：
 *  1.使用管道来实现父子进程之间的进程通信
 *   子进程向父进程发送自己的进程标识符，
 *   以及字符串“is sending a message to parent”，
 *   父进程则通过管道读出子进程发来的消息，
 *   将消息显示在屏幕上，然后终止。
 *  2.使用消息缓冲队列来实现 client 进程和 server 进程之间的通信
 *   server进程先建立一个关键字为SVKEY（如 75）的消息队列，
 *   然后等待接收类型为REQ（例如 1）的消息，
 *   在收到请求消息后，它便显示字符串“serving for client”，
 *   和接收到的 client 进程的进程标识数，
 *   表示正在为 client 进程服务；
 *   然后再向 client 进程发送应答消息，
 *   该消息的类型是 client 进程的进程标识数，
 *   而正文则是 server 进程自己的标识ID。
 *   client进程则向消息队列发送类型为REQ的消息（消息的正文为自己的进程标识 ID），
 *   以取得 sever 进程的服务，并等待 server 进程发来的应答；
 *   然后显示字符串“receive reply from”和接收到的server进程的标识ID。
 *  3.使用共享存储区来实现两个进程之间的进程通信
 *   进程 A 创建一个长度为 512 字节的共享内存，
 *   并显示写入该共享内存的数据，
 *   进程 B 将共享内存附加到自己的地址空间，
 *   并向共享内存中写入数据。
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

using namespace std;

struct MSG {
	long int mtype;
	int mtext;
};

class Process_contact {
	private:
		const int SVKEY=75;

		//use pipe
		int sub_pid;
		int pipe0[2];
		char str_in[50], str_out[50];

		//use message_queue
		int msgpid, server, client;
		MSG msg;

		//use share_memory
		int id;
    		char *addr;
    		char context_s[512];

	public:
		void pipe_f();
		void msg_que_f();
		void share_mem_f();
		void run();
};

void Process_contact::pipe_f(){
    if(pipe(pipe0)<0){
        cout<<"Fail to pipe!"<<endl;
    }
    if((sub_pid=fork())==0){
        sprintf(str_out,"%d is sending a message to parent",getpid());
        cout << str_out << endl;
        write(pipe0[1],str_out,sizeof(str_out));
    }
    else if(sub_pid>0){ //父进程
	read(pipe0[0],str_in,sizeof(str_out));
        cout<<str_in<<endl;
    }
    close(pipe0[0]);
    close(pipe0[1]);
}

void Process_contact::msg_que_f(){
    if((server=fork())==0){
        msgpid=msgget(SVKEY,IPC_CREAT);
        msgrcv(msgpid,&msg,100,2,0);
        cout<<"serving for client "<<msg.mtext<<endl;
        msg.mtype = msg.mtext;
        msg.mtext = getpid();
        msgsnd(msgpid,&msg,sizeof(int),0);
        return;
    }
    if((client=fork())==0){
        msgpid=msgget(SVKEY,0);
        if(msgpid!=-1){
            msg.mtype = 1; //REQ = 1
	    msg.mtext = getpid();
            msgsnd(msgpid,&msg,sizeof(int),0);
            msgrcv(msgpid,&msg,100,2,0);
            cout<<"receive reply from "<<msg.mtext<<endl;
            return;
        }
    }
    wait(0); 
    wait(0);
}

void Process_contact::share_mem_f(){
    id=shmget(SVKEY,512,0777|IPC_CREAT);
    if(id==-1){
        cout<<"shmget error"<<endl;
    }
    if(fork()==0){
        sprintf(context_s,"%d is sending message to parent",getpid());
        cout<<context_s<<endl;
        addr=(char *)shmat(id,0,0);
        strcpy(addr,context_s);
        shmdt(addr);
        exit(0);
     }else{
        wait(0);
        addr=(char *)shmat(id,0,0);
        cout<<addr<<endl;
        shmdt(addr);
        shmctl(id,IPC_RMID,0);
      }
}

void Process_contact::run(){
    int type;
    cout<<"1:pipe  2:message_queue  3:share_memory  0:exit"<<endl;
    while(1){
        cin >> type;
	switch(type){
            case 1:
                pipe_f();break;
            case 2:
                msg_que_f();break;
            case 3:
                share_mem_f();break;
	    case 0:
		return;
        }
    }
}

int main() {
	Process_contact p;
	p.run();
	return 0;
}
