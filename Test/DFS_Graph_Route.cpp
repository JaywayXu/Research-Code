#include <iostream>
using namespace std;

char visit[100];
char Vec[100][2] = {'a', 'b',
		    'b', 'd',
		    'c', 'f',
		    'd', 'v',
		    'e', 'd',
		    'e', 'u',
		    'f', 'e',
		    'f', 'v',
		    'u', 'a',
		    'u', 'c',
		    'v', 'b'};
int numVec = 11;

bool isInVisit(char nowNode, char visit[], int len_v);

void getRoute(char nowNode, char visit[], int len_v) {
	// 遍历临接表
	for(int i=0; i<numVec; i++) {
		char nextNode = 0;
		if (nowNode == Vec[i][0]) {
			nextNode = Vec[i][1];
		}
		visit[len_v] = nextNode; // 加入到已访问数组
		if (nextNode == 'v') { // 找到了最终节点
			for (int j=0; j<len_v+1; j++)
				cout << visit[j]; // 输出最终找到到路径
			cout << endl;
		}
		else if (isInVisit(nextNode, visit, len_v)) { // 已经访问过了
			return;
		}
		else if (nextNode != 0) { // 找到了连接的节点
			getRoute(nextNode, visit, len_v+1);
		}
	}
}

bool isInVisit(char nowNode, char visit[], int len_v) {
	for(int i=0; i<len_v; i++) {
		if (visit[i] == nowNode) return true;
	}
	return false;
}

int main() {
	visit[0] = 'u';
	getRoute('u', visit, 1);
	return 0;
}