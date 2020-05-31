#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <limits>
#include "Student.h"
#include "Sgms.h"

void Sgms::run()
{
    while(1)
    {
        std::cout
        << "---------------" << std::endl
        << "    功能菜单    " << std::endl
        << "---------------" << std::endl
        << "1. 录入学生记录" << std::endl
        << "2. 删除学生记录" << std::endl
        << "3. 修改学生记录" << std::endl
        << "4. 查找学生记录" << std::endl
        << "5. 成绩统计分析" << std::endl
        << "6. 成绩高低排序" << std::endl
        << "7. 成绩文件操作" << std::endl
        << "0. 退出程序" << std::endl
        << "---------------" << std::endl
        << "请输入你要使用的功能编号: ";

        int button_1 = 0;
        std::cin >> button_1;
        if(button_1 == 0)break;
        else{
            switch (button_1) {
                case 1:add_record();break;
                case 2:delete_record();break;
                case 3:change_record();break;
                case 4:search_record();break;
                case 5:analyse_record();break;
                case 6:sort_record();break;
                case 7:file_record();break;
            }
        }
        std::cout << "输入任意字符以继续：";
        std::string key;std::cin >> key;std::cout << std::endl;
    }
}


void Sgms::add_record()
{
    std::cout << "请分别输入：学号、姓名、数学成绩、物理成绩、英语成绩" << std::endl;
    std::string number, name;double math,physics,english;

    int button_2 = 0;
    do{
        std::cin >> number >> name >> math >> physics >> english;
        Student temp_stu(number,name,math,physics,english);
        List.push_back(temp_stu);
        std::cout << "！录入成功！" << std::endl
                << "1.继续录入 0.返回界面：";
        std::cin >> button_2;
    }while(button_2 == 1);
}

void Sgms::delete_record()
{
    std::cout << "请输入要删除的记录的学号或姓名:";
    std::string temp_data;
    std::cin >> temp_data;
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        if(temp_data == (*i).number || temp_data == (*i).name)
        {
            (*i).print_data();
            std::cout << "1.确认删除 0.取消：";
            int button_2 = 0;
            std::cin >> button_2;
            switch (button_2) {
                case 1:{
                    List.erase(i);
                    std::cout << "！删除成功！" << std::endl;
                    }break;
                case 0:break;
            }
            break;
        }
        if((i+1) == List.end())std::cout << "！未找到此记录！" << std::endl;
    }
}

void Sgms::change_record()
{
    std::cout << "请输入要修改的记录的学号或姓名:";
    std::string temp_data;
    std::cin >> temp_data;
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        if(temp_data == (*i).number || temp_data == (*i).name)
        {
            int button_2 = 0;
            std::cout << "请选择要修改的项目："
                    << "1.数学 2.物理 3.英语 4.学号 5.姓名 0.返回：";
            std::cin >> button_2;
            switch (button_2) {
                case 1:change_data((*i),1);break;
                case 2:change_data((*i),2);break;
                case 3:change_data((*i),3);break;
                case 4:change_data((*i),4);break;
                case 5:change_data((*i),5);break;
                case 0:break;
            }
            break;
        }
        if((i+1) == List.end())std::cout << "！未找到此记录！" << std::endl;
    }
}

void Sgms::search_record()
{
    std::cout << "1.个人成绩 2.分段名单 0.返回：";
    int button_2 = 0;
    std::cin >> button_2;
    switch(button_2){
        case 1:{
            std::cout << "请输入要查找的记录的学号或姓名(可模糊查找):";
            std::string temp_data;
            std::cin >> temp_data;
            std::cout << "查找的结果为：" << std::endl;
            for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
            {
                if((*i).number.find(temp_data) != std::string::npos || (*i).name.find(temp_data) != std::string::npos)
                {
                    (*i).print_data();
                }
            }
        }break;
        case 2:{
            std::cout << "1.数学 2.语文 3.英语 4.平均分：";
            int button_3 = 0;
            std::cin >> button_3;
            print_section(button_3);
        }break;
        case 0:break;
    }
}

