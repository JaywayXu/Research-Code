#include <iostream>
#include <vector>
#include <string>
#include "Student.h"

#ifndef Sgms__
#define Sgms__

//管理系统类
class Sgms
{
private:
    std::vector<Student> List;

public:
    void run();

    //菜单函数
    void add_record();
    void delete_record();
    void change_record();
    void search_record();
    void analyse_record();
    void sort_record();
    void file_record();
 
    //辅助函数
    void change_data(Student &,int);
    void print_section(int);
    void all_average(double &,double &,double &,double &);
    void standard_deviation(
        double &,double &,double &,double &,
        double,double,double,double);
    void qualified_rate(double &,double &,double &,double &);
    double double_cin(){double temp;std::cin >> temp;return temp;}
    std::string string_cin(){std::string temp;std::cin >> temp;return temp;}
};

#endif
