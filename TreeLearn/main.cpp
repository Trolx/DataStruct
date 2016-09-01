///练练练
#include <stdio.h>
#include <stdlib.h>
typedef char Telemtype;
typedef struct BinTree{
    Telemtype data;
    struct BinTree *LChild;
    struct BinTree *RChild;
}BinaryTree;

/*
 * 建树是通过先序遍历的方法进行，先输如一个字符，如果不是‘0’，则进行
 * 树的创建，否则不建树
 * 树的创建需要有一下几个步骤
 * 1.给树根结点申请空间
 * 2.给根节点的数据域赋值
 * 3.递归的分别创建左右子树
 * */
BinaryTree* create_tree(BinaryTree *Tree)
{
    Telemtype tmp;
    scanf("%c", &tmp);
    if(tmp == '0')
        return 0;
    Tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    Tree->data = tmp;
    Tree->LChild = create_tree(Tree->LChild);
    Tree->RChild = create_tree(Tree->RChild);
    return Tree;
}

/*
 * 递归写法的几种树的遍历（先序，中序，后序），都一样
 * 但是这样的写法其实在其他操作中也类似，
 * 1.比如说进行统计节点个数
 * 2.树的销毁等等
 * 对于时间复杂度，因为每个节点均遍历一次，所以复杂度为O(n)
 * */
void preorder_traverse(BinaryTree *tree)
{
    if(tree)
    {
        printf("%c ", tree->data);
        preorder_traverse(tree->LChild);
        preorder_traverse(tree->RChild);
    }
}

void inorder_traverse(BinaryTree *tree)
{
    if(tree)
    {
        inorder_traverse(tree->LChild);
        printf("%c ", tree->data);
        inorder_traverse(tree->RChild);
    }
}

void postorder_traverse(BinaryTree *tree)
{
    if(tree)
    {
        postorder_traverse(tree->LChild);
        postorder_traverse(tree->RChild);
        printf("%c ", tree->data);
    }
}

/*
 * 统计叶子节点的个数
 * 1.先看当前节点是否是叶子节点，如果是叶子节点，sum值加一
 * 2.然后递归的分别统计左右子树中拥有的叶子节点的个数
 * */
int sum_left(BinaryTree *tree)
{
    int sum = 0;
    if(tree)
    {
        if(!tree->LChild && !tree->RChild)
            sum ++;
        if(tree->LChild)
            sum += sum_left(tree->LChild);
        if(tree->RChild)
            sum += sum_left(tree->RChild);
    }
    return sum;
}
/*
 * 1.如果两颗树是空树，则两颗树相等
 * 2.否则，判断当前树的根节点是否相等
 * 3.然后再递归的判断左右子树
 * 4.如果都相同，发回1.否则返回0
 * */
int is_equal(BinaryTree *T1, BinaryTree *T2)
{
    if(!T1 && !T2)
    {
        return 1;
    }
    if(T1 && T2 && T1->data == T2->data)
        if(is_equal(T1->LChild, T2->LChild))
            if(is_equal(T1->RChild, T2->RChild))
                return 1;
    return 0;
}
/*
 * 思路同后序遍历
 * 1.先销毁左右子树
 * 2.然后释放当前根节点的空间
 * 3.将指针的指向   指到NULL
 * Note：free(tree)仅仅收回内存，不会改变T的指向。
 * */
void destory_tree(BinaryTree *tree)
{
    if(tree == NULL)
        return;
    destory_tree(tree->LChild);
    destory_tree(tree->RChild);
    free(tree);
    tree = NULL;
    return;
}

/*
 * 树的复制包含两部分，一部分是，为要根节点设置值和要指向的左右子树
 * 第二部分就是递归的复制左右子树
 * 左右子树的复制，还是同后序遍历
 * */
BinaryTree *get_tree_node(Telemtype item, BinaryTree *LChild, BinaryTree *RChild)
{
    BinaryTree *tree;
    tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->data = item;
    tree->LChild = LChild;
    tree->RChild = RChild;
    return tree;
}

