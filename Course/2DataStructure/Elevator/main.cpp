#include "Elevator.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	while(1){
		int nowtime = 1;
		int Time = 0;
		int a = 0;

		cout << "1.手动输入 2.自动生成" << endl;
		int input1;
		cin >> input1;

		if (1 == input1) {
			cout << "请输入共有几位乘客使用电梯：";
			cin >> a;
			Passenger *people = new Passenger[a + 1];
			for (int i = 1; i < a + 1; i++) {
				people[i].setData(i);
				cout << endl;
			}
			Elevator x;
			Time = (a * 600) + 1000;//此处的设置并不是最优解
			for (; nowtime < Time; nowtime++) {
				cout << nowtime << "t时刻  ";
				for (int i = 1; i < a + 1; i++) {
					if (people[i].getWhenWait() == nowtime)x.addPassenger(people[i]);
				}
				cout << "电梯在" << x.getFloor() << "层  ";
				x.judgeGiveUp(nowtime);
				cout << endl;
			}
			delete[]people;
			system("pause");
		} else if (2 == input1) {
			srand((unsigned)time(NULL));
			int a = rand()%10+1;
			Passenger *people = new Passenger[a+1];
			int nowFloor, goFloor, whenWait, waitTime;
			for (int i=1; i < a+1; i++) {
				cout << i << ": ";
				nowFloor = rand()%9+1; cout << nowFloor << "->";
				goFloor = rand()%9+1;
				if (nowFloor == goFloor) goFloor = (nowFloor + 1)%9+1; // 如果产生的随机数相同，则使之不相同
				cout << goFloor << "; ";
				whenWait = (rand()%100)*4 + rand()%4; cout << whenWait << " ";
				waitTime = (rand()%200+200)*10 + rand()%10; cout << waitTime << endl;
				people[i].setData(i, nowFloor, goFloor, whenWait, waitTime);
			}
			Elevator x;
			Time = (a * 600) + 1000;
			for (; nowtime < Time; nowtime++) {
				cout << nowtime << "t时刻  ";
				for (int i = 1; i < a + 1; i++) {
					if (people[i].getWhenWait() == nowtime)x.addPassenger(people[i]);
				}
				cout << "电梯在" << x.getFloor() << "层  ";
				x.judgeGiveUp(nowtime);
				cout << endl;
			}
			delete[]people;
			system("pause");
		}
	}
	
	return 0;
}