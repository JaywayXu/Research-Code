# include <stdio.h>
using namespace std;

struct list_node{
    int val;
    struct list_node * next;
};


list_node * input_list(void)
{
    int n, val;
    list_node * phead = new list_node();
    list_node * cur_pnode = phead;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &val);
        if (i == 1) {
            cur_pnode->val = val;
            cur_pnode->next = NULL;
        }
        else {
            list_node * new_pnode = new list_node();
            new_pnode->val = val;
            new_pnode->next = NULL;
            cur_pnode->next = new_pnode;
            cur_pnode = new_pnode;
        }
    }
    return phead;
}


list_node * relocate(list_node * head)
{
    //////在下面完成代码
    int num = 0;
    list_node * cur_pnode = head;
    while (cur_pnode) {
        num++;
        cur_pnode = cur_pnode->next;
    }
    int half = (num%2==0)?num/2:num/2;
    
    list_node *half_node = head;
    for (int i=1; i<=half; i++) {
        half_node = half_node->next;
    }
    for (int i=1; i<half; i++) {
        list_node *move_node = head->next;
        head->next = move_node->next;
        move_node->next = half_node->next;
        half_node->next = move_node;
        half_node = move_node->next;
    }
    return head;
}


void print_list(list_node * head)
{
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    puts("");
}


int main ()
{
    list_node * head = input_list();
    list_node * new_head = relocate(head);
    print_list(new_head);
    return 0;
}