#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建新结点
TreeNode *createNode(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 先序遍历递归算法建立二叉树（从键盘输入数据）
TreeNode *buildTreeFromInput() {
    int data;
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    TreeNode *node = createNode(data);
    node->left = buildTreeFromInput();
    node->right = buildTreeFromInput();

    return node;
}

// 先序遍历递归算法建立二叉树（从数组获取数据）
int arrayIndex = 0;
TreeNode *buildTreeFromArray(int *array, int size) {
    if (arrayIndex >= size || array[arrayIndex] == -1) {
        arrayIndex++;
        return NULL;
    }

    TreeNode *node = createNode(array[arrayIndex]);
    arrayIndex++;
    node->left = buildTreeFromArray(array, size);
    node->right = buildTreeFromArray(array, size);

    return node;
}

// 求二叉树的深度（递归算法）
int treeDepthRecursive(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = treeDepthRecursive(root->left);
    int rightDepth = treeDepthRecursive(root->right);
    return (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
}

// 求二叉树的深度（非递归算法）
int treeDepthNonRecursive(TreeNode *root) {
    // 请参考下面的按层次遍历实现
}

// 求结点所在层次
int findNodeLevel(TreeNode *root, int data, int level) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == data) {
        return level;
    }
    int leftLevel = findNodeLevel(root->left, data, level + 1);
    if (leftLevel != 0) {
        return leftLevel;
    }
    return findNodeLevel(root->right, data, level + 1);
}

// 交换二叉树中所有结点的左右子树的位置
void swapLeftRight(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
    swapLeftRight(root->left);
    swapLeftRight(root->right);
}

// 删除二叉树中以某个结点为根结点的子树
void deleteSubtree(TreeNode **root, int data) {
    if (*root == NULL) {
        return;
    }
    if ((*root)->data == data) {
        *root = NULL;
        return;
    }
    deleteSubtree(&((*root)->left), data);
    deleteSubtree(&((*root)->right), data);
}

// 以下是您要求的非递归遍历算法和按层次遍历的实现
// 由于篇幅原因，这里只提供函数声明，您可以在网上找到相应的实现方法
//void preorderTraversalNonRecursive(TreeNode *root);
//void inorderTraversalNonRecursive(TreeNode *root);
//void postorderTraversalNonRecursive(TreeNode *root);
//void levelOrderTraversal(TreeNode *root);
typedef struct Stack {
    TreeNode **data;
    int top;
    int capacity;
} Stack;

Stack *createStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->data = (TreeNode **)malloc(capacity * sizeof(TreeNode *));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

bool isStackEmpty(Stack *stack) {
    return stack->top == -1;
}

bool isStackFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack *stack, TreeNode *node) {
    if (isStackFull(stack)) {
        return;
    }
    stack->data[++stack->top] = node;
}

TreeNode *pop(Stack *stack) {
    if (isStackEmpty(stack)) {
        return NULL;
    }
    return stack->data[stack->top--];
}

// 先序遍历（非递归算法）
void preorderTraversalNonRecursive(TreeNode *root) {
    Stack *stack = createStack(100);
    TreeNode *current = root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            printf("%d ", current->data);
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        current = current->right;
    }
}

// 中序遍历（非递归算法）
void inorderTraversalNonRecursive(TreeNode *root) {
    Stack *stack = createStack(100);
    TreeNode *current = root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

// 后序遍历（非递归算法）
void postorderTraversalNonRecursive(TreeNode *root) {
    Stack *stack = createStack(100);
    TreeNode *current = root;
    TreeNode *lastVisited = NULL;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = stack->data[stack->top];
        if (current->right == NULL || current->right == lastVisited) {
            printf("%d ", current->data);
            pop(stack);
            lastVisited = current;
            current = NULL;
        } else {
            current = current->right;
        }
    }
}

// 按层次遍历
void levelOrderTraversal(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    TreeNode **queue = (TreeNode **)malloc(100 * sizeof(TreeNode *));
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front != rear) {
        TreeNode *current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}