BinaryTree* copy_tree(BinaryTree *tree)
{
    BinaryTree *newLChild, *newRChild, *newtree;
    if(!tree)
        return NULL;
    if(tree->LChild)
        newLChild = copy_tree(tree->LChild);
    else
        newLChild = NULL;

    if(tree->RChild)
        newRChild = copy_tree(tree->RChild);
    else
        newRChild = NULL;

    newtree = get_tree_node(tree->data, newLChild, newRChild);
    return newtree;
}

/*
 * 非递归的遍历就要用到 Stack & Queue
 * 1.Stack的初始化  stack.top = -1;
 * 2.Queue的初始化  queue.front = queue.rear = 0;
 * */
typedef struct TreeStack{
    BinaryTree *stroe[1000];
    int tag[1000];          //后序遍历要用到的标志域
    int top;
}Tstack;
/*
 *1.压栈操作，top+1 然后在当前位置存放节点信息
 *2.出栈操作，返回当前栈顶元素，然后top-1
 * */
void push_stack(Tstack *stack, BinaryTree *tree)
{
    if(stack->top == 1000)
        printf("the stack is full!\n");
    else{
        stack->top++;
        stack->stroe[stack->top] = tree;
    }
}

BinaryTree* pop_stack(Tstack *stack)
{
    if(stack->top == -1)
        return NULL;
    else{
        stack->top--;
        return stack->stroe[stack->top+1];
    }
}

typedef  struct TreeQueue{
    BinaryTree *stroe[1000];
    int front;
    int rear;
}Tqueue;
/*
 * 入队，出队比较简单
 * */
void enqueue(Tqueue *queue, BinaryTree *tree)
{
    if(queue->rear == 1000)
        printf("the queue is full!\n");
    else{
        queue->stroe[queue->rear] = tree;
        queue->rear++;
    }
}

BinaryTree* dequeue(Tqueue *queue)
{
    if(queue->front == queue->rear)
        return NULL;
    else{
        queue->front++;
        return queue->stroe[queue->front-1];
    }

}
/*
 * Note: 请先参照中序遍历，中序遍历是教科书说法，比较准确
 * 先序遍历的非递归算法和中序遍历的非递归算法类似
 * 1.先访问当前根结点，并将根结点入栈，往左走
 * 2.当当前节点没有左孩子时，将当前结点出栈，并访问他的右孩子
 * 3.一直循环，直到栈空
 * */
void non_recursion_preorder(BinaryTree *tree)
{
    Tstack stack;
    stack.top = -1;
    if(!tree)
        printf("the tree is empty!\n");
    else{
        while(tree || stack.top != -1)
        {
            if(tree)
            {
                printf("%c ", tree->data);
                push_stack(&stack, tree);
                tree = tree->LChild;
            }else{
                tree = pop_stack(&stack);
                tree = tree->RChild;
            }
            /*
             while(tree)                        //类似于中序遍历
             {
                printf("%c ", tree->LChild);
                push_stack(&stack, tree);
                tree = tree->LChild;
             }
                tree = pop_stack(&stack);
                tree = tree->RChild;
             * */
        }
    }
}

/*
 * 1.先扫描（并非访问）根结点的所有左结点并将他们一一进栈
 * 2.当当前结点没有左子树（或者做孩子结点已经访问过），将其出栈，访问他
 * 3.然后扫描该结点的右孩子结点，将其进栈，再扫描右孩子结点的所有左结点并一一进栈，如此继续，直到栈空
 * */
