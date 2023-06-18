//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 21:38
/*
 *��Ŀ����
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aTreeNode {
    char data;
    struct aTreeNode *lchild;
    struct aTreeNode *rchild;
    int flag;
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
        (*T)->flag = 0;
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

StackNode *getTop(StackNode *S) {
    if (isEmpty(S)) {
        return NULL;
    } else {
        StackNode *node = S->next;
        return node;
    }
}

void postOrder(TreeNode *T) {
    TreeNode *node = T;
    StackNode *S = initStack();
    while (node || !isEmpty(S)) {
        if (node) {
            push(node, S);
            node = node->lchild;
        } else {
            TreeNode *top = getTop(S)->data;
            if (top->rchild && top->rchild->flag == 0) {
                top = top->rchild;
                push(top, S);
                node = top->lchild;
            } else {
                top = pop(S)->data;
                printf("%c ", top->data);
                top->flag = 1;
            }
        }
    }
}
/*
 *        A
 *     B       C
 *   D    E   # #
 * # #  #  F
 *        # #
 */
int main(int argc, char *argv[]) {
    TreeNode *T;
    int index = 0;
    createTree(&T, argv[1], &index);
    postOrder(T);
    return 0;
}

