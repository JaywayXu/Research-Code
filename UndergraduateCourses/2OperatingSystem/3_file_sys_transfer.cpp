/**
 * 操作系统上机第三题：熟悉linux文件系统调用
 * 1、使用文件系统调用编写一个文件工具 filetools，使其具有以下功能： 
 *  1.创建新文件
 *  2.写文件
 *  3.读文件
 *  4.修改文件权限
 *  5.查看当前文件权限
 *  0.退出
 * 2、提示用户输入功能号，并根据用户输入的功能选择相应的功能；
 * 3、文件按可变记录文件组织，具体记录内容自行设计。
 */

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;

void create_new_file()
{
    cout << "please input the file name: ";
    char file_name[20];
    cin >> file_name;

    int fd;
    fd = open(file_name, O_RDWR | O_CREAT, 0666);
    if (fd < 0)
    {
        cout << "error" << endl;
        exit(1);
    }
    else
    {
        cout << "success = " << fd << endl;
        close(fd);
        cout << "closed" << endl;
    }
}

void write_file()
{
    cout << "please input the file name: ";
    char file_name[20];
    cin >> file_name;

    int fd;
    umask(0000);
    fd = open(file_name, O_RDWR | O_CREAT, 0666);
    if (fd < 0)
    {
        cout << "error" << endl;
        exit(1);
    }
    else
    {
        cout << "success = " << fd << endl;
        //write
        char buf[1024] = "hello world, lyc write this with cpp program.\n";
        int rtnum = write(fd, buf, strlen(buf));
        if (rtnum != -1)
        {
            cout << "buf = " << buf << endl;
        }
        else
        {
            cout << "error" << endl;
            exit(1);
        }
        close(fd);
        cout << "closed" << endl;
    }
}

void read_file()
{
    cout << "please input the file name: ";
    char file_name[20];
    cin >> file_name;

    int fd;
    umask(0000);
    fd = open(file_name, O_RDWR | O_CREAT, 0666);
    if (fd < 0)
    {
        cout << "error" << endl;
        exit(1);
    }
    else
    {
        cout << "success = " << fd << endl;
        //read
        char buf[1024];
        memset(buf, 0, 1024);
        int rtnum = read(fd, buf, 1024);
        if (rtnum != -1)
        {
            cout << "buf = " << buf << endl;
        }
        else
        {
            cout << "error" << endl;
            exit(1);
        }
        close(fd);
        cout << "closed" << endl;
    }
}

void change_mode()
{
    cout << "please input the file name: ";
    char file_name[20];
    cin >> file_name;

    char buf[20];
    cout << "please input the mode: ";
    cin >> buf;

    int mode = (atoi(buf)); //将要设置的权限字符串转换成整数,如"777"转换成777
    int mode_u;             //所有者权限
    int mode_g;             //所属组权限
    int mode_o;             //其他人权限

    if (mode > 777 || mode < 0)
    { //验证要设置的权限是否合法
        printf("Error mode!\n");
        exit(0);
    }

    mode_u = mode / 100;
    mode_g = mode / 10 % 10;
    mode_o = mode % 10;
    mode = mode_u * 8 * 8 + mode_g * 8 + mode_o; //八进制转换

    if (chmod(file_name, mode) == -1)
    { //调用chmod函数进行权限修改
        perror("Error mode!\n");
        exit(1);
    }
}

void get_mode()
{
    cout << "please input the file name: ";
    char file_name[20];
    cin >> file_name;

    char str[30];
    struct stat sb;
    if (stat(file_name, &sb) == -1)
    {
        perror("stat");
        exit(1);
    }
    int mode = sb.st_mode;

    //把模式值转化为字符串
    str[0] = '-';
    if (S_ISDIR(mode))
        str[0] = 'd'; /*-文件夹-*/
    if (S_ISCHR(mode))
        str[0] = 'c'; /*-字符设备-*/
    if (S_ISBLK(mode))
        str[0] = 'b'; /*-块设备-*/
    if (mode & S_IRUSR)
        str[1] = 'r'; /*--用户的三个属性-*/
    else
        str[1] = '-';
    if (mode & S_IWUSR)
        str[2] = 'w';
    else
        str[2] = '-';
    if (mode & S_IXUSR)
        str[3] = 'x';
    else
        str[3] = '-';
    if (mode & S_IRGRP)
        str[4] = 'r'; /*--组的三个属性-*/
    else
        str[4] = '-';
    if (mode & S_IWGRP)
        str[5] = 'w';
    else
        str[5] = '-';
    if (mode & S_IXGRP)
        str[6] = 'x';
    else
        str[6] = '-';
    if (mode & S_IROTH)
        str[7] = 'r'; /*-其他人的三个属性-*/
    else
        str[7] = '-';
    if (mode & S_IWOTH)
        str[8] = 'w';
    else
        str[8] = '-';
    if (mode & S_IXOTH)
        str[9] = 'x';
    else
        str[9] = '-';
    str[10] = '\0';
    cout << str << endl;
}

int main()
{
	int type;
	while(1) {
		cout << "0.创建文件 1.写入文件 2.读取文件" << endl
			<< "3.更改mode 4.读取mode" << endl;
		cin >> type;
		switch (type) {
		case 0:
    			create_new_file();
			break;
		case 1:
    			write_file();
			break;
		case 2:
			read_file();
			break;
		case 3:
			change_mode();
			break;
		case 4:
			get_mode();
			break;
		default:
			return 0;
		}
	}
    return 0;
}
