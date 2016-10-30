///练练练
#include <stdio.h>
#include <stdlib.h>
typedef char Telemtype;
typedef struct BinaryTree{
    Telemtype data;
    struct BinaryTree *LChild;
    struct BinaryTree *RChild;
}BinaryTree;
/* function content
 *
 * BinaryTree *create_tree(BinaryTree *root)
 * preorder_traverse(BinaryTree *root)
 * void inorder_traverse(BinaryTree *root)
 * void postorder_traverse(BinaryTree *root)
 * int sum_node(BinaryTree *root)
 * int tree_equal(BinaryTree *T1, BinaryTree *T2)
 * void destory_tree(BinaryTree *root)
 * BinaryTree *copy_tree(BinaryTree *root)
 * void non_recursion_preorder(BinaryTree *root)
 * void non_recursion_inorder(BinaryTree *root)
 * void non_recursion_postorder(BinaryTree *root)
 * void non_recursion_postorder2(BinaryTree *root)
 * void levelorder(BinaryTree *root)
 * void invert_levelorder(BinaryTree *root)
 * int tree_depth(BinaryTree *root)
 * int tree_depth2(BinaryTree *root)
 * void search_x_level(BinaryTree *root, Telemtype x)
 * BinaryTree *pre_in_create_tree(Telemtype A[], Telemtype B[], int startPre, int endPre, int startIn, int endIn)
 * BinaryTree *pre_in_create_tree2(Telemtype A[], Telemtype B[], int s1, int e1, int s2, int e2)
 * int is_complete(BinaryTree *root)
 * int double_son_node(BinaryTree *tree)
 * void swap_lrchild(BinaryTree *tree)
 * void swap_lrchild2(BinaryTree *root)
 * Telemtype search_k_node(BinaryTree *tree, int k)
 * void destroy_x_tree(BinaryTree *tree, Telemtype x)
 * void print_ancestor_node(BinaryTree *tree, Telemtype x)
 * BinaryTree *nearest_comm_ancestor(BinaryTree *tree, Telemtype p, Telemtype q)
 * int tree_width(BinaryTree *root)
 * void pre_to_post(Telemtype pre[], int s1, int e1, Telemtype post[], int s2, int e2)
 * BinaryTree *inorder_List(BinaryTree *root)
 * void link(BinaryTree *root, BinaryTree *head, BinaryTree *tail)
 * int is_similar(BinaryTree *T1, BinaryTree *T2)
 * int WPL(BinaryTree *root)
 * */
/*
 * 建树是通过先序遍历的方法进行，先输如一个字符，如果不是‘0’，则进行
 * 树的创建，否则不建树
 * 树的创建需要有一下几个步骤
 * 1.给树根结点申请空间
 * 2.给根节点的数据域赋值
 * 3.递归的分别创建左右子树
 * */
BinaryTree *create_tree(BinaryTree *root)
{
    Telemtype tmp;
    scanf("%c", &tmp);
    if(tmp == '0')
        return NULL;
    root = (BinaryTree*)malloc(sizeof(BinaryTree));
    root->data = tmp;
    root->LChild = create_tree(root->LChild);
    root->RChild = create_tree(root->RChild);
    return root;
}

/*
 * 递归写法的几种树的遍历（先序，中序，后序），都一样
 * 但是这样的写法其实在其他操作中也类似，
 * 1.比如说进行统计节点个数
 * 2.树的销毁等等
 * 对于时间复杂度，因为每个节点均遍历一次，所以复杂度为O(n)
 * */
void preorder_traverse(BinaryTree *root)
{
    if(root)
    {
        printf("%c ", root->data);
        preorder_traverse(root->LChild);
        preorder_traverse(root->RChild);
    }
}

void inorder_traverse(BinaryTree *root)
{
    if(root)
    {
        inorder_traverse(root->LChild);
        printf("%c ", root->data);
        inorder_traverse(root->RChild);
    }
}

void postorder_traverse(BinaryTree *root)
{
    if(root)
    {
        postorder_traverse(root->LChild);
        postorder_traverse(root->RChild);
        printf("%c ", root->data);
    }
}
/*
 * 统计二叉树中结点的个数
 * */
