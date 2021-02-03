#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct Employee {
    string name;
    int work_age;
    int age;
};

int partition(vector<Employee> &v, int low, int high) {
    Employee pivot = v[low];
    while (low < high) {
        while (low < high && v[high].age >= pivot.age) high--;
        v[low] = v[high];
        while (low < high && v[low].age <= pivot.age) low++;
        v[high] = v[low];
    }
    v[low] = pivot;
    return low;
}

void quickSort(vector<Employee> &v, int low, int high) {
    if (low < high) {
        int p = partition(v,low,high);
        quickSort(v,low,p-1);
        quickSort(v,p+1,high);
    }
}

void bubleSort(vector<Employee> &v) {
    int length = v.size();
    for (int i=0; i<length; i++) {
        for (int j=i; j<length-i-1; j++) {
            if (v[j].age >= v[j+1].age) {
                Employee t = v[j];
                v[j] = v[j+1];
                v[j+1] = t;
            }
        }
    }
}

void output(vector<Employee> v) {
    for (int i=0; i<v.size(); i++) {
        cout << v[i].name << " " << v[i].work_age << " " << v[i].age << endl;
    }
}

int main() {
    vector<Employee> v;
    string na; int wa, ag;
    while(cin >> na >> wa >> ag) {
        Employee e;
        e.name = na;
        e.work_age = wa;
        e.age = ag;
        v.push_back(e);
    }
    //quickSort(v,0,v.size()-1);
    bubleSort(v);
    output(v);
    return 0;
}
