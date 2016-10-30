#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct ListNode{
    struct ListNode* next;
    ElemType data;
}*LiskList, ListNode;

//  初始化链表
LiskList init_list(LiskList &list)
{
    list->next = NULL;
    list->data = 0;
    return list;
}

// * 建立链表
// * 头插法
// * 王道 P.27
// *

LiskList create_list(LiskList &list)
{
    ListNode *n_node;
    ElemType x;
    list = (LiskList)malloc(sizeof(ListNode));
    list->next = NULL;
    list->data = 0;
    scanf("%d", &x);
    while(x != 9999)                             ///输入9999表示结束
    {
        n_node = (LiskList)malloc(sizeof(ListNode));
        n_node->data = x;

        n_node->next = list->next;               ///核心的地方
        list->next = n_node;
        scanf("%d", &x);
    }
    return list;
}


// * 尾插法
// * 王道 P.28
// *

LiskList create_list2(LiskList &list)
{
    ElemType x;
    list = (LiskList)malloc(sizeof(ListNode));
    ListNode *n_node, *rear = list;             ///rear 指向链表尾
    list->next = NULL;
    list->data = 0;
    scanf("%d", &x);
    while(x != 9999)                            ///输入9999表示结束
    {
        n_node = (LiskList)malloc(sizeof(ListNode));
        n_node->data = x;

        rear->next = n_node;                    ///核心的地方
        rear = n_node;
        scanf("%d", &x);
    }
    rear->next = NULL;
    return list;
}


// * 打印链表的信息
// *

void show_list(LiskList list)
{
    printf("\nshow list\n");
    //因为加了头结点，所以跳过头结点
    list = list->next;
    while(list != NULL)
    {
        printf("%d ", list->data);
        list = list->next;
    }
    return;
}


// * 按序号查找结点的值
// * 王道 P.28
// *

ListNode* get_elem(LiskList list, int i)
{
    int j = 1;
    ListNode* tmp = list->next;
    if(i == 0)
        return list;
    if(i < 0)
        return NULL;
    while(tmp && i > j)
    {
        tmp = tmp->next;
        j++;
    }
    return tmp;
}

// * 按值查找表结点
// * 王道 P.29
// *

ListNode* locate_elem(LiskList list, ElemType x)
{
    ListNode* tmp = list->next;
    while(tmp && tmp->data != x)
        tmp = tmp->next;
    return tmp;
}


// * 在指定位置上插入一个结点，返回当且要插入结点的指针
// * 王道 P.29
// *

ListNode* insert_node(LiskList &list, int position, ElemType x)
{
    int i = 1;
    ListNode* p = list->next;
    while(i < position)
    {
        p = p->next;
        i++;
    }
    ListNode* tmp = (LiskList)malloc(sizeof(ListNode));
    tmp->data = x;
    tmp->next = p->next;                                    //这是核心
    p->next = tmp;
    return tmp;
}

// * 删除一个结点
// * 王道 P.30
// *

ElemType delete_node(LiskList &list, int position)
{
    int i = 1;
    ListNode* p = list->next;
    ListNode* pre = list;

    while(i < position)
    {
        pre = p;
        p = p->next;
        i++;
    }
    i = p->data;
    pre->next = p->next;
    free(p);
    return i;
}

// * 求链表的长度
// * 王道 P.31
// *


int list_length(LiskList list)
{
    int len = 0;
    ListNode* tmp = list->next;
    while(tmp)
    {
        tmp = tmp->next;
        len++;
    }
    return len;
}

int main()
{
    LiskList list;
    //list = create_list(list);
    list = create_list2(list);
    show_list(list);

    ListNode* get_elem1 = get_elem(list, 3);
    printf("\n%d \n", get_elem1->data);

    ListNode* locate_elem1 = locate_elem(list, 4);
    printf("\nthis is a pointer : %d\n", locate_elem1->data);

    insert_node(list, 3, 9999);
    show_list(list);

    delete_node(list, 3);
    show_list(list);

    printf("\nthe list`s length is %d\n", list_length(list));
    
    return 0;
}

