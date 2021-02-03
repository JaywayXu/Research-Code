#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

struct Node
{
    Node(int id, char input, int nextId)
    {
        this->id = id;
        this->input = input;
        this->nextId = nextId;
    }
    int id;
    char input;
    int nextId;
};

class MyClass
{
public:
    MyClass() {
        strExpress = "";
        statusId = 0;
    }

    MyClass(string str)
    {
        strExpress = str;
    }

    void printNFA();
    void strToNFA();

private:
    string strExpress;
    int statusId;
    vector<Node*> map;
};

void MyClass::strToNFA()
{
    stack<int> s_st;
    stack<int> s_ed;
    stack<char> s_str;

    s_str.push('$');
    s_st.push(statusId++);
    s_ed.push(statusId++);

    for(auto i=strExpress.begin(); i!=strExpress.end(); ++i)
    {
        char ch = *i;
        cout<<ch;
        switch (ch)
        {
            case '(':
            {
                s_ed.push(statusId++);
                s_str.push('(');
                break;
            }
            case ')':
            {
                int ed = s_ed.top();
                int st = s_st.top();
                map.push_back(new Node(st, '-', ed));
                ch = s_str.top();
                while(ch != '(')
                {
                    int nxt = s_st.top();
                    s_st.pop();
                    int pre = s_st.top();
                    if(ch != '#')
                        map.push_back(new Node(pre, ch, nxt));
                    s_str.pop();
                    ch = s_str.top();
                }
                s_str.pop();
                s_str.push('#');
                int top_num = s_ed.top();
                s_st.push(top_num);
                s_ed.pop();
                break;
            }
            case '|':
            {
                int ed = s_ed.top();
                int st = s_st.top();
                map.push_back(new Node(st, '-', ed));
                ch = s_str.top();
                while(ch != '(' && ch != '$')
                {
                    int nxt = s_st.top();
                    s_st.pop();
                    int pre = s_st.top();
                    if(ch != '#')
                        map.push_back(new Node(pre, ch, nxt));
                    s_str.pop();
                    ch = s_str.top();
                }
                break;
            }
            case '*':
            {
                int nxt = s_st.top();
                s_st.pop();
                int pre = s_st.top();
                map.push_back(new Node(pre, '-', nxt));
                map.push_back(new Node(nxt, '-', pre));
                s_st.push(nxt);
                break;
            }
            default:
            {
                s_str.push(ch);
                s_st.push(statusId++);
                break;
            }
        }
    }
    char ch = s_str.top();
    while(ch != '$')
    {
        int nxt = s_st.top();
        s_st.pop();
        int pre = s_st.top();
        if(ch != '#')
            map.push_back(new Node(pre, ch, nxt));
        s_str.pop();
        ch = s_str.top();
    }
}

void MyClass::printNFA()
{
    cout<<"NFA£º"<<endl;
    for(auto node : map)
    {
        cout<<node->id<<"--["<<node->input<<"]-->"<<node->nextId<<endl;
    }
}

int main()
{
    string str;
    stack<int> s;
//    cin>>str;
    str = "ab*(a*|(ab)*|b)*b";

    MyClass myclass(str);
    myclass.strToNFA();
    myclass.printNFA();

    return 0;
}