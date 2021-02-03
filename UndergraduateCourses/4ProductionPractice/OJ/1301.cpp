#include<iostream>
using namespace std;

typedef struct LNode {
	int data;
	struct LNode* next;
}LNode, *LinkedList;

void InitLinkList(LinkedList& L, int n) {
	int i;
	L = new LNode();
	if (L == NULL) {
		cout << "分配失败!\n";
	}
	L->data = -999;
	L->next = NULL;
	LNode* p = L;
	for (i = 0; i < n ; i++) {
		LNode * temp = new LNode();
		temp->data = i;
		temp->next = NULL;
		p->next = temp;
		p = p->next;
	}
	p->next = L; //构成循环链表
}

int get_len(LinkedList& L) {
	int len = 0;
	LNode* p = L->next;
	while (p != L) {
		p = p->next;
		len++;
	}
	return len;
}
void kill_people(LinkedList& L) {
	int margin = 3;
	int count = 1;
	LNode* p = L->next;
	LNode* pre = L;
	while (get_len(L)>1) {
		if (count == 3) {
			//cout << "被杀死的是:" << p->data << endl;
			pre->next = p->next;
			free(p);
			p = pre->next;
			if (p == L) {
				p = p->next;
				pre = pre->next;
			}
			count = 1;
		}
		p = p->next;
		pre = pre->next;
		if (p == L) {
			p = p->next;
			pre = pre->next;
		}
		count++;
	}
	cout << L->next->data << endl;
}

int main()
{
	int n;
	cin >> n;
	LinkedList L;
	InitLinkList(L, n);
	//cout << L->next->next->next->next->data << endl;
	//cout << get_len(L) << endl;
	kill_people(L);
	return 0;
}