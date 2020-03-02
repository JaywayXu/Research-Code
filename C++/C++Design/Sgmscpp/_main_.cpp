/*
 名称: 学生成绩管理系统
 作�?: 李延�?
 功能: 通过学生成绩的录入、删除、查找、修改�?
       成绩的统计分析，实现对学生成绩的管理
 版本: V4.0
     (v1.0 2018/1/15:框架 以及 1.录入 2.删除 3.修改 4.查询成绩 功能)
     (v2.0 2018/1/16:增加 5.成绩统计分析 6.成绩高低排序 功能；修�? 一些类型引起的错误)
     (v3.0 2018/1/17:增加 7.文件操作 功能)
     (.0 2018/1/18:增加 模糊搜索 功能；优�? 前面的功�?)
 时间: 2018/1/18
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::string;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                             类模�?                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////////

//学生�?
class _Student
{
	long long _school_number; //学号
	string _name;			  //姓名
	double _math;			  //数学成绩
	double _physics;		  //物理成绩
	double _english;		  //英语成绩

  public:
	_Student();
	void _school_number_(long long a) { _school_number = a; }
	void _name_(string a) { _name = a; }
	void _math_(double a) { _math = a; }
	void _physics_(double a) { _physics = a; }
	void _english_(double a) { _english = a; }
	void _cin();
	void _cin_school_number() { cin >> _school_number; }
	void _cin_name() { cin >> _name; }
	void _cin_math() { cin >> _math; }
	void _cin_physics() { cin >> _physics; }
	void _cin_english() { cin >> _english; }
	long long _get_school_number() { return _school_number; }
	string _get_name() { return _name; }
	double _get_math() { return _math; }
	double _get_physics() { return _physics; }
	double _get_english() { return _english; }
	double _get_average() { return (_math + _physics + _english) / 3.0; }
	void _delet();
	void _cout();
};

//构造函�?
_Student::_Student()
{
	_school_number = 0;
	;
	_name = '0';
	_math = 0;
	_physics = 0;
	_english = 0;
}

//输入数据成员函数
void _Student::_cin()
{
	cout << "请分别输入学生的:" << endl
		 << "学号、姓名、数学成绩、物理成绩、英语成绩：" << endl
		 << "若不想录入则全输�?0" << endl
		 << "----------------------------------------" << endl;
	_cin_school_number();
	_cin_name();
	_cin_math();
	_cin_physics();
	_cin_english();
	cout << "------------你已创建该条记录------------" << endl;
}

//输出数据成员函数
void _Student::_cout()
{
	cout << "学号�?" << setw(12) << _school_number
		 << "  姓名�?" << setw(8) << _name
		 << "  数学成绩�?" << setw(3) << _math
		 << "  物理成绩�?" << setw(3) << _physics
		 << "  英语成绩�?" << setw(3) << _english
		 << "  总分�?" << setw(4) << _get_average() * 3.0
		 << endl;
}

//删除数据成员函数
void _Student::_delet()
{
	_school_number = 0;
	;
	_name = '0';
	_math = 0;
	_physics = 0;
	_english = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                            主体模块                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////////

//平均值函�?
double average(_Student _stu[], const int n, const int x)
{
	//数学
	if (x == 1)
	{
		for (int j = 0;; j++)
		{
			static double sum = 0.0;
			static double num = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				sum += _stu[j]._get_math();
				num += 1.0;
			}
			if (j == n - 1)
			{
				return sum / num;
			}
		}
	}
	//物理
	if (x == 2)
	{
		for (int j = 0;; j++)
		{
			static double sum = 0.0;
			static double num = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				sum += _stu[j]._get_physics();
				num += 1.0;
			}
			if (j == n - 1)
			{
				return sum / num;
			}
		}
	}
	//英语
	if (x == 3)
	{
		for (int j = 0;; j++)
		{
			static double sum = 0.0;
			static double num = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				sum += _stu[j]._get_english();
				num += 1.0;
			}
			if (j == n - 1)
			{
				return sum / num;
			}
		}
	}
	//总体
	if (x == 0)
	{
		for (int j = 0;; j++)
		{
			static double sum = 0.0;
			static double num = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				sum += _stu[j]._get_average();
				num += 1.0;
			}
			if (j == n - 1)
			{
				return sum / num;
			}
		}
	}
	else
		return 0;
}

//标准差函�?
double biaozhuncha(_Student _stu[], const int n, const int x)
{
	//数学
	if (x == 1)
	{
		for (int j = 0;; j++)
		{
			static double cha = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				cha += (_stu[j]._get_math() - average(_stu, n, x)) * (_stu[j]._get_math() - average(_stu, n, x));
			}
			if (j == n - 1)
			{
				return sqrt(cha);
			}
		}
	}
	//物理
	if (x == 2)
	{
		for (int j = 0;; j++)
		{
			static double cha = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				cha += (_stu[j]._get_physics() - average(_stu, n, x)) * (_stu[j]._get_physics() - average(_stu, n, x));
			}
			if (j == n - 1)
			{
				return sqrt(cha);
			}
		}
	}
	//英语
	if (x == 3)
	{
		for (int j = 0;; j++)
		{
			static double cha = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				cha += (_stu[j]._get_english() - average(_stu, n, x)) * (_stu[j]._get_english() - average(_stu, n, x));
			}
			if (j == n - 1)
			{
				return sqrt(cha);
			}
		}
	}
	//总体
	if (x == 0)
	{
		for (int j = 0;; j++)
		{
			static double cha = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				cha += (_stu[j]._get_average() - average(_stu, n, x)) * (_stu[j]._get_average() - average(_stu, n, x));
			}
			if (j == n - 1)
			{
				return sqrt(cha);
			}
		}
	}
	else
		return 0;
}

//合格率函�?
double hegelv(_Student _stu[], const int n, const int x)
{
	//数学
	if (x == 1)
	{
		for (int j = 0;; j++)
		{
			static double fenzi = 0.0;
			static double fenmu = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				if (_stu[j]._get_math() > 60.0 || fabs(_stu[j]._get_math() - 60.0) <= 1E-6)
				{
					fenzi++;
				}
				fenmu += 1.0;
			}
			if (j == n - 1)
			{
				return fenzi / fenmu;
			}
		}
	}
	//物理
	if (x == 2)
	{
		for (int j = 0;; j++)
		{
			static double fenzi = 0.0;
			static double fenmu = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				if (_stu[j]._get_physics() > 60.0 || fabs(_stu[j]._get_physics() - 60.0) <= 1E-6)
				{
					fenzi++;
				}
				fenmu += 1.0;
			}
			if (j == n - 1)
			{
				return fenzi / fenmu;
			}
		}
	}
	//英语
	if (x == 3)
	{
		for (int j = 0;; j++)
		{
			static double fenzi = 0.0;
			static double fenmu = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				if (_stu[j]._get_english() > 60.0 || fabs(_stu[j]._get_english() - 60.0) <= 1E-6)
				{
					fenzi++;
				}
				fenmu += 1.0;
			}
			if (j == n - 1)
			{
				return fenzi / fenmu;
			}
		}
	}
	//总体
	if (x == 0)
	{
		for (int j = 0;; j++)
		{
			static double fenzi = 0.0;
			static double fenmu = 0.0;
			if (_stu[j]._get_school_number() != 0)
			{
				if (_stu[j]._get_average() > 60.0 || fabs(_stu[j]._get_average() - 60.0) <= 1E-6)
				{
					fenzi++;
				}
				fenmu += 1.0;
			}
			if (j == n - 1)
			{
				return fenzi / fenmu;
			}
		}
	}
	else
		return 0;
}

//模糊查找函数
string _find(string s, string a)
{
	if (s.find(a) != string::npos)
	{
		return s;
	}
	return a;
}

//主函�?
int main()
{
	const int N = 200;
	_Student _stu[N]; //创建一个对象数�?
	int _num;
	int _a;
	int _b;
	string paus;
	long long _school_num;
	double _low;
	double _high;
	string _name;

manu: //菜单
	cout
		<< "----------------------------------------" << endl
		<< "#############   功能菜单   #############" << endl
		<< "----------------------------------------" << endl
		<< "            1. 录入学生记录              " << endl
		<< "            2. 删除学生记录              " << endl
		<< "            3. 修改学生记录              " << endl
		<< "            4. 查找学生记录              " << endl
		<< "            5. 成绩统计分析              " << endl
		<< "            6. 成绩高低排序              " << endl
		<< "            7. 成绩文件操作              " << endl
		<< "            0. 退出程�?                  " << endl
		<< "----------------------------------------" << endl
		<< "请输入你要使用的功能编号: ";
	cin >> _num;
	cout
		<< "----------------------------------------" << endl;

	//录入学生记录
	if (_num == 1)
	{
		for (int i = 0; i < N; i++)
		{
			if (_stu[i]._get_school_number() == 0)
			{
				_stu[i]._cin();
				cout
					<< "输入1继续录入，输入其他则退回菜单：";
				cin >> _a;
				cout
					<< "----------------------------------------" << endl;
				if (_a != 1)
					goto manu;
			}
		}
	}

	//删除学生记录
	if (_num == 2)
	{
		cout << "项目�? 1.学号  2.姓名 " << endl
			 << "请输入你要删除记录的查找信息项目�?";
		cin >> _a;
		cout << "----------------------------------------" << endl;
		//1.学号
		if (_a == 1)
		{
			cout << "请输入要删除记录的学生学号：";
			cin >> _school_num;
			cout << "----------------------------------------" << endl;
			for (int j = 0; j < N; j++)
			{
				if (_school_num == _stu[j]._get_school_number())
				{
					_stu[j]._cout();
					cout << "确认删除请输�?1，取消请输入0�?";
					cin >> _b;
					cout << "----------------------------------------" << endl;
					if (_b == 1)
					{
						_stu[j]._delet();
						cout << "!!!删除学号�?" << _school_num << "的学生信息成�?!!!" << endl
							 << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
					else
						goto manu;
				}
			}
			cout << "!!!你输入的学号没有在记录中!!!" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//2.姓名
		if (_a == 2)
		{
			cout << "请输入要删除记录的学生姓名：";
			cin >> _name;
			cout << "----------------------------------------" << endl;
			for (int j = 0; j < N; j++)
			{
				if (_name == _stu[j]._get_name())
				{
					_stu[j]._cout();
					cout << "确认删除请输�?1，取消请输入0�?";
					cin >> _b;
					cout << "----------------------------------------" << endl;
					if (_b == 1)
					{
						_stu[j]._delet();
						cout << "!!!删除姓名�?" << _name << "的学生信息成�?!!!" << endl
							 << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
					else
						goto manu;
				}
			}
			cout << "!!!你输入的姓名没有在记录中!!!" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//输入错误
		if (_a != 2 && _a != 1)
		{
			cout << "！！！输入错误！！！" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
	}

	//修改学生记录
	if (_num == 3)
	{
		cout << "项目�? 1.学号  2.姓名 " << endl
			 << "请输入你要修改记录的查找信息项目�?";
		cin >> _a;
		cout << "----------------------------------------" << endl;
		//1.学号
		if (_a == 1)
		{
			cout << "请输入要修改记录的学生学号：";
			cin >> _school_num;
			cout << "----------------------------------------" << endl;
			for (int j = 0; j < N; j++)
			{
				if (_school_num == _stu[j]._get_school_number())
				{
					_stu[j]._cout();
					cout << "项目�? 1.姓名  2.成绩   " << endl
						 << "输入你要修改的项目序�?: ";
					cin >> _b;
					cout << "----------------------------------------" << endl;
					//1.姓名
					if (_b == 1)
					{
						cout << "请输入修改后的姓名： ";
						_stu[j]._cin_name();
						cout << "----------------------------------------" << endl;
						cout << "!!!学号�? " << _school_num << " 的学生姓名信息修改成�?!!!" << endl
							 << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
					//2.成绩
					if (_b == 2)
					{
						cout << "请输入修改后的内�? " << endl;
						cout << "数学成绩: ";
						_stu[j]._cin_math();
						cout << "物理成绩�?";
						_stu[j]._cin_physics();
						cout << "英语成绩: ";
						_stu[j]._cin_english();
						cout << "----------------------------------------" << endl;
						cout << "!!!学号�? " << _school_num << " 的学生成绩信息修改成�?!!!" << endl
							 << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
					//输入错误
					if (_b != 2 && _b != 1)
					{
						cout << "！！！输入错误！！！" << endl;
						cout << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
				}
			}
			cout << "!!!你输入的学号没有在记录中!!!" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//2.姓名
		if (_a == 2)
		{
			cout << "请输入要修改记录的学生姓名：";
			cin >> _name;
			cout << "----------------------------------------" << endl;
			for (int j = 0; j < N; j++)
			{
				if (_name == _stu[j]._get_name())
				{
					_stu[j]._cout();
					cout << "项目�? 1.学号  2.成绩   " << endl
						 << "输入你要修改的项目序�?: ";
					cin >> _b;
					cout << "----------------------------------------" << endl;
					//1.姓名
					if (_b == 1)
					{
						cout << "请输入修改后的学号： ";
						_stu[j]._cin_school_number();
						cout << "----------------------------------------" << endl;
						cout << "!!!姓名�? " << _name << " 的学生学号信息修改成�?!!!" << endl
							 << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
					//2.成绩
					if (_b == 2)
					{
						cout << "请输入修改后的内�? " << endl;
						cout << "数学成绩: ";
						_stu[j]._cin_math();
						cout << "物理成绩�?";
						_stu[j]._cin_physics();
						cout << "英语成绩: ";
						_stu[j]._cin_english();
						cout << "----------------------------------------" << endl;
						cout << "!!!姓名�? " << _name << " 的学生成绩信息修改成�?!!!" << endl
							 << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
					//输入错误
					if (_b != 2 && _b != 1)
					{
						cout << "！！！输入错误！！！" << endl;
						cout << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
				}
			}
			cout << "!!!你输入的学号没有在记录中!!!" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//输入错误
		if (_a != 2 && _a != 1)
		{
			cout << "！！！输入错误！！！" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
	}

	//查找学生记录
	if (_num == 4)
	{
		cout << "项目�? 1.学生成绩  2.分段名单 " << endl
			 << "输入你要选择的项目序�?: ";
		cin >> _a;
		cout << "----------------------------------------" << endl;
		//1.学生成绩
		if (_a == 1)
		{
			cout << "类型�?1.学号  2.姓名 3.姓名模糊查找" << endl
				 << "请输入你要查找的类型序号�?";
			cin >> _b;
			cout << "----------------------------------------" << endl;
			//1.学号
			if (_b == 1)
			{
				cout << "请输入要查找的学生学号：";
				cin >> _school_num;
				cout << "----------------------------------------" << endl;
				for (int j = 0; j < N; j++)
				{
					if (_school_num == _stu[j]._get_school_number())
					{
						cout << "学号�? " << _school_num << " 的学生信息是�?" << endl;
						_stu[j]._cout();
						cout << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
				}
			}
			//2.姓名
			if (_b == 2)
			{
				cout << "请输入要查找的学生姓名：";
				cin >> _name;
				cout << "----------------------------------------" << endl;
				for (int j = 0; j < N; j++)
				{
					if (_name == _stu[j]._get_name())
					{
						cout << "姓名�? " << _name << " 的学生信息是�?" << endl;
						_stu[j]._cout();
						cout << "----------------------------------------" << endl;
						cout << "输入任意继续";
						cin >> paus;
						goto manu;
					}
				}
			}
			//3.姓名模糊查找
			if (_b == 3)
			{
				cout << "请输入要查找的学生姓名关键字�?";
				cin >> _name;
				cout << "----------------------------------------" << endl;
				cout << "关键字为 " << _name << " 的所有学生信息是�?" << endl;
				for (int j = 0; j < N; j++)
				{
					if (_find(_stu[j]._get_name(), _name) == _stu[j]._get_name())
					{
						_stu[j]._cout();
					}
				}
				cout << "----------------------------------------" << endl;
				cout << "输入任意继续";
				cin >> paus;
				goto manu;
			}
			//输入错误
			if (_b != 2 && _b != 1)
			{
				cout << "！！！输入错误！！！" << endl;
				cout << "----------------------------------------" << endl;
				cout << "输入任意继续";
				cin >> paus;
				goto manu;
			}
			cout << "!!!没有该同学信�?!!!" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//2.分段名单
		if (_a == 2)
		{
			cout << "科目�?1.数学  2.物理  3.英语" << endl
				 << "请输入你要查询的科目序号�?";
			cin >> _b;
			cout << "----------------------------------------" << endl;
			//1.数学
			if (_b == 1)
			{
				cout << "请输入成绩分段的最低分与最高分" << endl
					 << "最低分�?";
				cin >> _low;
				cout << "最高分�?";
				cin >> _high;
				cout << "----------------------------------------" << endl;
				for (int j = 0; j < N; j++)
				{
					if (_stu[j]._get_math() >= _low && _stu[j]._get_math() <= _high)
						cout << "姓名�?" << setw(8) << _stu[j]._get_name() << "         "
							 << "数学成绩�?" << setw(6) << _stu[j]._get_math() << endl;
				}
			}
			//2.物理
			if (_b == 2)
			{
				cout << "请输入成绩分段的最低分与最高分" << endl
					 << "最低分�?";
				cin >> _low;
				cout << "最高分�?";
				cin >> _high;
				cout << "----------------------------------------" << endl;
				for (int j = 0; j < N; j++)
				{
					if (_stu[j]._get_physics() >= _low && _stu[j]._get_physics() <= _high)
						cout << "姓名�?" << setw(8) << _stu[j]._get_name() << "         "
							 << "物理成绩�?" << setw(6) << _stu[j]._get_physics() << endl;
				}
			}
			//3.英语
			if (_b == 3)
			{
				cout << "请输入成绩分段的最低分与最高分" << endl
					 << "最低分�?";
				cin >> _low;
				cout << "最高分�?";
				cin >> _high;
				cout << "----------------------------------------" << endl;
				for (int j = 0; j < N; j++)
				{
					if (_stu[j]._get_english() >= _low && _stu[j]._get_english() <= _high)
						cout << "姓名�?" << setw(8) << _stu[j]._get_name() << "         "
							 << "英语成绩�?" << setw(6) << _stu[j]._get_english() << endl;
				}
			}
			//输入错误
			if (_b != 2 && _b != 1 && _b != 3)
			{
				cout << "！！！输入错误！！！" << endl;
				cout << "----------------------------------------" << endl;
				cout << "输入任意继续";
				cin >> paus;
				goto manu;
			}
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//输入错误
		if (_a != 2 && _a != 1)
		{
			cout << "！！！输入错误！！！" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
	}

	//成绩统计分析
	if (_num == 5)
	{
		cout << "类型�?1.数学 2.物理 3.英语 4.总体 " << endl
			 << "请输入你要查找的类型序号�?";
		cin >> _a;
		cout << "----------------------------------------" << endl;
		//数学
		if (_a == 1)
		{
			cout << "平均数学成绩为：" << setw(5) << average(_stu, N, 1) << endl
				 << "标准差为�?" << setw(8) << biaozhuncha(_stu, N, 1) << endl
				 << "合格率为�?" << setw(6) << hegelv(_stu, N, 1) * 100.0 << " %" << endl
				 << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//物理
		if (_a == 2)
		{
			cout << "平均物理成绩为：" << setw(5) << average(_stu, N, 2) << endl
				 << "标准差为�?" << setw(8) << biaozhuncha(_stu, N, 2) << endl
				 << "合格率为�?" << setw(6) << hegelv(_stu, N, 2) * 100.0 << " %" << endl
				 << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//英语
		if (_a == 3)
		{
			cout << "平均英语成绩为：" << setw(5) << average(_stu, N, 3) << endl
				 << "标准差为�?" << setw(8) << biaozhuncha(_stu, N, 3) << endl
				 << "合格率为�?" << setw(6) << hegelv(_stu, N, 3) * 100.0 << " %" << endl
				 << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//总体
		if (_a == 4)
		{
			cout << "平均总体成绩为：" << setw(5) << average(_stu, N, 0) << endl
				 << "标准差为�?" << setw(8) << biaozhuncha(_stu, N, 0) << endl
				 << "合格率为�?" << setw(6) << hegelv(_stu, N, 0) * 100.0 << " %" << endl
				 << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//输入错误
		if (_a != 1 && _a != 2 && _a != 3 && _a != 4)
		{
			cout << "！！！输入错误！！！" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
	}

	//成绩高低排序
	if (_num == 6) //用了双浮点值的精确比较
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N - j - 1; k++)
			{
				if (_stu[k]._get_average() < _stu[k + 1]._get_average() && fabs(_stu[k]._get_average() - _stu[k + 1]._get_average()) >= 1E-6)
				{
					_Student temp = _stu[k];
					_stu[k] = _stu[k + 1];
					_stu[k + 1] = temp;
				}
				if (fabs(_stu[k]._get_average() - _stu[k + 1]._get_average()) <= 1E-6)
				{
					if (_stu[k]._get_math() < _stu[k + 1]._get_math() && fabs(_stu[k]._get_math() - _stu[k + 1]._get_math()) >= 1E-6)
					{
						_Student temp = _stu[k];
						_stu[k] = _stu[k + 1];
						_stu[k + 1] = temp;
					}
					if (fabs(_stu[k]._get_math() - _stu[k + 1]._get_math()) <= 1E-6)
					{
						if (_stu[k]._get_physics() < _stu[k + 1]._get_physics() && fabs(_stu[k]._get_physics() - _stu[k + 1]._get_physics()) >= 1E-6)
						{
							_Student temp = _stu[k];
							_stu[k] = _stu[k + 1];
							_stu[k + 1] = temp;
						}
						if (fabs(_stu[k]._get_physics() - _stu[k + 1]._get_physics()) <= 1E-6)
						{
							if (_stu[k]._get_english() < _stu[k + 1]._get_english() && fabs(_stu[k]._get_english() - _stu[k + 1]._get_english()) >= 1E-6)
							{
								_Student temp = _stu[k];
								_stu[k] = _stu[k + 1];
								_stu[k + 1] = temp;
							}
							if (fabs(_stu[k]._get_english() - _stu[k + 1]._get_english()) <= 1E-6)
							{
								if (_stu[k]._get_school_number() < _stu[k + 1]._get_school_number())
								{
									_Student temp = _stu[k];
									_stu[k] = _stu[k + 1];
									_stu[k + 1] = temp;
								}
							}
						}
					}
				}
			}
		}
		for (int j = 0; j < N; j++) //显示在屏幕上
		{
			if (_stu[j]._get_school_number() != 0)
			{
				_stu[j]._cout();
			}
		}
		cout << "----------------------------------------" << endl;
		cout << "输入任意继续";
		cin >> paus;
		goto manu;
	}

	//成绩文件操作
	if (_num == 7)
	{
		cout << "项目�? 1.读取文件  2.写入文件 " << endl
			 << "输入你要选择的项目序�?: ";
		cin >> _a;
		cout << "----------------------------------------" << endl;
		//读取文件
		if (_a == 1)
		{
			ifstream ifile("Grade.txt");
			for (int j = 0; j < N; j++)
			{
				if (_stu[j]._get_school_number() == 0)
				{
					if (ifile.eof())
					{
						break;
					}
					long long a;
					string b;
					double c, d, e;
					ifile >> a >> b >> c >> d >> e;
					_stu[j]._school_number_(a);
					_stu[j]._name_(b);
					_stu[j]._math_(c);
					_stu[j]._physics_(d);
					_stu[j]._english_(e);
				}
			}
			ifile.close();
			cout << "！！！读取文件成功！！！" << endl
				 << "----------------------------------------" << endl;
			cout << "输入1显示现在储存的所有内容，输入其他返回菜单:";
			cin >> _b;
			cout << "----------------------------------------" << endl;
			//显示内容
			if (_b == 1)
			{
				for (int j = 0; j < N; j++)
				{
					if (_stu[j]._get_school_number() != 0)
					{
						_stu[j]._cout();
					}
				}
				cout << "----------------------------------------" << endl;
				cout << "输入任意继续";
				cin >> paus;
				goto manu;
			}
			//返回菜单
			else
				goto manu;
		}
		//写入文件
		if (_a == 2)
		{
			ofstream ofile("Grade.txt");
			if (ofile.is_open())
			{
				for (int j = 0; j < N; j++)
				{
					if (_stu[j]._get_school_number() != 0)
					{
						ofile << endl
							  << _stu[j]._get_school_number() << " "
							  << _stu[j]._get_name() << " "
							  << _stu[j]._get_math() << " "
							  << _stu[j]._get_physics() << " "
							  << _stu[j]._get_english();
					}
				}
				ofile.close();
				cout << "！！！写入文件成功！！！" << endl;
				cout << "----------------------------------------" << endl;
			}
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
		//输入错误
		if (_a != 2 && _a != 1)
		{
			cout << "！！！输入错误！！！" << endl;
			cout << "----------------------------------------" << endl;
			cout << "输入任意继续";
			cin >> paus;
			goto manu;
		}
	}

	//退出程�?
	if (_num == 0)
		;

	//输入错误
	else
	{
		cout << "！！！输入错误！！！" << endl;
		cout << "----------------------------------------" << endl;
		cout << "输入任意继续";
		cin >> paus;
		goto manu;
	}

	return 0;
}
