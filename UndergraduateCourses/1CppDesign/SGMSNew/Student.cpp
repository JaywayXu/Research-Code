#include <iostream>
#include <string>
#include <iomanip>
#include "Student.h"

Student::Student()
{
    number = "none";
    name = "none";
    math = 0;
    physics = 0;
    english = 0;
}

Student::Student(
    std::string number,
    std::string name,
    double math,
    double physics,
    double english)
{
    this->number = number;
    this->name = name;
    this->math = math;
    this->physics = physics;
    this->english = english;
}

void Student::print_data()
{
    std::cout <<
    "学号：" << std::setw(11) << number <<
    " 姓名：" << std::setw(6) << name <<
    " 数学：" << std::setprecision(3) << std::setw(3) << math <<
    " 物理：" << std::setprecision(3) << std::setw(3) << physics <<
    " 英语：" << std::setprecision(3) << std::setw(3) << english <<
    " 平均：" << std::setprecision(3) << std::setw(3) << get_average() << std::endl;
}
