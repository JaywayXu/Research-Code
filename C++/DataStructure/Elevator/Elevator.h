#ifndef ELEVATOR_H
#define ELEVATOR_H

#include"PList.h"
#include"Passenger.h"

enum state {
	Opening,
	Opened,
	Closing,
	Closed,
	Waiting,
	Up,
	Down,
	In,
	Out,
	Accelerate,
	Decelerate
};

const int test = 40; // 检测有无再上电梯的乘客
const int open = 20; // 开门
const int close = 20; // 关门
const int in = 25; // 进
const int out = 25; // 出
const int accelerate = 15; // 加速
const int up = 51; // 向上一层
const int updecelerate = 14; // 上升减速
const int down = 61; // 向下一层
const int downdecelerate = 23; // 下降减速
const int wait = 300; // 静止时间

class Elevator {
private:
	state stateNow; // 电梯当前状态
	int floor; // 电梯当前所在层
	PList *pList; // 等待队列
	int inElevator[10]; // 电梯内
	int all;
	int dir; // 判断上下的情况
	int holdtime;
	int record;
	int near;
	int downTime;
	int upTime;

public:
	Elevator();
	~Elevator() {delete pList;}

	state getNowState()const {return stateNow;}
	void setNowState(state t) {stateNow = t;}
	int getFloor()const {return floor;}
	void setfloor(int floor1) {floor = floor1;}
	int getAll()const {return all;}
	void setAll(int num) {all += num;} // num为外部上电梯的人数
	int getDir()const {return dir;}
	void setDir(int num) {dir = num;}

	void addPassenger(const Passenger &x);// 添加乘客
	void judgeGiveUp(int &time); // 判断是否有人放弃，用在函数最开始
	bool noPassenger(int &time); // 判断是否有乘客请求

	void judgeDirction(int &time); // 判断电梯行走方向
	void moveDirction(const int floor1, int &time); // 用来改变电梯的状态

	bool judgeOpen(int &time); // 判断是否开门
	void OPEN(int &time); // 电梯门打开

	void judgeClose(int &time); // 40t时间来判断是否关门
	void CLOSE(int &time); // 关门

	bool judgeOut(int &time); // 判断乘客出去
	void OUT(int &time); // 乘客出去

	bool judgeIn(int &time); // 判断乘客进入
	void IN(int &time); // 乘客进入

	void moveUp(int &time); // 向上移动
	void moveDown(int &time); // 向下移动
};

Elevator::Elevator() {
	stateNow = Waiting;
	floor = 1;
	pList = new PList();
	for (int i=0; i<10; i++)inElevator[i] = 0;
	all = 0;
	dir = -1;
	holdtime = 0;
	record = 0;
	near = 0;
	downTime = 0;
	upTime = 0;
}

void Elevator::addPassenger(const Passenger &x) {
	pList->append(x);
	cout << " 第" << x.getID() << "名乘客进入等待队列 ";
}

void Elevator::judgeGiveUp(int &time) {
	//一进入系统则先判断该时刻是否有人放弃
	//waittime为现在的时间，用于和乘客等待的时间+wait来进行判断乘客是否放弃
	Node * ptemp = pList->getHead()->next;
	while (ptemp != NULL) {
		if ((ptemp->data.getWhenWait() + ptemp->data.getWaitTime()) <= time) {
			cout << "第" << ptemp->data.getID() << "名乘客已放弃等待  ";
			int delid = ptemp->data.getID();
			ptemp = ptemp->next;
			pList->remove(delid);
		}
		else ptemp = ptemp->next;
	}
	noPassenger(time);
}

bool Elevator::noPassenger(int &time) {
	// 用于判断电梯是否接收乘客的请求
	if (getNowState() == Waiting) {
		if (holdtime == wait && floor != 1) {
			//如果等够了300t并且不在1楼的话，开始下行
			setNowState(Down);
			setDir(0);
			holdtime = 0;
			moveDown(time);
			return true;
		} else if (holdtime == wait && floor == 1) {
			//如果电梯本身在一楼则不需要进行操作
			cout << "电梯空闲无人，正在等待";
			holdtime = 0;
			return true;
		} else if (all == 0 && pList->empty() == true) {
			cout << "电梯空闲无人，正在等待";
			holdtime++;
			return true;
		} else {
			judgeDirction(time);
			return false;
		}
	} else {
		judgeDirction(time);
		return false;
	}
}