void non_recursion_inorder(BinaryTree *tree)
{
    Tstack stack;
    stack.top = -1;
    if(!tree)
    {
        printf("the tree is empty!\n");
    }else {
        while(tree || stack.top != -1)  //树根节点不空，或者栈不空时
        {
            if(tree){
                push_stack(&stack, tree);   //根结点进栈，遍历左子树
                tree = tree->LChild;        //每次遇到非空的左子树，就往左走
            }else{
                tree = pop_stack(&stack);   //根指针退栈，访问根节点，遍历右子树
                printf("%c ", tree->data);
                tree = tree->RChild;
            }

            /*
             while(tree)                     //另外一种好的写法，只要有左子树，就往左走
             {
                 push_stack(&stack, tree);   //根结点进栈，遍历左子树
                 tree = tree->LChild;        //每次遇到非空的左子树，就往左走
             }
             tree = pop_stack(&stack);       //根指针退栈，访问根节点，遍历右子树
             printf("%c ", tree->data);
             tree = tree->RChild;
             * */
        }
    }
}

/*
 * 后序遍历是先访问左右子树，最后访问根结点。
 * 当用栈来存储结点时，必须分清返回根结点时，是从左结点返回的，还是从右结点返回的
 * 用辅助指针可以写（也可以在结点中增加一个标志域）
 * 1.从根结点一直向左走，直到没有左子树
 * 2.转向向右走，先取栈顶指针
 * 3.判断是否有右子树
 *    4.若存在右子树且右子树是否被访问过，转向右子树，将右子树根结点压栈，继续走到最左边
 *    5.不满足4，弹出当前根结点，进行访问，并做标记，将tmp置空,必须将tmp置空，跳过向左走，直接向右走
 *
 * Note:当访问一个结点 *tmp时，栈中的结点恰好是*tmp结点的所有祖先。
 *      从栈底到栈顶结点再加上*tmp结点，刚好构成从根结点到*tmp的一条路径
 *      在很多算法设计中都用到了这一特行，比如：
 *                *求根结点到某结点的路径
 *                *求两个结点的最近公共祖先
 * */

void non_recursion_postorder(BinaryTree *tree)
{
    Tstack stack;
    stack.top = -1;
    BinaryTree *tmp = tree;
    BinaryTree *tag = NULL;
    while(tmp || stack.top != -1)
    {
        if(tmp)                                    //走到最左边
        {
            push_stack(&stack, tmp);
            tmp = tmp->LChild;
        }else{                                      //向右走
            tmp = pop_stack(&stack);                //取栈顶元素  这里应该是获取栈顶元素，但是不能出栈  王道 P.128
            push_stack(&stack, tmp);
            if(tmp->RChild && tmp->RChild != tag)   //如果右子树存在，且未被访问过
            {
                tmp = tmp->RChild;                  //转向右子树
                push_stack(&stack, tmp);            //压栈
                tmp = tmp->LChild;                  //继续走到最左边
            }else{                                  //如果右子树不存在，或者已经访问过
                tmp = pop_stack(&stack);            //弹出当前的根结点
                printf("%c ", tmp->data);           //进行访问
                tag = tmp;                          //标记访问过
                tmp = NULL;                         //访问过后，重置tmp指针,必须将tmp置空，跳过向左走，直接向右走
            }
        }
    }
}

//后序遍历的标记数据域标记写法,
void non_recursion_postorder2(BinaryTree *tree)
{
    Tstack stack;
    stack.top = -1;
    if(!tree)
        printf("the tree is empty!\n");
    else{
        while(tree || stack.top != -1) {
            while (tree) {
                push_stack(&stack, tree);
                stack.tag[stack.top] = 0;       //设置访问标记，0为第一次访问，1为第二次访问
                tree = tree->LChild;
            }
            if (stack.tag[stack.top] == 0)       //第一次访问时，转向同层右结点
            {
                tree = stack.stroe[stack.top];  //左走到底时，tree是空，必须有这句话
                stack.tag[stack.top] = 1;
                tree = tree->RChild;
            } else {
                while (stack.tag[stack.top] == 1)//在栈中找到下一个第一次范格纹你的结点，退出循环时并没有pop，所以为其左子结点
                {
                    tree = pop_stack(&stack);
                    printf("%c ", tree->data);
                }
                tree = NULL;
            }
        }
    }
}

