#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;

struct name {
	char *firstName;
	char *lastName;
};

struct student {
	name na;
	double grade[3];
	double average;
};

void input(student **students, int len) {
	student *s = *students;
	cout << "分别输入每个学生的：名 姓 三门分数：" << endl;
	for (int i = 0; i < len; i++) {
		cin >> s[i].na.firstName >> s[i].na.lastName;
		for (int j = 0; j < 3; j++) {
			cin >> s[i].grade[j];
		}
	}
}

void aver(student **students, int len) {
	student *s = *students;
	double *ave = (double *)malloc(sizeof(double) * len);
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < 3; j++) {
			ave[i] += s[i].grade[j];
		}
		ave[i] /= 3.0;
		s[i].average = ave[i];
	}
}

void outputName(name na) {
	cout << na.firstName << na.lastName << endl;
}

void output(student **students, int len) {
	student *s = *students;
	for (int i = 0; i < len; i++) {
		cout << "姓名: ";
		outputName(s[i].na);
		cout << "各科分数: ";
		for (int j = 0; j < 3; j++) {
			cout << s[i].grade[j] << " ";
		}
		cout << endl
			 << "平均分: " << s[i].average << endl << endl;
	}
}

int main() {
	int stu_num;
	cout << "输入学生数量: ";
	cin >> stu_num;

	student *students = (student *)malloc(sizeof(student) * stu_num);
	for (int i = 0; i < stu_num; i++) {
		students[i].na.firstName = (char *)malloc(sizeof(char) * 50);
		students[i].na.lastName = (char *)malloc(sizeof(char) * 50);
		//strcpy(students[i].na.firstName, "aa");
		//strcpy(students[i].na.lastName, "a");
	}

	input(&students, stu_num);
	aver(&students, stu_num);
	cout << "student: " << endl;
	output(&students, stu_num);
	
	double class_ave = 0;
	for (int i = 0; i < stu_num; i++) {
		class_ave += students[i].average;
	}
	class_ave /= stu_num;
	cout << "班级平均分: " << class_ave << endl;
	return 0;
}