#include <iostream>
#include <vector>

using namespace std;

const int n = 5; //进程个数
const int m = 3; //资源种类

int Available[m] =  { 2, 3, 3 };
int Alloc[n][m] = { 2, 1, 2, 4, 0, 2, 3, 0, 5, 2, 0, 4, 3, 1, 4 };
int Need[n][m] = { 3, 4, 7, 1, 3, 4, 0, 0, 3, 2, 2, 1, 1, 1, 0 };
bool Finish[n] = { false, false, false, false, false };
int Work[m];
int Request[m];
int p;
vector<int> vec;

bool request_need() {
    int count = 0;
    int num = p;
    for (int i = 0; i < 3; i++) {
        if (Request[i] < Need[num-1][i] || Request[i] == Need[num-1][i]) {
            count++;
        }
    }
    if (count == 3) return true;
    else return false;
}

bool request_available() {
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (Request[i] < Available[i] || Request[i] == Available[i]) {
            count++;
        }
    }
    if (count == 3) return true;
    else return false;
}

bool need_work(int num) {
    int count = 0;
    for (int i=0; i < m; i++) {
        if (Need[num][i] < Work[i] || Need[num][i] == Work[i]){
            count++;
        }
    }
    if (count==m) return true;
    else return false;
}

bool security() {
    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (!Finish[j] && need_work(j)) {
                Finish[j] = true;
                Work[0] += Alloc[j][0];
                Work[1] += Alloc[j][1];
                Work[2] += Alloc[j][2];
                vec.push_back(j+1);
            }
        }
    }
    int count = 0;
    for (int i=0; i < n; i++) {
        if (Finish[i]) count++;
    }
    if (count == n) return true;
    else return false;
}

int main() {
    while (1) {
        cout << "输入进程号: " ;
        cin >> p;
        cout << "输入请求资源A、B、C的个数: ";
        for (int i=0; i<m; i++) cin >> Request[i];

        if (!request_need()) { //非法请求
            cout << "非法请求！" << endl;
            continue;
        }
        if (!request_available()) { //Pi阻塞
            cout << "P" << p << "阻塞" << endl;
            continue;
        }

        for (int i=0; i < m; i++) {
            Available[i] = Available[i] - Request[i];
        }
        for (int i = 0; i < m; i++) {
            Alloc[p-1][i] += Request[i];
        }
        for (int i=0; i < m; i++) {
            Need[p-1][i] -= Request[i];
        }

        for (int i=0; i<m; i++) Work[i] = Available[i];
        if (security()) {
            cout << "安全, ";
            int i=0;
            for (vector<int>::iterator it=vec.begin(); it < vec.end(); it++) {
                cout << "P" << *(it) << " ";
                Finish[i] = false;
                i++;
            }
            cout << endl;
            vec.clear();
        } else {
            for (int i=0; i < m; i++) {
                Available[i] = Available[i] + Request[i];
            }
            for (int i=0; i < m; i++) {
                Alloc[p-1][i] -= Request[i];
            }
            for (int i=0; i < m; i++) {
                Need[p-1][i] += Request[i];
            }
            cout << "不安全,已回收！" << endl;
        }
    }
    return 0;
}
