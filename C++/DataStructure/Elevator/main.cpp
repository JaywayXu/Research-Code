#include"Elevator.h"

int main() {
	long int time = 0;
	int a = 0, j = 1;
	cout << "请输入共有几位乘客使用电梯：";
	cin >> a;
	Passenger *people = new Passenger[a + 1];
	for (int i = 1; i < a + 1; i++) {
		people[i].setData(i);
		cout << endl;
	}
	Elevator x;
	long int Time = 0;
	
	Time = a * 1000;//此处的设置并不是最优解，目前还没有找到一个比较合适的值代替
	for (; time < Time; time++) {
		cout << time << "t时刻  ";
		for (int i = 1; i < a + 1; i++) {
			if (people[i].getWhenWait() == time)x.addPassenger(people[i]);
		}
		cout << "电梯在" << x.getFloor() << "层  ";
		x.judgeGiveUp(time);
		cout << endl;
	}
	delete[]people;
	system("pause");
	return 0;
}