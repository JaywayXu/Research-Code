#include <iostream>
#include <iomanip>

using namespace std;

class RD { //分区描述器
public:
    bool flag;
    int number;
    int addr;
    int size;
    RD *next;
    RD() {flag = 0; number = 0; addr = 0; size = 0; next = NULL;}
    RD(bool var1,int var2,int var3,int var4) {
        flag = var1; number = var2; addr = var3; size = var4; next = NULL;
        }
    void print() {
        if (number) {
            cout << "标志:" << setw(5) << flag
            << "  进程号:" << setw(5) << number
            << "  起始地址:" << setw(5) << addr
            << "  大小:" << setw(5) << size << endl;
        }
        else cout << "标志:" << setw(5) << flag
        << "  进程号:" << setw(5) << "空闲"
        << "  起始地址:" << setw(5) << addr
        << "  大小:" << setw(5) << size << endl;
    }
};


class Memory {
private:
    RD *head;
    int maxsize;
    int j_number;

public:
    Memory();
    ~Memory() {del(head);}
    void del(RD *p);

    void run();
    void print();

    bool request_first();
    bool request_fixed();
    bool request_nfixed();
    void release();

    int get_input_size();
    RD *get_pre(RD *p);
};

Memory::Memory() {
    head = new RD();
    j_number = 0;
}

void Memory::del(RD *p) {
    if (p) {
        del(p->next);
        delete p;
    }
}

void Memory::run() {
    cout << "输入主存空间: ";
    cin >> maxsize;
    head->next = new RD(0,0,0,maxsize);

    int method;
    cout << "策略: 1.首次 2.最适合 3.最不适合 ";
    cin >> method;
    while(method!=1 && method!=2 && method!= 3) {
        cout << "请输入正确的序号!" << endl;
        cout << "策略: 1.首次 2.最适合 3.最不适合 ";
        cin >> method;
    }

    while (1) {
        int fun;
        cout << "输入要使用的功能: 1.请求 2.释放 3.退出 ";
        cin >> fun;

        switch (fun) {
            case 1:
                switch (method) {
                case 1:
                    request_first();
                    print();
                    break;
                case 2:
                    request_fixed();
                    print();
                    break;
                case 3:
                    request_nfixed();
                    print();
                    break;
                }
                break;
            case 2:
                release();
                print();
                break;
            case 3:
                return;
            default:
                cout << "请输入正确的序号!" << endl;
                break;
        }
    }
}

void Memory::print() {
	RD *p = head;
	while (p != NULL) {
		if (p != head) {
			p->print();
		}
        p = p->next;
	}
}

bool Memory::request_first() {
    int size = get_input_size()+1;
    RD *p = head;
	while (p != NULL) {
		if (!p->flag && (p->size + 1) >= size) {
			RD *new_ptr = new RD(1, ++j_number, p->addr+p->size-size+1, size-1);
			RD *tmp = p->next;
			new_ptr->next = tmp;
			p->next = new_ptr;
			p->size -= size;
			if (p->size == -1) {				
				get_pre(p)->next = p->next;
				delete p;				
			}
			cout << "成功！" << endl;
			return true;
		}
        p = p->next;
	}
	cout << "空间不足！" << endl;
    return false;
}

bool Memory::request_fixed() {
    int size = get_input_size()+1;
    RD *p = head;
	RD *min_ptr = new RD(0, 0, 0, maxsize);
	while (p != NULL) {		
		if (!p->flag && (p->size+1) >= size && p->size <= min_ptr->size) {
			min_ptr = p;
		}
        p = p->next;
	}
	if (min_ptr->size+1 >= size) {
		RD *new_ptr = new RD(1, ++j_number, min_ptr->addr+min_ptr->size-size+1, size-1);
		RD *tmp = min_ptr->next;
		new_ptr->next = tmp;
		min_ptr->next = new_ptr;
		min_ptr->size -= size;
		if (min_ptr->size == -1) {
			get_pre(min_ptr)->next = min_ptr->next;
			delete min_ptr;
		}
		cout << "成功！" << endl;
		return true;
	}
	cout << "空间不足！" << endl;
    return false;
}

bool Memory::request_nfixed() {
    int size = get_input_size()+1;
    RD *p = head;
	RD *max_ptr = p->next;
	while (p != NULL) {
		if (!p->flag && (p->size+1) >= size && p->size >= max_ptr->size) {
			max_ptr = p;
		}
        p = p->next;
	}
	if (max_ptr->size+1 >= size) {
		RD *new_ptr = new RD(1, ++j_number, max_ptr->addr+max_ptr->size-size+1, size-1);
		RD *tmp = max_ptr->next;
		new_ptr->next = tmp;
		max_ptr->next = new_ptr;
		max_ptr->size -= size;
		if (max_ptr->size == -1) {
			get_pre(max_ptr)->next = max_ptr->next;
			delete max_ptr;
		}
		cout << "成功！" << endl;
		return true;
	}
	cout << "空间不足！" << endl;
    return false;
}

void Memory::release() {
    int j;
    cout << "输入要释放的进程号: ";
    cin >> j;

    //获取要释放进程的指针
    RD *p_release = head;
	while (p_release) {
		if (p_release->number == j && p_release->flag) {
            break;
		}
        p_release = p_release->next;
	}

    //获取前一个结点指针
    RD *pre = get_pre(p_release);

    if (!p_release) {
        cout << "无此进程!" << endl;
    } else if (pre == head && p_release->next) {
        if (p_release->next->flag) {
			p_release->flag = 0;
			p_release->number = 0;
		}
		else {
			p_release->next->addr -= (p_release->size + 1);
			p_release->next->size += (p_release->size + 1);
			head->next = p_release->next;
			delete p_release;
		}
    } else if (pre == head && !p_release->next) {
        p_release->flag = 0;
		p_release->number = 0;
    } else if (pre != head && !p_release->next) {
        if (pre->flag) {
			p_release->flag = 0;
			p_release->number = 0;
			return;
		}
		else {
			pre->size += (p_release->size + 1);
			pre->next = NULL;
			delete p_release;
		}
    } else if (pre != head && p_release->next) {
        if (pre->flag && p_release->next->flag) {
            p_release->flag = 0;
            p_release->number = 0;
        } else if (!pre->flag && p_release->next->flag) {
            pre->size += (p_release->size + 1);			
            pre->next = p_release->next;
            delete p_release;
        } else if (pre->flag && !p_release->next->flag) {
            p_release->next->size += (p_release->size + 1);
            p_release->next->addr = p_release->addr;
            pre->next = p_release->next;
            delete p_release;
        } else if (!pre->flag && !p_release->next->flag) {
            pre->size += (p_release->size + 1);
            pre->size += (p_release->next->size + 1);
            pre->next = p_release->next->next;
            delete p_release->next;
            delete p_release;
        }
    }
}

int Memory::get_input_size() {
    int size;
    cout << "输入申请大小: ";
    cin >> size;
    return size;
}

RD *Memory::get_pre(RD *p) {
    RD *temp = head;
    while (temp) {
		if (temp->next == p) {
			return temp;
		}
        temp = temp->next;
	}
	return NULL;
}

int main() {
    Memory m;
    m.run();
    return 0;
}
