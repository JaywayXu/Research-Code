#include <string>

#ifndef Student__
#define Student__

class Student
{
public:
    std::string number;
    std::string name;
    double math,physics,english;

public:
    Student();
    Student(std::string,std::string,double,double,double);
    void print_data();
    double get_average(){return (math+physics+english)/(3.0);}
};

#endif
