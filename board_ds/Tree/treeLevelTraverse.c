//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 17:52
/*
 * 实现二叉树的层次遍历
 * 队列是尾插头取
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aTreeNode {
    char data;
    struct aTreeNode *lchild;
    struct aTreeNode *rchild;
} TreeNode;
typedef struct aQueueNode {
    TreeNode *data;
    struct aQueueNode *pre;
    struct aQueueNode *next;
} QueueNode;

void createTree(TreeNode **T, char *data, int *index) {
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T)->data = ch;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

void preOrder(TreeNode *T) {
    if (T == NULL) return;
    else {
        printf("%c", T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

QueueNode *initQueue() {
    QueueNode *Q = (QueueNode *) malloc(sizeof(QueueNode));
    Q->data = NULL;
    Q->next = Q;
    Q->pre = Q;
    return Q;
}

int isEmpty(QueueNode *Q) {
    if (Q->next == Q) {
        return 1;
    }
    return 0;
}

void enQueue(TreeNode *data, QueueNode *Q) {
    QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
    node->data = data;
    node->pre = Q;
    node->next = Q;
    Q->pre->next = node;       //尾插法，Q->pre为最后一个节点
    Q->pre = node;
}

QueueNode *deQueue(QueueNode *Q) {
    if (isEmpty(Q)) {
        return NULL;
    } else {
        QueueNode *node = Q->next;
        Q->next->next->pre = Q;
        Q->next = Q->next->next;
        return node;
    }
}

void levelTraverse(QueueNode *Q, TreeNode *T) {
    enQueue(T, Q);
    while (!isEmpty(Q)) {
        QueueNode *node = deQueue(Q);
        printf("%c -> ", node->data->data);
        if (node->data->lchild) {
            enQueue(node->data->lchild, Q);
        }
        if (node->data->rchild) {
            enQueue(node->data->rchild, Q);
        }
    }
    printf("NULL");
}

int main(int argc, char *argv[]) {
    TreeNode *T;
    int index = 0;
    QueueNode *Q = initQueue();
    createTree(&T, argv[1], &index);
    preOrder(T);
    putchar(10);
    levelTraverse(Q, T);
    return 0;
}
