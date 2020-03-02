/**
 * 歌曲信息管理系统
 * 实现了：
 * - 用文件储存信息，运行每一个选项都会将文件中的数据写入内存，在运行完该模块之后再写入文件
 * - 第一个功能，录入歌曲记录
 * - 第二个功能，查找并删除记录
 * - 第三个功能，浏览记录
 * - 第四个功能，查找信息记录
 * - 第五个功能，按照作者姓名进行排序并显示
 * 时间：2018/6/28
 */

#include<stdio.h>
#include<string.h>

#define N 50     //储存结构体的数组的长度
#define IS_EXIST 23333     //创建该结构体存在的标志

//歌曲信息结构体
typedef struct SongInfo
{
    char name[20];     //歌曲名
    char author[20];   //作者
    char singer[20];   //演唱者
    char pub_date[6];  //发行年月(yyyymm)

    int _exist;     //方便后面筛选，如果该值等于IS_EXIST,证明该结构体存在
}SI;

//////////↓辅助函数↓//////////

//打开文件并将文件中的内容读取到结构体数组中
int readfile(SI *slist)
{
    int i = 0;
    FILE* rfile = fopen("song.txt","r");     //打开文件，方式为只读，文件名为"song.txt"
    if(!rfile)    //判断是否打开了文件
    {
        printf("open file error\n");
        return -1;
    }
    while(!feof(rfile))     //从文件中读取信息
    {
        fscanf(rfile,"%s%s%s%s",
            &slist[i].name,&slist[i].author,
            &slist[i].singer,&slist[i].pub_date);
        slist[i]._exist = IS_EXIST;
        i++;
    }
    if (fclose(rfile) != 0)     //判断是否关闭了文件
    {
        printf("close file error\n");
        return -1;
    }
    return 0;
}

//保存结构体数组中的内容到文件
int writefile(SI *slist)
{
    int i;
    FILE* wfile = fopen("song.txt","w");     //打开文件，方式为只写，覆盖式写入
    if(!wfile)     //判断是否打开了文件
    {
        printf("open file error\n");
        return -1;
    }
    for(i=0;i<N;i++)     //覆盖式写入文件
    {
        if(slist[i]._exist == IS_EXIST)
        {
            fprintf(wfile,"\n%s %s %s %s",
            slist[i].name,slist[i].author,
            slist[i].singer,slist[i].pub_date);
        }
    }
    if (fclose(wfile) != 0)     //判断是否关闭了文件
    {
        printf("close file error\n");
        return -1;
    }
}

//打印参数结构体的数据内容
void print_data(SI si)
{
    printf("歌曲名：%10s 作者：%10s 演唱者：%10s 发行年月：%6s\n",
                si.name,si.author,
                si.singer,si.pub_date);
}

//////////↓各菜单函数↓//////////

//1.录入
void add_record()
{
    int i;
    int button_2 = 0;     //选项按钮（第二层）
    SI si[N];     //创建临时储存文件中数据的结构体数组
    readfile(si);   //读取文件

    for (i = 0; i < N; i++)
    {
        if(si[i]._exist != IS_EXIST)     //筛选已录入数据的结构体
        {
            printf("请分别输入歌曲名、作者、演唱者、发行年月\n");
            scanf("%s%s%s%s",
                &si[i].name,&si[i].author,
                &si[i].singer,&si[i].pub_date);
            si[i]._exist = IS_EXIST;
            printf("1.继续录入 0.返回界面：");
            scanf("%d",&button_2);
            if(button_2 != 1)break;     //输入"1"之后继续录入
        }
    }

    writefile(si);    //写入文件
}

//2.删除
void delete_record()
{
    int i;
    char temp_name[20];     //临时字符串，存输入的姓名
    SI si[N];     //创建临时储存文件中数据的结构体数组
    readfile(si);    //读取文件

    printf("请输入要删除的歌曲的名字：");
    scanf("%s",&temp_name);
    for (i = 0; i < N; i++)
    {
        if(si[i]._exist != IS_EXIST)     //当循环到未录入数据的结构体之后跳出循环
        {
            printf("未找到该项记录！\n");
            system("pause");
            break;
        }
        else if(!strcmp(si[i].name,temp_name))     //比较输入的字符串和数据中的信息是否相等
        {
            int button_2 = 0;     //选项按钮（第二层）

            print_data(si[i]);

            printf("1.确认删除 0.取消：");     //找到符合条件的记录后确认是否删除
            scanf("%d",&button_2);
            if(button_2 != 1)break;
            else si[i]._exist = 0;
        }
    }

    writefile(si);    //写入文件
}

