//
// Created by trol_ on 2016/8/30.
//

//#include <stdio.h>
//#include <stdlib.h>
//typedef char TelemType;
//
//typedef struct BinTree{
//    TelemType data;
//    struct BinTree *LChild;
//    struct BinTree *RChild;
//}BinaryTree;
//
/////对于这样定义的结构体，  用 "."进行访问，而不是用"->",
/////对于这个知识点有点忘记了
//typedef struct NodeStack{
//    BinaryTree *arr[100];
//    int tag[100];
//    int top;
//}NodeStack;
//
//typedef struct NodeQueue{
//    BinaryTree *arr[100];
//    int front;
//    int rear;
//}NodeQueue;
//
//void enqueue(NodeQueue *queue, BinaryTree *T)
//{
//    if(queue->rear == 100)
//        printf("the queue is full!\n");
//    else{
//        queue->arr[queue->rear] = T;
//        queue->rear++;
//    }
//}
//
//BinaryTree *dequeue(NodeQueue *queue)
//{
//    if(queue->front == queue->rear)
//        return NULL;
//    else{
//        queue->front++;
//        return queue->arr[queue->front-1];
//    }
//}
//
//void node_push(NodeStack *s, BinaryTree *T)
//{
//    if(s->top == 100)
//        printf("NodeStack is full!\n");
//    else{
//        s->top++;
//        s->arr[s->top] = T;
//    }
//}
//
//BinaryTree* pop(NodeStack *s)
//{
//    if(s->top == -1)
//        return NULL;
//    else{
//        s->top--;
//        return s->arr[s->top+1];
//    }
//}
//
//BinaryTree* create_BinaryTree(BinaryTree *T)
//{
//    TelemType tmp;
//    scanf("%c", &tmp);
//    if(tmp == '0')
//        return 0;
//
//    T = (BinaryTree*)malloc(sizeof(BinaryTree));
//    T->data = tmp;
//    T->LChild = create_BinaryTree(T->LChild);
//    T->RChild = create_BinaryTree(T->RChild);
//    return T;
//}
//
//// 计算叶子节点的个数
//int sum_left(BinaryTree *T)
//{
//    int sum = 0, lnum, rnum;
//    if(T)
//    {
//        if((!T->LChild) && (!T->RChild))
//        {
//            sum++;
//        }
//        lnum = sum_left(T->LChild);
//        sum += lnum;
//        rnum = sum_left(T->RChild);
//        sum += rnum;
//    }
//    return sum;
//}
//
/////算法忘记了，复习
//void  non_recursion_preorder(BinaryTree *T)
//{
//    NodeStack stack;
//    stack.top = -1;
//    if(!T){
//        printf("the tree is empty/n");
//    }else{
//        while(T || stack.top != -1)
//        {
//            while(T)
//            {
//                printf("%c ", T->data);
//                node_push(&stack, T);
//                T = T->LChild;
//            }
//            T = pop(&stack);
//            T = T->RChild;
//        }
//    }
//}
//
/////算法忘记了，复习
//void non_recursion_inorder(BinaryTree *T)
//{
//    NodeStack stack;
//    stack.top = -1;
//    if(!T)
//        printf("the tree is empty!");
//    else{
//        while(T || stack.top != -1)
//        {
//
//            node_push(&stack, T);
//            T = T->LChild;
//        }
//        T = pop(&stack);
//        printf("%c ", T->data);
//        T = T->RChild;
//    }
//}
//
/////算法忘记了，复习
//void non_recursion_postorder(BinaryTree *T)
//{
//    NodeStack stack;
//    stack.top = -1;
//    if(!T)
//        printf("the tree is empty!\n");
//    else{
//        while(T || stack.top != -1)
//        {
//            node_push(&stack, T);
//            stack.tag[stack.top] = 0; ///设置访问标记，0为第一次访问，1为第二次访问
//            T = T->LChild;
//        }
//        if(stack.tag[stack.top] == 0)
//        {
//            T = stack.arr[stack.top];
//            stack.tag[stack.top] = 1;
//            T = T->RChild;
//        } else {
//            while(stack.arr[stack.top]->data == 1)
//            {
//                T = pop(&stack);
//                printf("%c ", T->data);
//            }
//            T = NULL;  ///必须将T置空，跳过向左走，直接向右走
//        }
//    }
//}
//
/////算法忘记了，复习
//void level_traverse(BinaryTree *T)
//{
//    NodeQueue queue;
//    BinaryTree* tmp;
//    queue.front = queue.rear = 0;
//    if(!T)
//    {
//        printf("the tree is empty!\n");
//        return;
//    }
//    enqueue(&queue, T);
//    while(queue.front != queue.rear)
//    {
//        T = dequeue(&queue);
//        printf("%c ", T->data);
//        if(T->LChild)
//            enqueue(&queue, T->LChild);
//
//        if(T->RChild)
//            enqueue(&queue, T->RChild);
//    }
//}
//
//void preorder_traverse(BinaryTree *T)
//{
//
//    if(T == NULL)
//        return ;
//    if(T)
//    {
//        printf("%c ", T->data);
//        preorder_traverse(T->LChild);
//        preorder_traverse(T->RChild);
//    }
//}
//
//void inorder_traverse(BinaryTree *T)
//{
//    if(T)
//    {
//        inorder_traverse(T->LChild);
//        printf("%c ", T->data);
//        inorder_traverse(T->RChild);
//    }
//}
//
//void postorder_traverse(BinaryTree *T)
//{
//
//    if(T)
//    {
//        postorder_traverse(T->LChild);
//        postorder_traverse(T->RChild);
//        printf("%c ", T->data);
//    }
//}
//
//int is_equal(BinaryTree *T1, BinaryTree *T2)
//{
//    if(!T1 && !T2)
//    {
//        return 1; ///都空判相等
//    }
//    if(T1 && T2 && T1->data == T2->data)
//    {
//        if(is_equal(T1->LChild, T2->LChild))
//        {
//            if(is_equal(T1->RChild, T2->RChild)){
//                return 1;
//            }
//        }
//    }
//    return  0;
//}
//
//void destroyBinaryTree(BinaryTree *tree)
//{
//    if(tree == NULL)
//        return;
//    destroyBinaryTree(tree->LChild);
//    destroyBinaryTree(tree->RChild);
//    free(tree);
//    tree = NULL;  ///free(T)仅仅收回内存，不会改变T的指向。
//    ///T=NULL是为了防止下面的代码使用这个已经收回的空间
//}
//
//BinaryTree* get_tree_node(TelemType item, BinaryTree *ltree, BinaryTree *rtree)
//{
//    BinaryTree *T;
//    T = (BinaryTree*)malloc(sizeof(BinaryTree));
//    T->data = item;
//    T->LChild = ltree;
//    T->RChild = rtree;
//    return T;
//}
//
/////算法忘记了，复习
//BinaryTree* copy_tree(BinaryTree *T)
//{
//    if(!T)
//        return NULL;
//    BinaryTree *newltree, *newrtree, *newT;
//    if(T->LChild)
//        newltree = copy_tree(T->LChild);
//    else
//        newltree = NULL;
//    if(T->RChild)
//        newrtree = copy_tree(T->RChild);
//    else
//        newrtree = NULL;
//    newT = get_tree_node(T->data, newltree, newrtree);
//    return newT;
//}
//
//int max(int n1, int n2)
//{
//    return (n1 > n2) ? n1 : n2;
//}
//
//int get_deep(BinaryTree *T)
//{
//    int dep = 0, ldep, rdep;
//    if(!T)
//        dep = 0;
//    else
//    {
//        ldep = get_deep(T->LChild);
//        rdep = get_deep(T->RChild);
//        dep = 1 + max(ldep, rdep);
//    }
//}
//
//int main()
//{
//    BinaryTree *bin_tree, *tree;
//    bin_tree = create_BinaryTree(bin_tree);
//    printf("+++++++++++++++++++++++++++++\n");
//    //preorder_traverse(bin_tree);
//    non_recursion_preorder(bin_tree);
//    puts("");
//    level_traverse(bin_tree);
//    puts("");
//    non_recursion_inorder(bin_tree);
//    inorder_traverse(bin_tree);
//    puts("");
//    non_recursion_postorder(bin_tree);
//    postorder_traverse(bin_tree);
//    puts("");
//    printf("left_node is %d\n", sum_left(bin_tree));
//    printf("The tree deep is %d\n", get_deep(bin_tree));
//    tree = copy_tree(bin_tree);
//    preorder_traverse(tree);
//
//    if(is_equal(bin_tree, tree) == 1)
//    {
//        printf("is equal!\n");
//    }
//    //destroyBinaryTree(tree);
//
//    return 0;
//}



