#include <iostream>
using namespace std;

typedef struct Node
{
    int data;
    struct Node *next;
} * LinkedList;

void InitList(LinkedList &L)
{
    L = new Node();
    L->data = -1;
    L->next = NULL;
    if (L == NULL)
    {
        cout << "initial fialed!\n";
    }
    Node *p = L;
    int a;
    cin >> a;
    while (a != 999)
    {
        Node *temp = new Node();
        temp->data = a;
        temp->next = NULL;
        p->next = temp;
        p = p->next;
        cin >> a;
    }
}

void printList(LinkedList L)
{
    Node *p = L->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int getLength(Node *L)
{
    int count = 0;
    Node *p = L->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

Node *findValue(LinkedList L, int val)
{
    Node *p = L->next;
    while (p != NULL)
    {
        if (val == p->data)
        {
            cout << "found it!\n";
            return p;
        }
        p = p->next;
    }
    cout << "can't find it!\n";
    return NULL;
}

//头插反转链表
void reverseList(LinkedList &L)
{
    Node *p = L->next;
    Node *post = NULL;
    L->next = NULL;
    while (p != NULL)
    {
        post = p->next;
        p->next = NULL;
        p->next = L->next;
        L->next = p;
        p = post;
    }
}

int main()
{
    int n;
    LinkedList L;
    InitList(L);
    cout << "old list:";
    printList(L);
    cout << "number of node: " << getLength(L) << endl;
    cout << "input value:";
    cin >> n;
    findValue(L, n);
    cout << "reversed list:";
    reverseList(L);
    printList(L);
    return 0;
}
