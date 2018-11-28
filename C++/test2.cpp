#include <iostream>

class Student
{
private:
    std::string name;
    double math;
    double english;

public:
    Student();
    Student(std::string, double, double);
    void show();
};

Student::Student()
{
    name = "null";
    math = 0;
    english = 0;
}

Student::Student(std::string xname, double xmath, double xenglish)
{
    name = xname;
    math = xmath;
    english = xenglish;
}

void Student::show()
{
    std::cout << name << " "
            << math << " "
            << english << std::endl;
}

int main()
{
    Student Pang("pcx", 100, 100);
    Pang.show();

    Student X;
    X.show();

    return 0;
}