//#include <stdio.h>
//#include <stdlib.h>
//typedef char Telemtype;
//typedef struct BinTree{
//    Telemtype data;
//    struct BinTree *LChild;
//    struct BinTree *RChild;
//}BinaryTree;
//
//BinaryTree* create_tree(BinaryTree *Tree)
//{
//    Telemtype tmp;
//    scanf("%c", &tmp);
//
//    if(tmp == '0')
//        return 0;
//    Tree = (BinaryTree*)malloc(sizeof(BinaryTree));
//    Tree->data = tmp;
//    Tree->LChild = create_tree(Tree->LChild);
//    Tree->RChild = create_tree(Tree->RChild);
//    return Tree;
//}
//
//void preorder_traverse(BinaryTree *tree)
//{
//    if(tree)
//    {
//        printf("%c *", tree->data);
//        preorder_traverse(tree->LChild);
//        preorder_traverse(tree->RChild);
//    }
//}
//
//void inorder_traverse(BinaryTree *tree)
//{
//    if(tree)
//    {
//        inorder_traverse(tree->LChild);
//        printf("%c ", tree->data);
//        inorder_traverse(tree->RChild);
//    }
//}
//
//int max(int a, int b)
//{
//    return (a > b) ? a : b;
//}
//
//int tree_deep(BinaryTree *tree)
//{
//    int deep = 0, rdeep, ldeep;
//    if(tree)
//    {1
//        ldeep = tree_deep(tree->LChild);
//        rdeep = tree_deep(tree->RChild);
//        deep = 1 + max(ldeep, rdeep);
//    }
//    return deep;
//}
//
//int tree_doubleson(BinaryTree *tree)
//{
//    int cnt = 0;
//    if(tree)
//    {
//        if(tree->LChild!=NULL && tree->RChild != NULL)
//        {
//            cnt++;
//        }
//        cnt += tree_doubleson(tree->LChild);
//        cnt += tree_doubleson(tree->RChild);
//    }
//    return cnt;
//}
//
//int main()
//{
//    BinaryTree *tree;
//    tree = create_tree(tree);
//    preorder_traverse(tree);
//    inorder_traverse(tree);
//    printf("树的深度是  %d\n", tree_deep(tree));
//    printf("%d\n", tree_doubleson(tree));
//    return 0;
//}
