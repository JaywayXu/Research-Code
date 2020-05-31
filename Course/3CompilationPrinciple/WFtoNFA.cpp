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
    MyClass()
    {
        strExpress = "";
        statusId = 0;
    }

    MyClass(string str)
    {
        strExpress = str;
        statusId = 0;
    }

    bool is_c = false;
    void printNFA();
    void strToNFA();
    void change();

private:
    string strExpress;
    int statusId;
    vector<Node *> map;
};

void MyClass::strToNFA()
{
    stack<int> s_st;
    stack<int> s_ed;
    stack<char> s_str;

    s_str.push('$');
    s_st.push(statusId++);
    s_ed.push(statusId++);

    for (auto i = strExpress.begin(); i != strExpress.end(); ++i)
    {
        char ch = *i;
        cout << ch;
        switch (ch)
        {
        case '(':
        {
            s_ed.push((statusId++) - 1);
            s_str.push('(');
            break;
        }
        case ')':
        {
            int ed = s_ed.top();
            int st = s_st.top();
            map.push_back(new Node(st, '-', ed));
            ch = s_str.top();
            while (ch != '(')
            {
                int nxt = s_st.top();
                s_st.pop();
                int pre = s_st.top();
                if (ch != '#')
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
            while (ch != '(' && ch != '$')
            {
                int nxt = s_st.top();
                s_st.pop();
                int pre = s_st.top();
                if (ch != '#')
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
            is_c = true;
            s_st.push(nxt);
            break;
        }
        default:
        {
            s_str.push(ch);
            s_st.push((statusId++) - 1);
            break;
        }
        }
    }
    char ch = s_str.top();
    while (ch != '$')
    {
        int nxt = s_st.top();
        s_st.pop();
        int pre = s_st.top();
        if (ch != '#')
            map.push_back(new Node(pre, ch, nxt));
        s_str.pop();
        ch = s_str.top();
    }
}

void MyClass::printNFA()
{
    cout << "  NFA:" << endl;
    for (auto node : map)
    {
        cout << node->id << " " << node->input << " " << node->nextId << endl;
    }
}

void MyClass::change()
{
    vector<int> fid, lid;
    vector<char> value;
    for (auto node : map)
    {
        fid.push_back(node->id);
        value.push_back(node->input);
        lid.push_back(node->nextId);
    }
    if (is_c)
    {
        for (int i = 0; i < fid.size() - 1; i++)
        {
            if (fid[i] == lid[i + 1] && fid[i + 1] == lid[i] && value[i] == value[i + 1])
            {
                char a = fid[i],b = lid[i];
                fid.erase(fid.begin()+i);
                value.erase(value.begin()+i);
                lid.erase(lid.begin()+i);
                fid.erase(fid.begin()+i);
                value.erase(value.begin()+i);
                lid.erase(lid.begin()+i);
                for (int i = 0; i < fid.size(); i++) {
                    if (fid[i] == b) fid[i] = a;
                    if (lid[i] == b) lid[i] = a;
                }
            }
        }
        for (int i=0; i<fid.size();i++) {
            if (fid[i] == lid[i] && value[i] == '-') {
                fid.erase(fid.begin()+i);
                lid.erase(lid.begin()+i);
                value.erase(value.begin()+i);
            }
        }
    }

    cout << endl;
    for (int i = 0; i < fid.size(); i++)
    {
        cout << fid[i] << " " << value[i] << " " << lid[i] << endl;
    }
    
}

int main()
{
    string str;
    cout << "输入正规式："
    cin>>str;
    // str = "a*x";
    cout<< "NFA为："
    MyClass myclass(str);
    myclass.strToNFA();
    // myclass.printNFA();
    myclass.change();

    return 0;
}
