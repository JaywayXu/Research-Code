#include<iostream>
#include<string>

class Person
{
private:
    int number;
    std::string name;
public:
    Person();
    ~Person();
};

Person::Person()
{
    std::cout<<"构造Person"<<std::endl;
}

Person::~Person()
{
    std::cout<<"析构Person"<<std::endl;
}

class A
{
private:
    int number;
    std::string name;
public:
    A();
    ~A();
};

A::A()
{
    std::cout<<"构造A"<<std::endl;
}

A::~A()
{
    std::cout<<"析构A"<<std::endl;
}

class Student:public Person
{
public:
    Student();
    ~Student();
};

Student::Student()
{
    std::cout<<"构造Student"<<std::endl;
}

Student::~Student()
{
    std::cout<<"析构Student"<<std::endl;
}

class Teacher:virtual A
{
public:
    Teacher();
    ~Teacher();
};

Teacher::Teacher()
{
    std::cout<<"构造Teacher"<<std::endl;
}

Teacher::~Teacher()
{
    std::cout<<"析构Teacher"<<std::endl;
}

class Me:public Teacher,virtual public Student
{
public:
    Me();
    ~Me();
};

Me::Me()
{
    std::cout<<"构造Me"<<std::endl;
}

Me::~Me()
{
    std::cout<<"析构Me"<<std::endl;
}