void Elevator::judgeDirction(int &time) {
	// 使用该函数进行判断电梯的走向
	near = floor; // 初始化near的值，为防止不满足条件的情况出现时依旧可以使用MoveDirction函数
	int upoutfar = 0, downoutfar = 10; // 定义2个记录上下出去最远请求的变量
	int upinfar = 0, downinfar = 10; // 定义2个记录上下进来最远请求的变量
	if (stateNow == Closed) {
		if (getAll() == 0 && pList->empty() == true) {
			setNowState(Waiting);
			return;
		}
		if (floor == 1) {
			setNowState(Up); setDir(1);
		}
		if (floor == 9) {
			setNowState(Down); setDir(0);
		}
		if (getAll() != 0) {//电梯里依旧有人
			//此时需要区分电梯的运行方向，分两种情况来处理
			bool key = false;
			for (int i=floor; i<10; i++) {
				if (inElevator[i] != 0) {
					near = i;
					upoutfar = i;
					setNowState(Up);
					setDir(1);
					key = true;
					break;
				}
			}
			if (key == false) {
				for (int i=1; i<floor; i++) {
					if (inElevator[i] != 0) {
						near = i;
						downoutfar = i;
						setNowState(Down);
						setDir(0);
						break;
					}
				}
			}
		}
		if (pList->empty() == false) {//电梯外等待的人不为空
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (getDir() == 1) {//只接上行乘客
					if (ptemp->data.getNowFloor() > floor) {//乘客所处楼层在电梯楼层上，这样才有可能电梯前往接人
						//开始检索在链表中的乘客，并且进行判断是否有要上行的
						if (ptemp->data.getGoFloor() > ptemp->data.getNowFloor()) {
							//代表此人是上行，并且是在电梯运行方向的楼上，需要前往接人
							if (ptemp->data.getGoFloor() > upoutfar)upoutfar = ptemp->data.getGoFloor();
						} else {
							if (ptemp->data.getNowFloor() > upoutfar)upoutfar = ptemp->data.getNowFloor();
						}
					}
					if (upinfar == 0 && upoutfar == 0) { setNowState(Down); setDir(0); }
					if (upinfar <= upoutfar)near = upoutfar;
					else near = upinfar;
				} else if (getDir() == 0) {//只接下行乘客
					if (ptemp->data.getNowFloor() < floor) {//乘客所处楼层在电梯楼层下，这样才有可能电梯前往接人
						//开始检索在链表中的乘客，并且进行判断是否有要下行的
						if (ptemp->data.getGoFloor() < ptemp->data.getNowFloor()) {
							//代表此人是下行，并且是在电梯运行方向的楼下，需要前往接人
							if (ptemp->data.getGoFloor() < downoutfar)downoutfar = ptemp->data.getGoFloor();
						}
						if (ptemp->data.getGoFloor() > ptemp->data.getNowFloor()) {
							if (ptemp->data.getNowFloor() < downoutfar)downoutfar = ptemp->data.getNowFloor();
						}
					}
					if (downinfar == 10 && downoutfar == 10) { setNowState(Up); setDir(1); }
					if (downinfar <= downoutfar)near = downinfar;
					else near = downoutfar;
				}
				ptemp = ptemp->next;
			}
		}

	}
	if (stateNow == Waiting) {
		Node * ptemp = pList->getHead()->next;
		int time_now = 0;
		while (ptemp != NULL) {
			int Time_now = ptemp->data.getWhenWait();//用于记录最先按的人
			time_now = Time_now;
			if (ptemp->data.getWhenWait() < time_now){//挑选出最先按键的人，然后进行改变电梯的方向
				time_now = ptemp->data.getWhenWait();
			}
			ptemp = ptemp->next;
		}
		ptemp = pList->getHead()->next;
		while (ptemp != NULL) {
			int up(floor), down(floor);
			if (ptemp->data.getWhenWait() == time_now) {
				int x = ptemp->data.getGoFloor() - ptemp->data.getNowFloor();
				//此时会出现4种情况，并且只会有2种是电梯上行，2种是电梯下行
				if ((x > 0 && (ptemp->data.getNowFloor() > floor)) || (x<0 && (ptemp->data.getNowFloor()>floor))) {
					setNowState(Up);
					setDir(1);
					upinfar = ptemp->data.getNowFloor();
					if (up < upinfar) {
						up = upinfar;
					}
				} else if ((x > 0 && (ptemp->data.getNowFloor() < floor)) || (x < 0 && (ptemp->data.getNowFloor() < floor))) {
					setNowState(Down);
					setDir(0);
					downinfar = ptemp->data.getNowFloor();
					if (down > downinfar) {
						down = downinfar;
					}
				}
				if (down != floor&&up != floor) {//当上下同时有人请求时，满足先上的原则
					setNowState(Up); near = upinfar; setDir(1);
				} else if (up != floor) {//只有上行的请求
					setNowState(Up); near = upinfar; setDir(1);
				} else if (down != floor) {//只有下行的请求
					setNowState(Down); near = downinfar; setDir(0);
				}
				if (floor == 1) { setNowState(Up); setDir(1); }
			}
			ptemp = ptemp->next;
		}
		if (near == floor)  OPEN(time);
	}
	if (stateNow == Up) {
		if (getAll() != 0) {//电梯里有人
			for (int i = 1; i < 10; i++) {
				if (inElevator[i] != 0) {
					if (i >= near) {
						upinfar = i;
					}
				}
			}
		}
		if (pList->empty() == false) {
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() >= near) {
					if (ptemp->data.getGoFloor() >= upoutfar) {
						upoutfar = ptemp->data.getGoFloor();
					}
					if (ptemp->data.getNowFloor() >= upoutfar) {
						upoutfar = ptemp->data.getNowFloor();
					}
				}
				ptemp = ptemp->next;
			}
		}
		if (upinfar >= upoutfar) near = upinfar;
		else near = upoutfar;
	}
	if (stateNow == Down) {
		//downinfar = 10, downoutfar = 10;
		if (getAll() != 0) {//电梯里有人
			for (int i = 1; i < 10; i++) {
				if (inElevator[i] != 0) {
					if (i <= near) {
						downinfar = i;
						break;
					}
				}
			}
		}
		if (pList->empty() == false) {
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() <= near) {
					if (ptemp->data.getNowFloor() <= downoutfar) {
						downoutfar = ptemp->data.getNowFloor();
					}
					if (ptemp->data.getGoFloor() <= downoutfar) {
						downoutfar = ptemp->data.getGoFloor();
					}
				}
				ptemp = ptemp->next;
			}
		}
		if (getAll() == 0 && pList->empty() == true)near = 1;
		else if (downinfar >= downoutfar)near = downoutfar;
		else near = downinfar;
	}
	moveDirction(near, time);
}

