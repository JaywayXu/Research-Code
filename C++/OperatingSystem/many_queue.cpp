#include <iostream>
using namespace std;

const int Q = 7;

class PCB {
public:
    string name;
    int need;
    int turn;
    PCB *next;
    PCB(string t_name, int t_need, int t_turn):name(t_name), need(t_need), turn(t_turn), next(nullptr) {}
};

class RQ {
public:
    PCB *first;
    PCB *last;
    RQ():first(nullptr), last(nullptr) {}
    void load_RQ1() {
        PCB *temp = new PCB("P1",16,6);
        in(temp);
        temp = new PCB("P2",11,5);
        in(temp);
        temp = new PCB("P3",14,4);
        in(temp);
        temp = new PCB("P4",13,3);
        in(temp);
        temp = new PCB("P5",15,2);
        in(temp);
    }
    void load_RQ2() {
        PCB *temp = new PCB("P6",21,1);
        in(temp);
        temp = new PCB("P7",18,2);
        in(temp);
        temp = new PCB("P8",10,3);
        in(temp);
        temp = new PCB("P9",7,4);
        in(temp);
        temp = new PCB("P10",14,5);
        in(temp);
    }
    void in(PCB *temp) {
        if (!first) {
            first = temp;
            last = temp;
        } else {
            last->next = temp;
            last = temp;
        }
    }
    void sort() {
        PCB* pNode1 = first;
        PCB* pNode2 = first;
        if(first == nullptr)
            return;
        for(;pNode1->next!= nullptr;pNode1=pNode1->next)
        {
            for(pNode2=first;pNode2->next!= nullptr;pNode2=pNode2->next)
            {
                if(pNode2->need > pNode2->next->need)
                {
                    string t_name = pNode2->name;
                    int t_need = pNode2->need;
                    int t_turn = pNode2->turn;

                    pNode2->name = pNode2->next->name;
                    pNode2->need = pNode2->next->need;
                    pNode2->turn = pNode2->next->turn;

                    pNode2->next->name = t_name;
                    pNode2->next->need = t_need;
                    pNode2->next->turn = t_turn;
                }
            }
        }
    }
    void print() {
        PCB *temp = first;
        while (temp != nullptr) {
            cout << temp->name << ": " << temp->turn << endl;
            temp = temp->next;
        }
    }
};

int main() {
    int clock = 0;

    // input RQ1
    RQ rq1; rq1.load_RQ1();
    // input RQ2
    RQ rq2; rq2.load_RQ2();
    RQ final;
    PCB *pi;

    // run RQ1
    while (rq1.first != nullptr) {
        // select pi from RQ1 to run
        pi = rq1.first;
        // calculate t
        if (pi->need <= Q) { //if pi finished
            cout << "  -> " << pi->name << "(" << pi->need << ")";

            clock += pi->need;
            pi->need = 0;
            pi->turn += clock; // calculate pi's turn
            rq1.first = rq1.first->next;
            pi->next = nullptr;
            final.in(pi);
        } else {
            cout << "  -> " << pi->name << "(" << Q << ")";

            pi->need -= Q;
            clock += Q;
            rq1.first = rq1.first->next;
            pi->next = nullptr;
            rq1.in(pi);
        }
    }
    cout << endl;
    // run RQ2
    rq2.sort();
    //rq2.print();
    while (rq2.first != nullptr) {
        // select Pi from RQ2 to run
        pi = rq2.first;

        cout << "  -> " << pi->name << "(" << pi->need << ")";

        clock += pi->need;
        pi->need = 0;
        pi->turn += clock; // calculate pi's turn
        rq2.first = rq2.first->next;
        pi->next = nullptr;
        final.in(pi);
    }
    cout << endl;
    // print time
    final.print();
    return 0;
}