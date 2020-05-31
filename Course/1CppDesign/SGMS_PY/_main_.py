'''
项目名称：学生成绩管理系统(pytnon版)
作者：李延炽
时间：2018/1/27
版本：v3.0
版本特性：
v1.0 (实现4个功能)
v2.0 (实现6个功能)
v3.0 (实现7个功能)
'''

import math


#学生类
class Student:
	_name = '0'
	_number = '0'
	_math = '0'
	_physics = '0'
	_english = '0'

	#构造函数
	def __init__(self, a='0', b='0', c='0', d='0', e='0'):
		self._name = a
		self._number = b
		self._math = c
		self._physics = d
		self._english = e

	#平均成绩
	def _average_(self):
		return (float(self._math) + float(self._physics) + float(self._english))/3.0

	#打印成绩
	def _print_(self):
		print("姓名：%-6s"%self._name," 学号：%-11s"%self._number," 数学：%-4s"%self._math," 物理：%-4s"%self._physics," 英语：%-4s"%self._english,"总分:%-5.0f"%(float(self._math) + float(self._physics) + float(self._english)))


#暂停
def _pause_():
	input("Press any key to continue...")
	print("")


#平均成绩
def _average_(stu, a):
	x = 0
	sum = 0.0
	while x < len(stu):
		if a == 0:
			b = stu[x]._average_()
		elif a == 1:
			b = stu[x]._math
		elif a == 2:
			b = stu[x]._physics
		elif a == 3:
			b = stu[x]._english
		else:
			print("\n！！！输入错误！！！\n")
			_pause_()
		sum += float(b)
		x += 1
	average = sum / x
	return average


#标准差
def _biaozhuncha_(stu, a):
	x = 0
	fc = 0.0
	while x < len(stu):
		if a == 0:
			b = stu[x]._average_()
			c = _average_(stu,0)
		elif a == 1:
			b = stu[x]._math
			c = _average_(stu,1)
		elif a == 2:
			b = stu[x]._physics
			c = _average_(stu,2)
		elif a == 3:
			b = stu[x]._english
			c = _average_(stu,3)
		else:
			print("\n！！！输入错误！！！\n")
			_pause_()
		fc += (float(b) - float(c))*(float(b) - float(c))
		x += 1
	return math.sqrt(fc / x)

#合格率
def _hegelv_(stu,a):
	x = 0
	y = 0
	while x < len(stu):
		if a == 0:
			b = stu[x]._average_()
		elif a == 1:
			b = stu[x]._math
		elif a == 2:
			b = stu[x]._physics
		elif a == 3:
			b = stu[x]._english
		else:
			print("\n！！！输入错误！！！\n")
			_pause_()
		if float(b) >= 60:
			y += 1
		x += 1
	return (y / x)*100

#增加记录
def _add_(stu):
	while True:
		stu.append(Student(input("姓名："),input("学号："),input("数学成绩："),input("物理成绩："),input("英语成绩：")))
		print("\n录入学生信息成功！\n" )
		if input("输入1继续录入，否则返回菜单：") != '1':
			print("\n")
			break
		else:
			print("\n")

#删除记录
def _delete_(stu):
	print("1.学号      2.姓名")
	a = input("请输入要查找删除的项目序号：")
	if a == '1':
		number = input("\n请输入学号：")
		x = 0
		while x < len(stu):
			if stu[x]._number == number:
				b = input("\n请确认是否删除，确认请输入1，否则取消：")
				if b == '1':
					del stu[x]
					print("\n删除成功！\n")
					_pause_()
					break
				else:
					print("\n取消成功！\n")
					_pause_()
					break
			x += 1
			if x == len(stu):
				print("\n！！！未找到该条记录！！！\n")
				_pause_()
	elif a == '2':
		name = input("\n请输入姓名：")
		x = 0
		while x < len(stu) :
			if stu[x]._name == name:
				b = input("\n请确认是否删除，确认请输入1，否则取消：")
				if b == '1':
					del stu[x]
					print("\n删除成功！\n")
					_pause_()
					break
				else:
					print("\n取消成功！\n")
					_pause_()
					break
			x += 1
			if x == len(stu):
				print("\n！！！未找到该条记录！！！\n")
				_pause_()
	else:
		print("\n！！！输入错误！！！\n")
		_pause_()