void Elevator::moveDirction(const int near, int &time) {
	//near为乘客的请求最远的楼层
	if (near < floor) {
		setNowState(Down);
		setDir(0);
		moveDown(time);
		return;
	}
	if (near > floor) {
		setNowState(Up);
		setDir(1);
		moveUp(time);
		return;
	}
	if (getNowState() == Opening) {
		OPEN(time);
		return;
	}
	if (getNowState() == In) {
		IN(time);
		judgeClose(time);
		return;
	}
	if (getNowState() == Out) {
		OUT(time);
		judgeClose(time);
		return;
	}
	if (getNowState() == Opened) {
		judgeClose(time);
		if (judgeOut(time))OUT(time);
		if (judgeIn(time))IN(time);
		return;
	}
	if (getNowState() == Closing) {
		CLOSE(time);
		return;
	}
	if (near == floor&&pList->empty() == true && getAll() == 0) {
		setNowState(Waiting);
		noPassenger(time);
		return;
	}
	if (near == floor) {
		setNowState(Opening);
		OPEN(time);
		return;
	}
}

bool Elevator::judgeOpen(int &time) {//判断此楼层是否有人需要进出
	if (judgeIn(time) || judgeOut(time)) {
		OPEN(time);
		return true;
	}
	else return false;
}

void Elevator::OPEN(int &time) {
	if (getNowState() != Opening) {
		setNowState(Opening);
		record = 0;
		return;
	}
	if (record < open) {
		record++;
		cout << "电梯开门中";
		return;
	} else {//开门完成后
		record = 0;
		cout << "开门完成";
		setNowState(Opened);
		if (judgeOut(time))OUT(time);
		if (judgeIn(time))IN(time);
		judgeClose(time);
	}
}