/*
 * 层次遍历，其实就是BFS  （广度优先搜索）
 * */
void levelorder(BinaryTree *tree)
{
    Tqueue queue;
    queue.front = queue.rear = 0;
    enqueue(&queue, tree);              //根结点入队
    while(queue.front != queue.rear) {  //队列不为空时，循环
        tree = dequeue(&queue);         //队头元素出队
        printf("%c ", tree->data);      //访问当前结点
        if (tree->LChild != NULL)
            enqueue(&queue, tree->LChild);
        if (tree->RChild != NULL)
            enqueue(&queue, tree->RChild);
    }
}
/*
 * 层次遍历的应用，将树自下而上，自右向左遍历，
 * 就是把层次遍历访问的结点入栈，然后从栈弹出的顺序
 * 王道 P.128
 * */
void invert_levelorder(BinaryTree *tree)
{
    Tqueue queue;
    Tstack stack;
    if(tree != NULL)
    {
        stack.top = -1;
        queue.front = queue.rear = 0;
        enqueue(&queue, tree);              //根结点入队
        while(queue.front != queue.rear) {
            tree = dequeue(&queue);
            push_stack(&stack, tree);      //当前结点 入栈
            if (tree->LChild != NULL)
                enqueue(&queue, tree->LChild);
            if (tree->RChild != NULL)
                enqueue(&queue, tree->RChild);
        }

        while(stack.top != -1)
        {
            tree = pop_stack(&stack);
            printf("%c ", tree->data);
        }
    }
}
/*
 * 王道 第五题 P.129 通过层次遍历获得树的深度
 * */
