//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 20:48
/*
 * ������ջ��ʵ��ǰ���������������ķǵݹ���ʽ
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
    //������ĳ�*index++;�ͻᱨ������
    *index += 1;
    if (ch == '#') {
        //��ʱΪ�սڵ�
        *T = NULL;
    } else {
        //��ʱ��Ϊ��
        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T)->data = ch;
        //�������������߼�һ�£����еݹ�
        createTree(&((*T)->lchild), data, index);
        //�������������߼�һ�£����еݹ�
        createTree(&((*T)->rchild), data, index);
    }
}

StackNode *initStack() {
    StackNode *S = (StackNode *) malloc(sizeof(StackNode));
    S->data = NULL;
    S->next = NULL;
    return S;
}

//ͷ�巨
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