#修改记录
def _change_(stu):
	print("1.学号      2.姓名")
	a = input("请输入要查找修改的项目序号：")
	if a == '1':
		number = input("\n请输入学号：")
		x = 0
		while x < len(stu) :
			if stu[x]._number == number:
				print("\n1.姓名 2.数学成绩 3.物理成绩 4.英语成绩")
				b = input("请输入要修改的项目序号：")
				if b == '1':
					stu[x]._name = input("\n请输入修改后的姓名：")
					print("\n修改成功！\n")
					_pause_()
					break
				elif b == '2':
					stu[x]._math = input("\n请输入修改后的数学成绩：")
					print("\n修改成功！\n")
					_pause_()
					break
				elif b == '3':
					stu[x]._physics = input("\n请输入修改后的物理成绩：")
					print("\n修改成功！\n")
					_pause_()
					break
				elif b == '4':
					stu[x]._english = input("\n请输入修改后的英语成绩：")
					print("\n修改成功！\n")
					_pause_()
					break
				else:
					print("\n！！！输入错误！！！\n")
					_pause_()
					break
			x += 1
			if x == len(stu):
				print("\n！！！未找到该条记录！！！\n")
				_pause_()
	elif a == '2':
		name = input("\n请输入姓名：")
		x = 0
		while x < len(stu) :
			if stu[x]._number == number:
				print("\n1.学号 2.数学成绩 3.物理成绩 4.英语成绩")
				b = input("请输入要修改的项目序号：")
				if b == '1':
					stu[x]._number = input("\n请输入修改后的学号：")
					print("\n修改成功！\n")
					_pause_()
					break
				elif b == '2':
					stu[x]._math = input("\n请输入修改后的数学成绩：")
					print("\n修改成功！\n")
					_pause_()
					break
				elif b == '3':
					stu[x]._physics = input("\n请输入修改后的物理成绩：")
					print("\n修改成功！\n")
					_pause_()
					break
				elif b == '4':
					stu[x]._english = input("\n请输入修改后的英语成绩：")
					print("\n修改成功！\n")
					_pause_()
					break
				else:
					print("\n！！！输入错误！！！\n")
					_pause_()
					break
			x += 1
			if x == len(stu):
				print("\n！！！未找到该条记录！！！\n")
				_pause_()
	else:
		print("\n！！！输入错误！！！\n")
		_pause_()

#查找记录
def _search_(stu):
	print("1.个人成绩    2.分段名单")
	a = input("请输入要使用项目序号：")
	if a == '1':
		print("\n1.学号      2.姓名")
		b = input("请输入要查找的项目序号：")
		if b == '1':    
			number = input("\n请输入学号：")
			x = 0
			while x < len(stu):
				if stu[x]._number == number:
					print("")
					stu[x]._print_()
					print("")
					_pause_()
					break
				x += 1
				if x == len(stu):
					print("\n！！！未找到该条记录！！！\n")
					_pause_()
		elif b == '2':    
			name = input("\n请输入姓名：")
			x = 0
			while x < len(stu):
				if stu[x]._name == name:
					print("")
					stu[x]._print_()
					print("")
					_pause_()
					break
				x += 1
				if x == len(stu):
					print("\n！！！未找到该条记录！！！\n")
					_pause_()
		else:
			print("\n！！！输入错误！！！\n")
			_pause_()
	elif a == '2':
		print("\n1.平均分 2.数学 3.物理 4.英语")
		b = input("请输入要查找的项目序号：")
		if b == '1':
			low = float(input("\n请输入最低分："))
			high = float(input("请输入最高分："))
			print("")
			x = 0
			while x < len(stu):
				if low <= stu[x]._average_() <= high:
					stu[x]._print_()
				x += 1
			print("")
			_pause_()
		elif b == '2':
			low = input("\n请输入最低分：")
			high = input("请输入最高分：")
			print("")
			x = 0
			while x < len(stu):
				if low <= stu[x]._math <= high:
					stu[x]._print_()
				x += 1
			print("")
			_pause_()
		elif b == '3':
			low = input("\n请输入最低分：")
			high = input("请输入最高分：")
			print("")
			x = 0
			while x < len(stu):
				if low <= stu[x]._physics <= high:
					stu[x]._print_()
				x += 1
			print("")
			_pause_()
		elif b == '4':
			low = input("\n请输入最低分：")
			high = input("请输入最高分：")
			print("")
			x = 0
			while x < len(stu):
				if low <= stu[x]._english <= high:
					stu[x]._print_()
				x += 1
			print("")
			_pause_()
		else:
			print("\n！！！输入错误！！！\n")
			_pause_()
	else:
		print("\n！！！输入错误！！！\n")
		_pause_()