//3.浏览
void scan_record()
{
    int i;
    SI si[N];     //创建临时储存文件中数据的结构体数组
    readfile(si);    //读取文件

    printf("查询到的结果为:\n");
    for(i = 0; i<N; i++)     //打印出所有符合搜索条件的记录
    {
        if(si[i]._exist == IS_EXIST)     //筛选出已录入数据的记录
        {
            print_data(si[i]);
        }
    }
    system("pause");     //暂停

    writefile(si);     //写入文件
}

//4.查询
void search_record()
{
    int i;
    char data[20];     //创建临时储存输入的数据的字符串
    SI si[N];     //创建临时储存文件中数据的结构体数组
    readfile(si);     //读取文件

    printf("请输入歌曲名或作者或演唱者来查找信息：");
    scanf("%s",&data);
    printf("查找的结果为:\n");
    for(i = 0; i<N; i++)     //将所有符合条件的记录打印出来
    {
        if(si[i]._exist == IS_EXIST)     //筛选出已录入数据的记录
            if(!strcmp(data,si[i].name) || 
                !strcmp(data,si[i].author) ||
                !strcmp(data,si[i].singer))
            {
                print_data(si[i]);
            }
    }
    system("pause");     //暂停

    writefile(si);     //写入文件
}

//5.分组显示
void sort_record()
{
    int i,j;
    int x=0;     //创建一个临时整形变量来储存已录入数据的记录的条数
    SI si[N];     //创建临时储存文件中数据的结构体数组
    SI temp_si;     //创建临时结构体作为交换结构体数组中两个相邻结构体的媒介
    readfile(si);    //读取文件

    printf("分组后的结果为:\n");
    for(i = 0; i<N; i++)    //计算出已录入数据的记录的条数
    {
        if(si[i]._exist == IS_EXIST)x += 1;
    }
    for(i = 0; i<x-1; i++)     //冒泡排序
    {
        for(j = 0; j<x-i-1; j++)
        {
            if(strcmp(si[j].author,si[j+1].author)>0)     //按照记录的作者进行升序排序
            {
                temp_si = si[j];
                si[j] = si[j+1];
                si[j+1] = temp_si;
            }
        }
    }
    for(i = 0; i<N; i++)     //打印出排序后的所有记录
    {
        if(si[i]._exist == IS_EXIST)print_data(si[i]);
    }
    system("pause");     //暂停

    writefile(si);     //写入文件
}

//////////↓运行函数，程序逻辑主体↓//////////

//运行函数
void Run()
{
    while(1)     //无限循环，每运行完一个模块就返回菜单
    {
        int button_1 = 0;     //选项按钮（第一层）

        //菜单
        printf("---功能菜单---\n");
        printf("1.录入歌曲信息\n");
        printf("2.删除歌曲信息\n");
        printf("3.浏览歌曲信息\n");
        printf("4.查询歌曲信息\n");
        printf("5.分组显示信息\n");
        printf("0.退出管理系统\n");
        printf("-------------\n");
        printf("请选择：");

        scanf("%d",&button_1);     //输入选项按钮（第一层）
        if(button_1 == 0)break;     //为"0"时推出
        else{
            switch(button_1){                    //switch
                case 1:add_record();break;       //输入"1"进入录入模块
                case 2:delete_record();break;    //输入"2"进入删除模块
                case 3:scan_record();break;      //输入"3"进入浏览模块
                case 4:search_record();break;    //输入"4"进入查找模块
                case 5:sort_record();break;      //输入"5"进入排序模块
                default:                         //输入错误重新进入菜单
                    printf("请输入0-5之间的数字！\n");
                    system("pause");
                    break;
            }
        }
    }
}

//////////↓主函数↓//////////

int main()
{
    Run();     //运行
    return 0;
}