int tree_depth(BinaryTree *tree)
{
    if(!tree)
        return 0;
    Tqueue queue;
    queue.front = queue.rear = 0;
    int last = 1, level = 0;        //last指向下一层的第一个结点
    enqueue(&queue, tree);          //根结点入队
    while(queue.front != queue.rear)
    {
        tree = dequeue(&queue);
        if(tree->LChild)
            enqueue(&queue, tree->LChild);
        if(tree->RChild)
            enqueue(&queue, tree->RChild);
        //好好理解这里
        if(queue.front == last)     //处理该层的最右结点
        {
            level++;                //层数加一
            last = queue.rear;      //last指向下层
        }
    }
    return level;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
/*
 * 统计树的深度，同后序遍历
 * 1.如果树空，深度为零
 * 2.否则分别递归求解左右子树的深度
 * 3.树的深度为 1+左右子树中更大的深度
 * */
int tree_depth2(BinaryTree *tree)
{
    int d = 0, dl, dr;
    if(!tree)
        d = 0;
    else
    {
        dl = tree_depth2(tree->LChild);
        dr = tree_depth2(tree->RChild);
        d = 1 + max(dl, dr);
    }
    return d;
}

/*
 * 下面这种写法，牛逼666
 * NOTE: 关键的地方还是区间划分
 * */
BinaryTree* pre_in_create_tree2(Telemtype A[], Telemtype B[], int start1, int end1, int start2, int end2)
{
    if(start1 > end1 || start2 > end2)
        return NULL;
    BinaryTree *tree;
    tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->data = A[start1];                                         //根结点
    for(int i = start2; i <=end2; i++)                       //根结点在中序中的划分
    {
        if(A[start1] == B[i]) {
            tree->LChild = pre_in_create_tree2(A, B, start1 + 1, start1 + i - start2, start2, i - 1);
            tree->RChild = pre_in_create_tree2(A, B, i - start2 + start1 + 1, end1, i + 1, end2);
        }
    }
    return tree;
}

/*
 * 由先序和中序遍历，来唯一确定一棵二叉树
 * 1.根据先序序列确定树的根结点
 * 2.根据根结点在中序遍历中划分左右子树，然后根据左右子树结点在先序序列中的次序，可以确定子树的根结点，（即回到第一步）
 * 王道书上 P.130 第六题
 * */
BinaryTree* pre_in_create_tree(Telemtype A[], Telemtype B[], int startPre, int endPre, int startIn, int endIn)
{
    int i;
    BinaryTree *tree;
    tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->data = A[startPre];
    for(i = startIn; B[i]!=tree->data; ++i);
    int LChild_len = i - startIn;                                    //左子树的长度
    int RChild_len = endIn - i;                                      //右子树的长度

    if(LChild_len)                                                  //递归建立左子树
        tree->LChild = pre_in_create_tree(A, B, startPre+1, startPre+LChild_len, startIn, startIn+LChild_len-1);   //划分的区间，是值得注意的地方
    else
        tree->LChild = NULL;

    if(RChild_len)                                                  //递归建立右子树
        tree->RChild = pre_in_create_tree(A, B, endPre-RChild_len+1, endPre, endIn-RChild_len+1, endIn);
    else
        tree->RChild = NULL;
    return tree;
}
/*
 * 层次遍历的应用
 * 1.将所有结点加入队列（包括空结点）。
 * 2.当遇到空结点时，判断其后是否存在非空结点，如果存在，则不是完全二叉树
 * 王道 P.131 第七题
 * */
bool is_complete(BinaryTree *tree)
{
    Tqueue queue;
    queue.front = queue.rear = 0;
    if(!tree)
        return 1;                           //空树为满二叉树
    enqueue(&queue, tree);
    while(queue.front != queue.rear)
    {
        if(!tree)                           //结点非空，将其左右子树入队
        {
            enqueue(&queue, tree->LChild);
            enqueue(&queue, tree->RChild);
        } else {                            //结点非空，检查其后是否有非空结点
            while(queue.front != queue.rear)
            {
                tree = dequeue(&queue);
                if(tree)                    //结点非空，为非完全二叉树
                    return 0;
            }
        }
    }
    return 1;
}
/*
 * 统计双分支结点的个数
 * 递归思路
 * f(root) = 0;                                      若root == NULL
 * f(root) = f(root->LChild) + f(root->RChild) + 1;  当前root结点为双分支结点
 * f(root) = f(root->LChild) + f(root->RChild);      其他情况（当前root为单分支结点，或者root为叶子结点）
 * 王道P.131 第八题
 * */
int double_son_node(BinaryTree *tree)
{
    if(tree == NULL)
        return 0;
    if(tree->LChild != NULL && tree->RChild != NULL)
    {
        return  double_son_node(tree->LChild) + double_son_node(tree->RChild) + 1;
    }else {
        double_son_node(tree->LChild) + double_son_node(tree->RChild);
    }
}

/*
 * 交互二叉树的左右子树(后序遍历的应用)
 * 1.首先交换root的左孩子的左右子树，
 * 2.然后交换root的右孩子的左右子树
 * 3.最后交换root的左右孩子，当结点为空时递归结束
 * 王道  P.131  第九题
 * */
void swap_lrchild(BinaryTree *tree)
{
    BinaryTree *tmp;
    if(tree)
    {
        swap_lrchild(tree->LChild);
        swap_lrchild(tree->RChild);
        tmp = tree->LChild;
        tree->LChild = tree->RChild;
        tree->RChild = tmp;
    }
}
/*
 * 求先序遍历中的第k个结点的值（确保k值在有效范围内）
 * 1.设置一个全局变量itag记录访问过的结点的序号，其初值是根结点在先序序列中的序号，即为1
 * 2.当二叉树tree为空时，返回特殊结点“#”，当itag == k时，表示找到了满足条件的结点，返回 tree->data
 * 3.当itag != k 是，则递归的在左右子树中继续查找
 * 王道   P.131    第十题
 * */
int itag = 1;
Telemtype search_k_node(BinaryTree *tree, int k)
{
    if(tree == NULL)
        return '#';
    if(itag == k)
        return tree->data;
    itag++;
    Telemtype ch = search_k_node(tree->LChild, k);
    if(tree->LChild != NULL)
        return ch;
    ch = search_k_node(tree->RChild, k);
    if(tree->RChild != NULL)                        //确保一定有返回值
        return ch;
    else
        return '#';
}
/*
 * 层次遍历的基本思想，就是找到 X 结点，然后删除它这棵树
 * 1.如果当前树根为X结点，直接删掉
 * 2.否则，进行层次遍历，去找 X,找到了就删掉，
 * Note:应为之前封装的好，明显要比书上的代码形式统一，也好看的多
 * 王道 P.132 第十一题
 * */
void destroy_x_tree(BinaryTree *tree, Telemtype x)
{
    if(tree)
    {
        if(tree->data == x)
        {
            destory_tree(tree);
            return;
        }
        Tqueue queue;
        queue.front = queue.rear = 0;
        enqueue(&queue, tree);
        while(queue.front != queue.rear)
        {
            tree = dequeue(&queue);
            if(tree->LChild)
            {
                if(tree->LChild->data == x)
                {
                    destory_tree(tree->LChild);
                    tree->LChild = NULL;
                } else {
                    enqueue(&queue, tree->LChild);
                }
            }
            if(tree->RChild)
            {
                if(tree->RChild->data == x)
                {
                    destory_tree(tree->RChild);
                    tree->RChild = NULL;
                }else{
                    enqueue(&queue, tree->RChild);
                }
            }
        }
    }
    return;
}

/*
 * 打印X结点的所有祖先，用到了非递归后序遍历的栈中信息
 * 1.非递归后序遍历找到X
 * 2.此时栈中的所有元素均为该结点的祖先结点
 * Note:树上的代码是后序遍历的不同写法，感觉没必要记那种（应该看一下深入理解后序遍历），
 * 会一种就够了了，所以我的代码，就是把上边的后序遍历中的输出语句该为了判断是否是当前结点。
 * 王道 P.133 第十二题
 * */

void print_ancestor_node(BinaryTree *tree, Telemtype x)
{
    Tstack stack;
    stack.top = -1;
    if(!tree)
        printf("the tree is empty!\n");
    else{
        while(tree || stack.top != -1) {
            while (tree) {
                push_stack(&stack, tree);
                stack.tag[stack.top] = 0;       //设置访问标记，0为第一次访问，1为第二次访问
                tree = tree->LChild;
            }
            if (stack.tag[stack.top] == 0)       //第一次访问时，转向同层右结点
            {
                tree = stack.stroe[stack.top];  //左走到底时，tree是空，必须有这句话
                stack.tag[stack.top] = 1;
                tree = tree->RChild;
            } else {
                while (stack.tag[stack.top] == 1)//在栈中找到下一个第一次范格纹你的结点，退出循环时并没有pop，所以为其左子结点
                {
                    tree = pop_stack(&stack);
                    //每次根改动都是下边
                    if(tree->data == x)
                    {

                        printf("\n%c ancestor is : \n",tree->data);;
                        for(int i = 0; i <= stack.top; ++i)
                        {
                            printf("%c ", stack.stroe[i]->data);
                        }
                        return;
                    }
                    //*********************
                }
                tree = NULL;
            }
        }
    }
}
/*
 * 求 p q两个结点的最近公共祖先，非递归后序遍历的应用，就是利用栈信息
 * 假设p 在 q的左边
 * 1.后序遍历必然先遍历到 p,这时把栈中的信息借用辅助栈保存起来
 * 2.继续遍历，遍历到 q 结点的时候，将栈中的结点逐个和辅助栈的结点匹配，
 *      第一个相等的元素就是p & q的最近公共祖先
 * 王道 P.134 第13题
 * */
BinaryTree* nearest_comm_ancestor(BinaryTree *tree, Telemtype p, Telemtype q)
{
    Tstack stack;
    Tstack ass_stack;
    stack.top = -1;
    ass_stack.top = -1;
    while(tree || stack.top != -1)
    {
        while(tree)
        {
            push_stack(&stack, tree);
            stack.tag[stack.top] = 0;
            tree = tree->LChild;
        }
        if(stack.tag[stack.top] == 0)
        {
            tree = stack.stroe[stack.top];
            stack.tag[stack.top] = 1;
            tree = tree->RChild;
        } else {
            while(stack.tag[stack.top] == 1)
            {
                tree = pop_stack(&stack);
                //每次根改动都是下边
                if(tree->data == p)
                {
                    for(int i = 0; i <= stack.top; ++i)
                    {
                        ass_stack.stroe[i] = stack.stroe[i];
                        ass_stack.top = stack.top;
                    }
                }
                if(tree->data == q)
                {
                    for(int i = stack.top; i >= 0; --i)
                    {
                        for(int j = ass_stack.top; j >= 0; --j)
                        {
                            if(stack.stroe[i]->data == ass_stack.stroe[j]->data)
                            {
                                return stack.stroe[i];
                            }
                        }
                    }
                }
                //*********************
            }
            tree = NULL;
        }
    }
}

/*
 * 求树的宽度，二叉树的宽度即 某一层拥有最多的结点树（层次遍历的应用）
 *
 * 王道  P.135  第十四题
 * */
/*
int tree_width(BinaryTree *tree)
{
    Tqueue queue;
    queue.front = queue.rear = 0;
    enqueue(&queue, tree);
    while(queue.front != queue.rear)
    {
        tree = dequeue(&queue);
    }
}
*/
/*
 * 2016/9/1  今天就写到这里，感觉自己对后序遍历的非递归算法，理解不够。
 * 先不写了回头总结总结
 * */

int main()
{
    BinaryTree *tree;
    tree = create_tree(tree);
    printf("preorder\n");
    //preorder_traverse(tree);
    non_recursion_preorder(tree);
    printf("\ninorder\n");
    //inorder_traverse(tree);
    non_recursion_inorder(tree);
    printf("\npostorder\n");
    //postorder_traverse(tree);
    non_recursion_postorder(tree);
    printf("\nlevelorder\n");
    levelorder(tree);
    printf("\ninvert_levelorder\n");
    invert_levelorder(tree);
    printf("\nleft_node`s number is %d\n", sum_left(tree));
    printf("\ndepth is %d\n", tree_depth2(tree));
    printf("\ndepth is %d\n", tree_depth(tree));
    //Telemtype A[] = {'A','B','C','D','E','F','G','H','K'};
    //Telemtype B[] = {'B','D','C','A','E','H','G','K','F'};
    Telemtype A[] = {' ','1','2','4','7','3','5','6','8'};
    Telemtype B[] = {' ','4','7','2','1','5','3','8','6'};
    BinaryTree *root, *root2;
    root = pre_in_create_tree(A, B, 1, 8, 1, 8);
    puts("\n*********************root traverse\n");
    preorder_traverse(root);
    root2 = pre_in_create_tree2(A, B, 1, 8, 1, 8);
    puts("\n*********************root2 traverse\n");
    preorder_traverse(root2);
    printf("is complete %d\n", is_complete(root));
    printf("double son node is %d\n", double_son_node(root));

    swap_lrchild(root2);
    preorder_traverse(root2);
    printf("\n%c\n", search_k_node(root2, 4));
    destroy_x_tree(root2, '2');
    preorder_traverse(root2);
    puts("\nprint_ancestor_node");
    print_ancestor_node(root, '5');
    root2 = nearest_comm_ancestor(root, '5', '6');
    printf("\nthe nearest_comm_ancestor is %c ", root2->data);
    printf("\n\nend!!\n\n");
    return 0;
}