#统计分析
def _analysis_(stu):
	print("0.总体 1.数学 2.物理 3.英语")
	a = input("请输入要查询的科目：")
	if a == '0':
		print("\n平均成绩：",_average_(stu,0))
		print("\n标准差：",_biaozhuncha_(stu,0))
		print("\n合格率：",_hegelv_(stu,0)," %\n")
		_pause_()
	elif a == '1':
		print("\n平均成绩：",_average_(stu,1))
		print("\n标准差：",_biaozhuncha_(stu,1))
		print("\n合格率：",_hegelv_(stu,1)," %\n")
		_pause_()
	elif a == '2':
		print("\n平均成绩：",_average_(stu,2))
		print("\n标准差：",_biaozhuncha_(stu,2))
		print("\n合格率：",_hegelv_(stu,2)," %\n")
		_pause_()
	elif a == '3':
		print("\n平均成绩：",_average_(stu,3))
		print("\n标准差：",_biaozhuncha_(stu,3))
		print("\n合格率：",_hegelv_(stu,3)," %\n")
		_pause_()
	else:
		print("\n！！！输入错误！！！\n")
		_pause_()

#成绩排序
def _sort_(stu):
	x = 0
	while x < len(stu):
		y = 0
		while y < len(stu)-1:
			if stu[y]._average_() < stu[y+1]._average_():
				temp = stu[y]
				stu[y] = stu[y+1]
				stu[y+1] = temp
			elif stu[y]._average_() == stu[y+1]._average_():
				if stu[y]._math < stu[y+1]._math:
					temp = stu[y]
					stu[y] = stu[y+1]
					stu[y+1] = temp
				elif stu[y]._math == stu[y+1]._math:
					if stu[y]._physics < stu[y+1]._physics:
						temp = stu[y]
						stu[y] = stu[y+1]
						stu[y+1] = temp
					elif stu[y]._physics == stu[y+1]._physics:
						if stu[y]._english < stu[y+1]._english:
							temp = stu[y]
							stu[y] = stu[y+1]
							stu[y+1] = temp
						elif stu[y]._english == stu[y+1]._english:
							if stu[y]._number < stu[y+1]._number:
								temp = stu[y]
								stu[y] = stu[y+1]
								stu[y+1] = temp
			y += 1
		x += 1
	i = 0
	while i < len(stu):
		stu[i]._print_()
		i += 1
	print("")
	_pause_()

#文件操作
def _file_(stu):
	print("1.读取文件  2.写入文件")
	a = input("请输入要使用的项目序号：")
	if a == '1':
		readfile = open("grade.txt",'r')
		stulines = readfile.readlines()
		x = 0
		while x < len(stulines):
			stu.append(Student((stulines[x].split())[0],(stulines[x].split())[1],(stulines[x].split())[2],(stulines[x].split())[3],(stulines[x].split())[4]))
			x += 1
		readfile.close()
		print("\n读取成功！\n")
		_pause_()
	elif a == '2':
		writefile = open("grade.txt",'w')
		x = 0
		while x < len(stu):
			line = stu[x]._name+" "+stu[x]._number+" "+stu[x]._math+" "+stu[x]._physics+" "+stu[x]._english+"\n"
			writefile.write(line)
			x += 1
		writefile.close()
		print("\n写入成功！\n")
		_pause_()
	else:
		print("\n！！！输入错误！！！\n")
		_pause_()

stu = []

while True:
	print("1.增加记录")
	print("2.删除记录")
	print("3.修改记录")
	print("4.查找记录")
	print("5.统计分析")
	print("6.成绩排序")
	print("7.文件操作")
	print("0.退出程序")
	input_a = input("\n请输入你要使用的功能的序号：")
	print("\n")
	if input_a == '1':
		_add_(stu)
	elif input_a == '2':
		_delete_(stu)
	elif input_a == '3':
		_change_(stu)
	elif input_a == '4':
		_search_(stu)
	elif input_a == '5':
		_analysis_(stu)
	elif input_a == '6':
		_sort_(stu)
	elif input_a == '7':
		_file_(stu)
	elif input_a == '0':
		break
	else:
		print("！！！输入错误！！！\n")
		_pause_()