//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 20:48
/*
 * 这里用栈来实现前序遍历和中序遍历的非递归形式
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aTreeNode {
    char data;
    struct aTreeNode *lchild;
    struct aTreeNode *rchild;
} TreeNode;
typedef struct aStackNode {
    TreeNode *data;
    struct aStackNode *next;
} StackNode;

void createTree(TreeNode **T, char *data, int *index) {
    char ch;
//    scanf("%c\n", &ch);
    ch = data[*index];
    //把这里改成*index++;就会报错？？？
    *index += 1;
    if (ch == '#') {
        //此时为空节点
        *T = NULL;
    } else {
        //此时不为空
        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T)->data = ch;
        //创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index);
        //创建左子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index);
    }
}

StackNode *initStack() {
    StackNode *S = (StackNode *) malloc(sizeof(StackNode));
    S->data = NULL;
    S->next = NULL;
    return S;
}

//头插法
void push(TreeNode *data, StackNode *S) {
    StackNode *node = (StackNode *) malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
}

int isEmpty(StackNode *S) {
    if (S->next == NULL) {
        return 1;
    }
    return 0;
}

StackNode *pop(StackNode *S) {
    if (isEmpty(S)) {
        return NULL;
    } else {
        StackNode *node = S->next;
        S->next = node->next;
        return node;
    }
}

void preOrder(TreeNode *T) {
    TreeNode *node = T;
    StackNode *S = initStack();
    while (node || !isEmpty(S)) {
        if (node) {
            printf("%c ", node->data);
            push(node, S);
            node = node->lchild;
        } else {
            node = pop(S) ->data;
            node = node->rchild;
        }
    }
}
void inOrder(TreeNode *T) {
    TreeNode *node = T;
    StackNode *S = initStack();
    while (node || !isEmpty(S)) {
        if (node) {
            push(node, S);
            node = node->lchild;
        } else {
            node = pop(S) ->data;
            printf("%c ", node->data);
            node = node->rchild;
        }
    }
}

int main(int argc, char *argv[]) {
    TreeNode *T;
    int index = 0;
    createTree(&T, argv[1], &index);
    printf("preOrder:\t");
    preOrder(T);
    putchar(10);
    printf("inOrder:\t");
    inOrder(T);
    putchar(10);
    return 0;
}
