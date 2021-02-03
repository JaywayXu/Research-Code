#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#ifndef SGMS_ONCE_  
#define SGMS_ONCE_ 

class Student
{
friend class CSGMS_MFCDlg;
friend class ADD;
friend class Change;
friend class Del;
friend class Search;
friend class SORT;

private:
    std::string number;
    std::string name;
    double math,physics,english;

public:
    inline Student();
    inline Student(std::string,std::string,double,double,double);
    inline double get_average(){return (math+physics+english)/(3.0);}
    inline std::string getstr();
};

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

std::string Student::getstr()
{
    std::ostringstream ostr;
    ostr << std::left << std::setw(11) << number << " "
        << std::left << std::setw(10) <<name << " "
        << std::left << std::setprecision(3) << std::setw(5) << math << " "
        << std::left << std::setprecision(3) << std::setw(5) << physics <<" "
        << std::left << std::setprecision(3) << std::setw(5) << english;
    std::string temp_str = ostr.str();
    return temp_str;
}

#endif