int sum_node(BinaryTree *root)
{
    if(!root)               //root == NULL
        return 0;
    else{
        return sum_node(root->LChild)
               + sum_node(root->RChild) + 1;
    }
}

/*
 * 统计叶子节点的个数
 * 1.先看当前节点是否是叶子节点，如果是叶子节点，sum值加一
 * 2.然后递归的分别统计左右子树中拥有的叶子节点的个数
 * */
int sum_leaf(BinaryTree *root)
{
    int sum = 0;
    if(root)
    {
        if(!root->LChild && !root->RChild)
            sum ++;
        if(root->LChild)
            sum += sum_leaf(root->LChild);
        if(root->RChild)
            sum += sum_leaf(root->RChild);
    }
    return sum;
}
/*
 * 1.如果两颗树是空树，则两颗树相等
 * 2.否则，判断当前树的根节点是否相等
 * 3.然后再递归的判断左右子树
 * 4.如果都相同，发回1.否则返回0
 * */
int tree_equal(BinaryTree *T1, BinaryTree *T2)
{
    if(!T1 && !T2)
        return 1;

    if(T1 && T2 && T1->data == T2->data)
        if(tree_equal(T1->LChild, T2->LChild))
            if(tree_equal(T1->RChild, T2->RChild))
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
void destory_tree(BinaryTree *root)
{
    if(!root)
        return;

    destory_tree(root->LChild);
    destory_tree(root->RChild);
    free(root);
    root = NULL;
    return;
}

/*
 * 树的复制包含两部分，一部分是，为要根节点设置值和要指向的左右子树
 * 第二部分就是递归的复制左右子树
 * 左右子树的复制，还是同后序遍历
 * */
BinaryTree *get_tree_node(Telemtype data, BinaryTree *LChild, BinaryTree *RChild)
{
    BinaryTree *root;
    root = (BinaryTree*)malloc(sizeof(BinaryTree));
    root->data = data;
    root->LChild = LChild;
    root->RChild = RChild;
    return root;
}

BinaryTree *copy_tree(BinaryTree *root)
{
    BinaryTree *newLChild, *newRChild, *newRoot;
    if(!root)
        return NULL;

    if(root->LChild)
        newLChild = copy_tree(root->LChild);
    else
        newLChild = NULL;
    if(root->RChild)
        newRChild = copy_tree(root->RChild);
    else
        newRChild = NULL;

    newRoot = get_tree_node(root->data, newLChild, newRChild);

    return newRoot;
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
void push_stack(Tstack *stack, BinaryTree *root)
{
    if(stack->top == 1000)
        printf("the stack is full!\n");
    else{
        stack->top++;
        stack->stroe[stack->top] = root;
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
    int level[1000];
    int front;
    int rear;
}Tqueue;
/*
 * 入队，出队比较简单
 * */
void enqueue(Tqueue *queue, BinaryTree *root)
{
    if(queue->rear == 1000)
        printf("the queue is full!\n");
    else{
        queue->stroe[queue->rear] = root;
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
void non_recursion_preorder(BinaryTree *root)
{
    Tstack stack;
    stack.top = -1;
    if(!root)
        printf("the tree is empty!\n");
    else{
        while(root || stack.top != -1)
        {
            if(root)
            {
                printf("%c ", root->data);
                push_stack(&stack, root);
                root = root->LChild;
            }else{
                root = pop_stack(&stack);
                root = root->RChild;
            }
            /*
             while(root)                        //类似于中序遍历,详见下边
             {
                printf("%c ", root->LChild);
                push_stack(&stack, root);
                root = root->LChild;
             }
                root = pop_stack(&stack);
                root = root->RChild;
             * */
        }
    }
}

/*
 * 1.先扫描（并非访问）根结点的所有左结点并将他们一一进栈
 * 2.当当前结点没有左子树（或者做孩子结点已经访问过），将其出栈，访问他
 * 3.然后扫描该结点的右孩子结点，将其进栈，再扫描右孩子结点的所有左结点并一一进栈，如此继续，直到栈空
 * */
void non_recursion_inorder(BinaryTree *root)
{
    Tstack stack;
    stack.top = -1;
    if(!root)
    {
        printf("the tree is empty!\n");
    }else {
        while(root || stack.top != -1)  //树根节点不空，或者栈不空时
        {
            if(root){
                push_stack(&stack, root);   //根结点进栈，遍历左子树
                root = root->LChild;        //每次遇到非空的左子树，就往左走
            }else{
                root = pop_stack(&stack);   //根指针退栈，访问根节点，遍历右子树
                printf("%c ", root->data);
                root = root->RChild;
            }

            /*
             while(root)                     //另外一种好的写法，只要有左子树，就往左走
             {
                 push_stack(&stack, root);   //根结点进栈，遍历左子树
                 root = root->LChild;        //每次遇到非空的左子树，就往左走
             }
             root = pop_stack(&stack);       //根指针退栈，访问根节点，遍历右子树
             printf("%c ", root->data);
             root = root->RChild;
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
 *    5.不满足4，弹出当前根结点，进行访问，并做标记，将root置空,必须将root置空，跳过向左走，直接向右走
 *
 * Note:当访问一个结点 *tmp (就是当前root)时，栈中的结点恰好是*tmp结点的所有祖先。
 *      从栈底到栈顶结点再加上*tmp结点，刚好构成从根结点到*tmp的一条路径
 *      在很多算法设计中都用到了这一特行，比如：
 *                *求根结点到某结点的路径
 *                *求两个结点的最近公共祖先
 * */

void non_recursion_postorder(BinaryTree *root)
{
    Tstack stack;
    stack.top = -1;
    BinaryTree *vis = NULL;

    if(!root)
        printf("the tree is empty!\n");

    while(root || stack.top != -1)
    {
        if(root)                                    //走到最左边
        {
            push_stack(&stack, root);
            root = root->LChild;
        }else{                                      //向右走
            root = stack.stroe[stack.top];           //取栈顶元素    王道 P.128
            if(root->RChild && root->RChild != vis)   //如果右子树存在，且未被访问过
            {
                root = root->RChild;                  //转向右子树
                push_stack(&stack, root);            //压栈
                root = root->LChild;                  //继续走到最左边
            }else{                                  //如果右子树不存在，或者已经访问过
                root = pop_stack(&stack);            //弹出当前的根结点
                printf("%c ", root->data);           //进行访问
                vis = root;                          //标记访问过
                root = NULL;                         //访问过后，重置root指针,必须将root置空，跳过向左走，直接向右走
            }
        }
    }
}

//后序遍历的标记数据域标记写法,这个不推荐
void non_recursion_postorder2(BinaryTree *root)
{
    Tstack stack;
    stack.top = -1;
    if(!root)
        printf("the tree is empty!\n");
    else{
        while(root || stack.top != -1) {
            while (root) {
                push_stack(&stack, root);
                stack.tag[stack.top] = 0;       //设置访问标记，0为第一次访问，1为第二次访问
                root = root->LChild;
            }
            if (stack.tag[stack.top] == 0)       //第一次访问时，转向同层右结点
            {
                root = stack.stroe[stack.top];  //左走到底时，tree是空，必须有这句话
                stack.tag[stack.top] = 1;
                root = root->RChild;
            } else {
                while (stack.tag[stack.top] == 1)//在栈中找到下一个第一次范格纹你的结点，退出循环时并没有pop，所以为其左子结点
                {
                    root = pop_stack(&stack);
                    printf("%c ", root->data);
                }
                root = NULL;
            }
        }
    }
}

/*
 * 层次遍历，其实就是BFS  （广度优先搜索）
 * */
void levelorder(BinaryTree *root)
{
    Tqueue queue;
    queue.front = queue.rear = 0;

    if(!root)
        printf("the tree is empty!\n");

    enqueue(&queue, root);              //根结点入队

    while(queue.front != queue.rear)
    {  //队列不为空时，循环
        root = dequeue(&queue);         //队头元素出队
        printf("%c ", root->data);      //访问当前结点

        if (root->LChild != NULL)
            enqueue(&queue, root->LChild);

        if (root->RChild != NULL)
            enqueue(&queue, root->RChild);
    }
}
/*
 * 层次遍历的应用，将树自下而上，自右向左遍历，
 * 就是把层次遍历访问的结点入栈，然后从栈弹出的顺序
 * 王道 P.128
 * */
void invert_levelorder(BinaryTree *root)
{
    Tqueue queue;
    Tstack stack;

    if(!root)
        printf("the tree is empty!\n");

    stack.top = -1;
    queue.front = queue.rear = 0;
    enqueue(&queue, root);              //根结点入队

    while(queue.front != queue.rear)
    {
        root = dequeue(&queue);
        push_stack(&stack, root);      //当前结点 入栈

        if (root->LChild != NULL)
            enqueue(&queue, root->LChild);

        if (root->RChild != NULL)
            enqueue(&queue, root->RChild);
    }

    while(stack.top != -1)
    {
        root = pop_stack(&stack);
        printf("%c ", root->data);
    }
}
/*
 * 王道 第五题 P.129 通过层次遍历获得树的深度
 * */
int tree_depth(BinaryTree *root)
{
    Tqueue queue;

    if(!root)
        return 0;

    queue.front = queue.rear = 0;
    int last = 1, level = 0;        //last指向下一层的第一个结点
    enqueue(&queue, root);          //根结点入队

    while(queue.front != queue.rear)
    {
        root = dequeue(&queue);

        if(root->LChild)
            enqueue(&queue, root->LChild);
        if(root->RChild)
            enqueue(&queue, root->RChild);

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
int tree_depth2(BinaryTree *root)
{
    int d = 0, dl, dr;
    if(!root)
        d = 0;
    else
    {
        dl = tree_depth2(root->LChild);
        dr = tree_depth2(root->RChild);
        d = 1 + max(dl, dr);
    }
    return d;
}

/*
 *求二叉树中值为x的结点所在的层数
 * */
void search_x_level(BinaryTree *root, Telemtype x)
{
    static int level = 1;
    if(root)
    {
        if(root->data == x)
            printf("the x level is %d\n", level) ;
        level++;
        search_x_level(root->LChild, x);
        search_x_level(root->RChild, x);
        level--;
    }
}

/*
 * 下面这种写法，牛逼666,学这个
 * NOTE: 关键的地方还是区间划分
 * s1 : start1, e1 : end1
 * s2 : start2, e2 : end2
 * */
BinaryTree *pre_in_create_tree2(Telemtype A[], Telemtype B[], int s1, int e1, int s2, int e2)
{
    if(s1 > e1 || s2 > e2)
        return NULL;
    BinaryTree *root;
    root = (BinaryTree*)malloc(sizeof(BinaryTree));
    root->data = A[s1];                                         //根结点
    for(int i = s2; i <=e2; i++)                       //根结点在中序中的划分
    {
        if(A[s1] == B[i]) {
            root->LChild = pre_in_create_tree2(A, B, s1 + 1, s1 + i - s2, s2, i - 1);
            root->RChild = pre_in_create_tree2(A, B, i - s2 + s1 + 1, e1, i + 1, e2);
        }
    }
    return root;
}

/*
 * 由先序和中序遍历，来唯一确定一棵二叉树
 * 1.根据先序序列确定树的根结点
 * 2.根据根结点在中序遍历中划分左右子树，然后根据左右子树结点在先序序列中的次序，可以确定子树的根结点，（即回到第一步）
 * 王道书上 P.130 第六题
 * */
BinaryTree *pre_in_create_tree(Telemtype A[], Telemtype B[], int startPre, int endPre, int startIn, int endIn)
{
    int i;
    BinaryTree *root;
    root = (BinaryTree*)malloc(sizeof(BinaryTree));
    root->data = A[startPre];
    for(i = startIn; B[i]!=root->data; ++i);
    int LChild_len = i - startIn;                                    //左子树的长度
    int RChild_len = endIn - i;                                      //右子树的长度

    if(LChild_len)                                                  //递归建立左子树
        root->LChild = pre_in_create_tree(A, B, startPre+1, startPre+LChild_len, startIn, startIn+LChild_len-1);   //划分的区间，是值得注意的地方
    else
        root->LChild = NULL;

    if(RChild_len)                                                  //递归建立右子树
        root->RChild = pre_in_create_tree(A, B, endPre-RChild_len+1, endPre, endIn-RChild_len+1, endIn);
    else
        root->RChild = NULL;

    return root;
}
/*
 * 层次遍历的应用
 * 1.将所有结点加入队列（包括空结点）。
 * 2.当遇到空结点时，判断其后是否存在非空结点，如果存在，则不是完全二叉树
 * 王道 P.131 第七题
 * */
int is_complete(BinaryTree *root)
{
    Tqueue queue;

    if(!root)
        return 1;                           //空树为满二叉树

    queue.front = queue.rear = 0;
    enqueue(&queue, root);

    while(queue.front != queue.rear)
    {
        if(!root)                           //结点非空，将其左右子树入队
        {
            enqueue(&queue, root->LChild);
            enqueue(&queue, root->RChild);
        } else {                            //结点非空，检查其后是否有非空结点
            while(queue.front != queue.rear)
            {
                root = dequeue(&queue);
                if(root)                    //结点非空，为非完全二叉树
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
    }else
    {
        return double_son_node(tree->LChild) + double_son_node(tree->RChild);
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
 * 借用队列实现左右子树交换
 * */
void swap_lrchild2(BinaryTree *root)
{
    BinaryTree *p, *tmp;
    Tqueue queue;
    queue.front = queue.rear = 0;
    if(root)
        enqueue(&queue, root);
    while(queue.rear != queue.front)
    {
        p = dequeue(&queue);
        if(p->LChild)
            enqueue(&queue, p->LChild);
        if(p->RChild)
            enqueue(&queue, p->RChild);

        tmp = p->LChild;
        p->LChild = p->RChild;
        p->RChild = tmp;
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
BinaryTree *nearest_comm_ancestor(BinaryTree *tree, Telemtype p, Telemtype q)
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
    return NULL;
}

/*
 * 求树的宽度，二叉树的宽度即 某一层拥有最多的结点树（层次遍历的应用）
 * 将所有节点对应的层次放在一个队列里，然后通过扫描队列求出各层的总结点的个数，最大的层结点即为二叉树的宽度
 * 王道  P.135  第十四题
 * */

int tree_width(BinaryTree *root)
{
    Tqueue queue;
    int k, max, i, n;

    if(!root)
        return 0;

    queue.front = queue.rear = 0;
    enqueue(&queue, root);
    queue.level[queue.rear] = 1;

    while(queue.front != queue.rear)
    {
        root = dequeue(&queue);
        k = queue.level[queue.front];
        if(root->LChild)
        {
            enqueue(&queue, root->LChild);
            queue.level[queue.rear] = k + 1;
        }
        if(root->RChild)
        {
            enqueue(&queue, root->RChild);
            queue.level[queue.rear] = k + 1;
        }

        max = 0; i = 0;                                            ///max保存同一层最多的结点个数
        k = 1;                                                     ///k表示从第一层开始查找
        while(i <= queue.rear)                                     ///i扫描队中所有的元素
        {
            n = 0;                                                  ///n统计第k层的结点个数
            while(i <= queue.rear && queue.level[i] == k)
            {
                n++;
                i++;
            }
            k = queue.level[i];
            if(n > max)
                max = n;
        }
    }
    return  max;
}

/*
 * 15、设有一棵满二叉树（所有结点的值均不相同），已知先序序列，求其后序序列
 *王道P1
 * */

void pre_to_post(Telemtype pre[], int s1, int e1, Telemtype post[], int s2, int e2)
{
    int half;
    if(e1 >= s1)
    {
        post[e2] = pre[s1];
        half = (e1 - s1) / 2;
        pre_to_post(pre, s1+1, s1+half, post, s2, s2+half-1);
        pre_to_post(pre, s1+half+1, e1, post, s1+half, e2-1);
    }
}

/*
 *16、将二叉树的叶节点按从左到右的顺序连城一个单链表，表头指针为head。
 * 二叉树按二叉链表的方式存储，链接时用叶结点的右指针域来存放指针单链表
 * */

BinaryTree *head, *pre = NULL;
BinaryTree *inorder_List(BinaryTree *root)
{
    if(root)
    {
        inorder_List(root->LChild);
        if (!root->LChild && !root->RChild) {
            if (!pre) {
                head = root;
                pre = root;
            } else {
                pre->RChild = root;
                pre = root;
            }
            inorder_List(root->RChild);
            pre->RChild = NULL;
        }
    }
    return head;
}
/*
 * 利用结点的右孩子rchild将一颗二叉树的叶子结点按照从左往右的顺序串成一个单链表
 * */
void link(BinaryTree *root, BinaryTree *head, BinaryTree *tail)
{
    if(root)
    {
        if(!root->LChild && !root->RChild)
        {
            if(!head)
            {
                head = root;
                tail = root;
            }else
            {
                tail->RChild = root;
                tail = root;
            }
        }
        link(root->LChild, head, tail);
        link(root->RChild, head, tail);
    }
}


/*
 *17、判断两颗二叉树是否相似
 * 相似：T1，T2都是空二叉树或都只有一个根结点，或T1的左子树和T2的左子树相似，T1的右子树和T2的右子树相似
 * */
int is_similar(BinaryTree *T1, BinaryTree *T2)
{
    int lvalue, rvalue;
    if(!T1 && !T2)
        return 1;
    else if(!T1 || !T2)
        return 0;
    else
    {
        lvalue = is_similar(T1->LChild, T2->LChild);
        rvalue = is_similar(T1->RChild, T2->RChild);
        return (lvalue&&rvalue);
    }
}

/*
 *18、写出中序线索二叉树里查找指定结点后序的前驱结点的算法
 * */

/*
 *19、求二叉树的带却路径长度（WPL）。
 * WPL指二叉树中所有叶结点的带权路径长度之和。
 * */
int wpl_preorder(BinaryTree *root, int deep)
{
    static int wpl = 0;
    if(!root->LChild && !root->RChild)
        wpl += deep*(root->data - '0');     ///此时data中存放的是权值，但我们data是char型。
    if(root->LChild)
        wpl_preorder(root->LChild, deep+1);
    if(root->RChild)
        wpl_preorder(root->RChild, deep+1);
    return wpl;
}

int WPL(BinaryTree *root)
{
    return wpl_preorder(root, 0);
}


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
    printf("\nleft_node`s number is %d\n", sum_leaf(tree));
    printf("\ndepth is %d\n", tree_depth2(tree));
    printf("\ndepth is %d\n", tree_depth(tree));
    //Telemtype A[] = {'A','B','C','D','E','F','G','H','K'};
    //Telemtype B[] = {'B','D','C','A','E','H','G','K','F'};
    Telemtype A[] = {' ', '1', '2', '4', '7', '3', '5', '6', '8'};
    Telemtype B[] = {' ', '4', '7', '2', '1', '5', '3', '8', '6'};
    BinaryTree *root, *root2;
    root = pre_in_create_tree(A, B, 1, 8, 1, 8);
    puts("\n*********************root traverse\n");
    preorder_traverse(root);
    root2 = pre_in_create_tree2(A, B, 1, 8, 1, 8);
    puts("\n*********************root2 traverse\n");
    preorder_traverse(root2);
    printf("is complete %d\n", is_complete(root));
    printf("double son node is %d\n", double_son_node(root));
    printf("\nthe swap_lrChild2\n");
    swap_lrchild2(tree);
    preorder_traverse(tree);
    puts("the end swap_LRChile\n");
    preorder_traverse(root2);
    printf("\n%c\n", search_k_node(root2, 4));
    destroy_x_tree(root2, '2');
    preorder_traverse(root2);
    puts("\nprint_ancestor_node");
    print_ancestor_node(root, '5');
    root2 = nearest_comm_ancestor(root, '5', '6');
    printf("\nthe nearest_comm_ancestor is %c ", root2->data);
    printf("\n\nend!!\n\n");



    ///copy_tree   Test
    BinaryTree *copy_tree_root = copy_tree(tree);
    preorder_traverse(copy_tree_root);
    preorder_traverse(tree);
    ///tree_width  Test
    int width = tree_width(tree);
    printf("\nthe tree`s width is %d\n", width);

    ///search_x_level Test
    search_x_level(tree, '3');
    search_x_level(tree, '2');
    search_x_level(tree, '1');
    search_x_level(tree, '4');

    ///sum_node
    int s_node = sum_node(tree);
    printf("%d\n", s_node);

    return 0;
}
///test case ：12003400500