void Elevator::judgeClose(int &time) {
	if (getNowState() == Opened){
		if (record < test) {
			record++;
			cout << "正在关门检测";
			return;
		} else {
			cout << "关门检测结束";
			if (getNowState() == Opened) {
				record = 0;
				CLOSE(time);
				return;
			} else {//疑似可以删除    
				record = 0;
				return;
			}
		}
	}
	else return;
}

void Elevator::CLOSE(int &time) {
	if (record < close) {
		record++;
		setNowState(Closing);
		cout << "电梯正在关门中";
	} else {
		record = 0;
		cout << "电梯已经关门";
		setNowState(Closed);
		if (near == floor) {//电梯已经到达最大请求楼层，可能会出现4种情况
			if (pList->empty() == false || getAll() != 0) {//等待队列有人或电梯里也有人
				Node * ptemp = pList->getHead()->next; int OutPeople = 0;
				while (ptemp != NULL) {
					if (ptemp->data.getNowFloor() == floor)OutPeople += 1;
					if (getAll() != 0 && OutPeople != 0) {//电梯里有人，外面有人       判断去的方向
						if (getDir() == 1 && (ptemp->data.getGoFloor() > floor)) {//电梯上行，乘客上行，开门
							setNowState(Opening);
						} else if (getDir() == 0 && (ptemp->data.getGoFloor() < floor)) {//电梯下行，乘客下行，开门
							setNowState(Opening);
						}
					}
					if (getAll() == 0 && OutPeople != 0) {//电梯没人，外面有人
						if (getDir() == 1) {//电梯上行
							if (ptemp->data.getGoFloor() > floor)
								setNowState(Opening);
							else if (ptemp->data.getGoFloor() < floor) {
								setDir(0); setNowState(Opening);
							}
						}
						if (getDir() == 0) {//电梯下行
							if (ptemp->data.getGoFloor() < floor)
								setNowState(Opening);
							else if (ptemp->data.getGoFloor() > floor) {
								setDir(1); setNowState(Opening);
							}
						}
					}
					if (getAll() != 0 && OutPeople == 0) {
						//电梯里有人，外面没人，此时应该分是否继续送乘客上行或者下行，首先遍历数组得到乘客要去几层
						for (int i = 1; i < 10; i++) {
							if (inElevator[i] != 0) {
								if (i < floor) { setNowState(Down); setDir(0); }
								if (i > floor) { setNowState(Up); setDir(1); }
							}
						}
					}
					ptemp = ptemp->next;
				}
			} else if (pList->empty() == true && getAll() == 0){//等待队列没人，电梯也没人
				setNowState(Waiting); setDir(-1);
			}
		} else if (near != floor) {
			if (getDir() == 1) {
				setDir(1); setNowState(Up);
			}
			if (getDir() == 0) {
				setDir(0); setNowState(Down);
			}
		}
		noPassenger(time);
	}
}

bool Elevator::judgeOut(int &time) {
	if (getAll() != 0) {
		int j = floor;
		if (inElevator[j] != 0)return true;
	}
	return false;
}

void Elevator::OUT(int &time) {
	if (record < out) {
		if (getNowState() == Opened) {
			record++;
			cout << "乘客正在下电梯";
			if (inElevator[floor] != 0) {
				cout << "在该层一共下去" << inElevator[floor] << "个人";
				setAll(-inElevator[floor]);
				inElevator[floor] = 0;
			}
			setNowState(Out);
			return;
		}
		if (getNowState() == Out) {
			record++;
			cout << "乘客正在下电梯";
			return;
		}
	} else {
		cout << "电梯里需要下的乘客都已下去";
		record = 0;
		setNowState(Opened);
	}
}

