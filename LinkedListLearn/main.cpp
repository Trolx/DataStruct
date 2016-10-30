#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct ListNode{
    struct ListNode* next;
    ElemType data;
}*LinkList, ListNode;

//  初始化链表
LinkList init_list(LinkList &list)
{
    list->next = NULL;
    list->data = 0;
    return list;
}

// * 建立链表
// * 头插法
// * 王道 P.27
// *

LinkList create_list(LinkList &list)
{
    ListNode *n_node;
    ElemType x;
    list = (LinkList)malloc(sizeof(ListNode));
    list->next = NULL;
    list->data = 0;
    scanf("%d", &x);
    while(x != 9999)                             ///输入9999表示结束
    {
        n_node = (LinkList)malloc(sizeof(ListNode));
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

LinkList create_list2(LinkList &list)
{
    ElemType x;
    list = (LinkList)malloc(sizeof(ListNode));
    ListNode *n_node, *rear = list;             ///rear 指向链表尾
    list->next = NULL;
    list->data = 0;
    scanf("%d", &x);
    while(x != 9999)                            ///输入9999表示结束
    {
        n_node = (LinkList)malloc(sizeof(ListNode));
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

void show_list(LinkList list)
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

ListNode* get_elem(LinkList list, int i)
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

ListNode* locate_elem(LinkList list, ElemType x)
{
    ListNode* tmp = list->next;
    while(tmp && tmp->data != x)
        tmp = tmp->next;
    return tmp;
}


// * 在指定位置上插入一个结点，返回当且要插入结点的指针
// * 王道 P.29
// *

ListNode* insert_node(LinkList &list, int position, ElemType x)
{
    int i = 1;
    ListNode* p = list->next;
    while(i < position)
    {
        p = p->next;
        i++;
    }
    ListNode* tmp = (LinkList)malloc(sizeof(ListNode));
    tmp->data = x;
    tmp->next = p->next;                                    //这是核心
    p->next = tmp;
    return tmp;
}

// * 删除一个结点
// * 王道 P.30
// *

ElemType delete_node(LinkList &list, int position)
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

// * 求链表的=长度
// * 王道 P.31
// *

int list_length(LinkList list)
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
/*
 * swap function
 * 用来交换两个结点的信息
 * */
void swap(ListNode *n1, ListNode *n2)
{
    ElemType  tmp;
    tmp = n1->data;
    n1->data = n2->data;
    n2->data = tmp;
}
/*
 * 单链表的插入排序
 * http://www.cnblogs.com/Camilo/p/3927912.html
 * 基本思想：假设前面n-1个结点有序，将第n个结点插入到前面结点的适当位置，使这n个结点有序。
 * 实现方法：
 * 将链表上第一个结点拆下来，成为含有一个结点的链表(head1)，其余的结点自然成为另外一个链表(head2)，此时head1为含有一个结点的有序链表；
 * 将链表head2上第一个结点拆下来，插入到链表head1的适当位置，使head1仍有序，此时head1成为含有两个结点的有序链表；
 * 依次从链表head2上拆下一个结点，插入到链表head1中，直到链表head2为空链表为止。最后，链表head1上含所有结点，且结点有序。
 * */
LinkList insert_sort(LinkList list)
{
    ListNode *list2, *current, *p, *q;
    if(!list || !(list->next))
        return  list;

    //第一次拆分
    list2 = list->next;
    list->next = NULL;

    while(list2)
    {
        current = list2;
        list2 = list2->next;
        //寻找插入位置，插入位置为p和q之间
        for(p = NULL, q = list; q && q->data <= current->data; p = q, q = q->next);

        if(q == list)
            list = current;  //current插入到最前面
        else
            p->next = current;

        current->next = q;
    }
    return list;
}

/*
 * 单链表冒泡排序
 * 还是自己理解的东西，写自己的风格超级舒服
 * */
LinkList bubble_sort(LinkList list)
{
    if(!list || !(list->next))
        return  list;
    ListNode *p, *q;
    for(p = list; p != NULL; p = p->next)
    {
        for(q = p; q->next != NULL; q = q->next)
        {
            if(q->data > q->next->data)
                swap(q, q->next);
        }
    }
    return list;
}

int main()
{
    LinkList list;
    //list = create_list(list);
    list = create_list2(list);
    show_list(list);

//    ListNode* get_elem1 = get_elem(list, 3);
//    printf("\n%d \n", get_elem1->data);
//
//    ListNode* locate_elem1 = locate_elem(list, 4);
//    printf("\nthis is a pointer : %d\n", locate_elem1->data);
//
//    insert_node(list, 3, 9999);
//    show_list(list);
//
//    delete_node(list, 3);
//    show_list(list);

    printf("\nthe list`s length is %d\n", list_length(list));

    //bubble_sort(list);
    insert_sort(list);
    show_list(list);

    return 0;
}