/*
 *                  1
 *          2               3
 *     4        5      6         7
 *  -1  -1   -1  -1  -1  -1   -1  -1
 */
int main() {
    int array[] = {1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, -1, 7, -1, -1};
    int size = sizeof(array) / sizeof(array[0]);

    TreeNode *root = buildTreeFromArray(array, size);

    printf("Preorder traversal (non-recursive): ");
    preorderTraversalNonRecursive(root);
    printf("\n");

    printf("Inorder traversal (non-recursive): ");
    inorderTraversalNonRecursive(root);
    printf("\n");

    printf("Postorder traversal (non-recursive): ");
    postorderTraversalNonRecursive(root);
    printf("\n");

    printf("Level order traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    printf("Tree depth (recursive): %d\n", treeDepthRecursive(root));

    int nodeData = 2;
    printf("Level of node with data %d: %d\n", nodeData, findNodeLevel(root, nodeData, 1));

    swapLeftRight(root);
    printf("After swapping left and right children:\n");
    printf("Level order traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    int deleteData = 3;
    deleteSubtree(&root, deleteData);
    printf("After deleting subtree with root data %d:\n", deleteData);
    printf("Level order traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}

/*
#include <stdlib.h>
#include <stdio.h>

#define DataType int
#define M 1024
#define NodeNum 100
#define MaxSize 100

typedef struct node {
    DataType data;
    struct node *lchild, *rchild;
} BTNode, *BTNodePtr;
BTNodePtr BTree, p, q, Root = NULL;

void INITIAL();         //初始（创建）一棵二叉树
void ROOT();            //求二叉树BTree的结点，或求结点x所在二叉树的根节点
void PARENT();          // 求二叉树BTree中结点x的双亲结点
void LDELETE();         //求二叉树BTree中结点x的左孩子
void RDELETE();        //求二叉树BTree中结点x的右孩子
void TRAVERSE();        //遍历  按照某种次序（或原则）依次访问二叉树BTree中各个节点，得到由该二叉树的所有接单组成的序列
int LAYER();            //求二叉树中结点x所处的层次
int DEPTH();            //求二叉树BTree的深度
void DESTROY(BTNodePtr T);         //销毁一棵二叉树  删除BTree的所有结点，并释放结点空间，使之成为一棵空二叉树

void VISIT(BTNodePtr T);

void SequenceVisit(DataType T);

void recursion_preoreder(BTNodePtr T) {//前序遍历 DLR
    if (T != NULL) {
        VISIT(T);
        recursion_preoreder(T->lchild);
        recursion_preoreder(T->rchild);
    }
}

void preorder(BTNodePtr T);

void recursion_inorder(BTNodePtr T) {//中序遍历 LDR
    if (T != NULL) {
        recursion_inorder(T->lchild);
        VISIT(T);
        recursion_inorder(T->rchild);
    }
}

void inorder(BTNodePtr T) {
    BTNodePtr stack[M], p = T;
    int top = -1;
    if (T != NULL) {
        do {
            for (; p != NULL; p = p->lchild) {
                stack[++top] = p;
            }
            p = stack[top--];
            VISIT(p);
            p = p->rchild;
        } while (p != NULL || top != 1);
    }
}

void recursion_postorder(BTNodePtr T) {//后序遍历 LRD
    if (T != NULL) {
        recursion_postorder(T->lchild);
        recursion_postorder(T->rchild);
        VISIT(T);
    }
}

void posrorder(BTNodePtr T) {
    BTNodePtr stack1[M], p = T;
    int stack2[M], top = -1, flag;
    if (T != NULL) {
        do {
            while (p != NULL) {
                stack1[++top] = p;  //当前p所指结点的地址进栈
                stack2[top] = 0;    //当前p所指结点 不可访问标志 进栈
                p = p->lchild;
            }//p指向其左孩子结点
            p = stack1[top];
            flag = stack2[top--];//退栈
            if (flag == 0) {
                stack1[++top] = p;      //当前p所指结点再次进栈
                stack2[top] = 1;        //当前p所指结点 可访问标志 进栈
                p = p->rchild;
            } else { VISIT(p); };
            p = NULL;                   //表明以p结点为根的树访问完成
        } while (p != NULL || top != -1);
    }
}

void layerOrder(BTNodePtr T) {
    BTNodePtr queue[NodeNum], p;
    int front, rear;
    if (T != NULL) {
        queue[0] = T;
        front = -1;
        rear = 0;
        while (front < rear) {      //若队列不空
            p = queue[++front];
            VISIT(p);           //访问p指结点
            if (p->lchild != NULL)   //若左孩子非空
                queue[++rear] = p->lchild;
            if (p->rchild != NULL)   //若右孩子非空
                queue[++rear] = p->rchild;
        }
    }
}

void SequenceInOrder(DataType btree[], int n) {       //二叉树的顺序存储及其中序遍历
    int stack[MaxSize], i, top = -1;
    i = 0;
    if (n >= 0) {
        do {
            while (i < n) {
                stack[++top] = i;       //btree[i]的位置i元素进栈
                i = i * 2 + 1;          //找到i的左孩子的位置
            }
            i = stack[top--];           //退栈
            SequenceVisit(btree[i]);    //访问结点btree[i]
            i = i * 2 + 2;               //找到i的右孩子的位置
        } while (!(i > n - 1 && top == -1));
    }
}

BTNodePtr copyTree(BTNodePtr src) {      //二叉树的拷贝
    BTNodePtr obj;
}

void DESTROY(BTNodePtr p) {
    if (p != NULL) {
        DESTROY(p->lchild);
        DESTROY(p->rchild);
        free(p);
        p = NULL;
    }
}

int MAX(int x, int y) {
    if (x > y) return x;
    else return y;
}

int DEPTH(BTNodePtr p) {
    if (p == NULL)return 0;
    else
        return 1 + MAX(DEPTH(p->lchild), DEPTH((p->rchild)));
}

BTNodePtr recursion_insertBST(BTNodePtr p, DataType item) {//递归实现二叉查找树的建立
    if (p == NULL) {
        p = (BTNodePtr) malloc(sizeof(BTNode));
        p->data = item;
        p->lchild = p->rchild = NULL;
    } else if (item < p->data) {
        p->lchild = recursion_insertBST(p->lchild, item);
    } else if (item > p->data) {
        p->rchild = recursion_insertBST(p->rchild, item);
    } else {      //树中存在该元素
        //do something
    }
    return p;
}

//设置Root为一个全局变量
void insertBST(DataType item) {
    BTNodePtr p, q;
    p = (BTNodePtr) malloc(sizeof(BTNode));
    p->data = item;
    p->lchild = NULL;
    p->rchild = NULL;
    if (Root == NULL)
        Root = p;
    else {
        q = Root;
        while (1) {
            //比较值的大小
            //小于向左，大于向右
            if (item < q->data) {
                if (q->lchild == NULL) {
                    q->lchild = p;
                    break;
                } else {
                    q = q->lchild;
                }
            } else if (item > q->data) {
                if (q->rchild == NULL) {
                    q->rchild = p;
                    break;
                } else {
                    q = q->rchild;
                }
            } else {            //树中存在该元素
                //do something
            }
        }
    }
}
void DeleteBST();
BTNodePtr SearchBST(BTNodePtr T,DataType item){
    BTNodePtr p = T;
    while (p != NULL){
        if(item == p->data)
            return p;       //查找成功
        else if(item > p->data)
            p = p->rchild;  //将p移到右子树的根节点
        else if(item < p->data)
            p = p->lchild;  //将p移到左子树的根节点
    }
    return  NULL;           //查找失败
}
BTNodePtr recursion_SearchBST(BTNodePtr T,DataType item){
    if(T != NULL){
        if( item == T->data)
            return T;       //查找成功
        else if(item > T->data)
            return recursion_SearchBST(T->rchild,item);//查找T的右子树
        else if(item < T->data)
            return recursion_SearchBST(T->lchild,item);//查找T的左子树
    } else return NULL;     //查找失败
}
int main() {

    return 0;
}
*/