bool Elevator::judgeIn(int &time) {//如果电梯未满，则返回true，可以继续进人
	//目前需要完善，因为是先把人删除输入进数组，所以需要进行有个判断
	if (getAll() != 13) {
		if (!pList->empty()) {//不为空则执行if语句
			Node * ptemp = pList->getHead()->next; int upnum1 = 0, downnum1 = 0;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() == floor) {
					if ((ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) && (getDir() > 0)) {
						//乘客是往上走的
						return true;
					}
					if ((ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) && (getDir() == 0)) {
						//乘客下行
						return true;
					}
					int floor1 = near;
					for (int i=floor1+1; i<10; i++) { // 消除BUG
						if (inElevator[i] != 0) {
							near = i;
						}
					}
					if (near == ptemp->data.getNowFloor()) {
						//达到了最大请求楼层，如果是与电梯方向同向，则不改变方向，并且允许进入
						//如果不与电梯同向，则改变方向，如果两个情况都有，就优先满足同方向的
						if (getDir() == 1) {
							if (ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) {
								setDir(1); upnum1++;
							}
							if (ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) {
								setDir(0); downnum1++;
							}
							if (upnum1 != 0 && downnum1 != 0)setDir(1);
						} else if (getDir() == 0) {
							if (ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) {
								setDir(1); upnum1++;
							}
							if (ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) {
								setDir(0);  downnum1++;
							}
							if (upnum1 != 0 && downnum1 != 0)setDir(0);
						}
						return true;
					}
				}
				// if (ptemp->data.getNowFloor() > floor) {
				// 	setNowState(Up);
				// 	setDir(1);
				// }
				ptemp = ptemp->next;
			}
		}
	}
	return false;
}

void Elevator::IN(int &time) {
	if (getAll() < 13) {
		if (record < in) {
			if (getNowState() == Opened) {
				record++;
				Node * ptemp = pList->getHead()->next;
				while (ptemp != NULL) {
					if (ptemp->data.getNowFloor() == floor){//首先人得在电梯楼层，这才能进行判定
						if ((ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) && (getDir() > 0)) {
							//乘客是往上走的
							cout << "第" << ptemp->data.getID() << "个乘客正在进入电梯";
							inElevator[ptemp->data.getGoFloor()] += 1;
							setAll(1);
							pList->remove(ptemp->data.getID());
							setNowState(In);
							return;
						}
						if ((ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) && (getDir() == 0)) {
							//乘客下行
							cout << "第" << ptemp->data.getID() << "个乘客正在进入电梯";
							inElevator[ptemp->data.getGoFloor()] += 1;
							setAll(1);
							pList->remove(ptemp->data.getID());
							setNowState(In);
							return;
						}
					}
					ptemp = ptemp->next;
				}
			}
			if (getNowState() == In) {
				record++;
				cout << "乘客正在进入电梯";
				return;
			}
		} else {
			cout << "乘客已经进入电梯";
			record = 0;
			setNowState(Opened);
		}
	} else {
		cout << "电梯内人数已经达到最大值";
		setNowState(Closing);
	}
}

void Elevator::moveUp(int &time) {
	if (record < accelerate) {
		record++;
		cout << "电梯正在加速上楼";
		return;
	}
	if (record < up+accelerate) {
		record++;
		cout << "电梯正在匀速上楼";
		return;
	} else {
		floor++;
		record = 0;
		if (judgeOpen(time) == false) {
			record = accelerate+1;
			moveUp(time);
		}
		else {
			cout << "电梯正在匀速上楼" << endl;
			while (upTime <= updecelerate) {
				cout << time+1 << "t时刻  ";
				cout << "电梯在" << getFloor()-1 << "层  ";
				if (upTime == updecelerate) cout << "电梯已到达"; 
				else cout << "电梯正在减速上楼" << endl;
				upTime++;
				time++;
			}
			upTime = 0;
			setNowState(Opening);
		}
	}

}

void Elevator::moveDown(int &time) {
	if (record < accelerate) {
		record++;
		cout << "电梯正在加速下楼";
		return;
	}
	if (record < down+accelerate) {
		record++;
		cout << "电梯正在匀速下楼";
		return;
	} else {
		floor--;
		record = 0;
		if (judgeOpen(time) == false) {
			record = accelerate+1;
			moveDown(time);
		}
		else {
			cout << "电梯正在匀速下楼" << endl;
			while (downTime <= downdecelerate) {
				cout << time+1 << "t时刻  ";
				cout << "电梯在" << getFloor()+1 << "层  ";
				if (downTime == downdecelerate) cout << "电梯已到达"; 
				else cout << "电梯正在减速下楼" << endl;
				downTime++;
				time++;
			}
			downTime = 0;
			setNowState(Opening);
		}
	}
}

#endif // ELEVATOR_H