void Sgms::analyse_record()
{
    double math_average = 0,english_average = 0,physics_average = 0,average_average = 0;
    double math_dev = 0,english_dev = 0,physics_dev = 0,average_dev = 0;
    double math_qua = 0,english_qua = 0,physics_qua = 0,average_qua = 0;

    all_average(math_average,physics_average,english_average,average_average);
    standard_deviation(math_dev,physics_dev,english_dev,average_dev,
        math_average,physics_average,english_average,average_average);
    qualified_rate(math_qua,physics_qua,english_qua,average_qua);

    std::cout << "平均成绩：" << std::endl
            << "数学：" << std::setprecision(4) << std::setw(4) << math_average
            << " 物理：" << std::setprecision(4) << std::setw(4) << physics_average
            << " 英语：" << std::setprecision(4) << std::setw(4) << english_average
            << " 总体：" << std::setprecision(4) << std::setw(4) << average_average <<std::endl
            << "标准差：" << std::endl
            << "数学：" << std::setprecision(4) << std::setw(4) << math_dev
            << " 物理：" << std::setprecision(4) << std::setw(4) << physics_dev
            << " 英语：" << std::setprecision(4) << std::setw(4) << english_dev
            << " 总体：" << std::setprecision(4) << std::setw(4) << average_dev <<std::endl
            << "合格率：" << std::endl
            << "数学：" << std::setprecision(3) << std::setw(3) << math_qua << "%"
            << " 物理：" << std::setprecision(3) << std::setw(3) << physics_qua << "%"
            << " 英语：" << std::setprecision(3) << std::setw(3) << english_qua << "%"
            << " 总体：" << std::setprecision(3) << std::setw(3) << average_qua << "%" << std::endl;
}

void Sgms::sort_record()
{
    if(List.size() != 0){
        int i,j;Student T;
        for(i = 0;i < (int)List.size()-1;i++)
        {
            for(j = 0;j < (int)List.size()-1-i;j++)
            {
                if(List[j].get_average() < List[j+1].get_average()
                    && fabs(List[j].get_average()-List[j+1].get_average()) > 1E-6)
                {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                if(fabs(List[j].get_average()-List[j+1].get_average()) <= 1E-6)
                {
                    if(List[j].math < List[j+1].math
                        && fabs(List[j].math-List[j+1].math) > 1E-6)
                    {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                    if(fabs(List[j].math-List[j+1].math) <= 1E-6)
                    {
                        if(List[j].physics < List[j+1].physics
                            && fabs(List[j].physics-List[j+1].physics) > 1E-6)
                        {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                        if(fabs(List[j].physics-List[j+1].physics) <= 1E-6)
                        {
                            if(List[j].english < List[j+1].english
                                && fabs(List[j].english-List[j+1].english) > 1E-6)
                            {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                            if(fabs(List[j].english-List[j+1].english) <= 1E-6)
                            {
                                if(std::stoll(List[j].number) < std::stoll(List[j+1].number)
                                    && fabs(std::stoll(List[j].number)-std::stoll(List[j+1].number)) > 1E-6)
                                {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                            }
                        }
                    }
                }
            }
        }
        std::cout << "！排序成功！" << std::endl
                << "1.查看 0.返回:";
        int button_2 = 0;
        std::cin >> button_2;
        switch (button_2) {
            case 1:{
                for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
                {(*i).print_data();}
            }break;
            case 0:break;
        }
    }
}

void Sgms::file_record()
{
    std::cout << "1.读取文件 2.写入文件 0.返回：";
    int button_2 = 0;
    std::cin >> button_2;
    switch (button_2) {
        case 1:{
            std::ifstream ifile("Grade.txt");
            std::string temp_number,temp_name;
            double temp_math,temp_physics,temp_english;
            while(1)
            {
                if(ifile.eof())break;
                ifile >> temp_number >> temp_name >> temp_math >> temp_physics >> temp_english;
                Student temp_stu(temp_number,temp_name,temp_math,temp_physics,temp_english);
                List.push_back(temp_stu);
            }
            std::cout << "！读取成功！" << std::endl
                    << "1.查看 0.返回:";
            int button_3 = 0;
            std::cin >> button_3;
            switch (button_3) {
                case 1:{
                    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
                    {(*i).print_data();}
                }break;
                case 0:break;
            }
        }break;
        case 2:{
            std::ofstream ofile("Grade.txt");
            if (ofile.is_open())
            {
                for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
                {
                    ofile << std::endl
                        << (*i).number << " "
                        << (*i).name << " "
                        << (*i).math << " "
                        << (*i).physics << " "
                        << (*i).english;
                }
                ofile.close();
                std::cout << "！写入成功！" << std::endl;
            }
            else std::cout << "！文件无法打开！" << std::endl;
        }break;
        case 0:break;
    }
}


void Sgms::change_data(Student &temp_stu,int x)
{
    std::cout << "请输入修改后的内容：";
    switch (x) {
        case 1:temp_stu.math = double_cin();break;
        case 2:temp_stu.physics = double_cin();break;
        case 3:temp_stu.english = double_cin();break;
        case 4:temp_stu.number = string_cin();break;
        case 5:temp_stu.name = string_cin();break;
    }
    std::cout << "！修改成功！" << std::endl;
}

void Sgms::print_section(int x)
{
    std::cout << "请输入成绩分段的最低分与最高分：";
    double bottom = 0,top = 100;
    std::cin >> bottom >> top;
    std::cout << "查找的结果为：" << std::endl;
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        switch (x) {
            case 1:if((*i).math >= bottom && (*i).math <= top)(*i).print_data();break;
            case 2:if((*i).physics >= bottom && (*i).physics <= top)(*i).print_data();break;
            case 3:if((*i).english >= bottom && (*i).english <= top)(*i).print_data();break;
            case 4:if((*i).get_average() >= bottom && (*i).get_average() <= top)(*i).print_data();break;
        }
    }
}

void Sgms::all_average(
    double &math_average,double &physics_average,double &english_average,double &average_average)
{
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        math_average += (*i).math;
        physics_average += (*i).physics;
        english_average += (*i).english;
        average_average += (*i).get_average();
    }
    math_average /= List.size();
    physics_average /= List.size();
    english_average /= List.size();
    average_average /= List.size();
}

void Sgms::standard_deviation(
    double &math_dev,double &physics_dev,double &english_dev,double &average_dev,
    double math_average,double physics_average,double english_average,double average_average)
{
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        math_dev += ((*i).math - math_average)*((*i).math - math_average);
        physics_dev += ((*i).physics - physics_average)*((*i).physics - physics_average);
        english_dev += ((*i).english - english_average)*((*i).english - english_average);
        average_dev += ((*i).get_average() - average_average)*((*i).get_average() - average_average);
    }
    math_dev = sqrt(math_dev/List.size());
    physics_dev = sqrt(physics_dev/List.size());
    english_dev = sqrt(english_dev/List.size());
    average_dev = sqrt(average_dev/List.size());
}

void Sgms::qualified_rate(
    double &math_qua,double &physics_qua,double &english_qua,double &average_qua)
{
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        if((*i).math >= 60)math_qua += 1;
        if((*i).physics >= 60)physics_qua += 1;
        if((*i).english >= 60)english_qua += 1;
        if((*i).get_average() >= 60)average_qua += 1;
    }
    math_qua = (math_qua/List.size())*100;
    physics_qua = (physics_qua/List.size())*100;
    english_qua = (english_qua/List.size())*100;
    average_qua = (average_qua/List.size())*100;
}
