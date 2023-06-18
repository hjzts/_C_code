//
// Created by 86152 on 2023/6/8.
//

//Author hugo
//Time 2023/6/8 20:44
/*
 * 这是一个队列
 * 队列应该是尾en，头de
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aNode {
    int data;
    struct aNode *next;
} Node;

Node *initQueue() {
    Node *Q = (Node *) malloc(sizeof(Node));
    Q->data = 0;
    Q->next = NULL;
    return Q;
}

void enQueue(Node *Q, int data) {
    Node *q = Q;
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    for (int i = 0; i < Q->data; ++i) {
        q = q->next;
    }
    node->next = q->next;
    q->next = node;
    Q->data++;
}

void printQueue(Node *Q) {
    Node *node = Q->next;
    while (node) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int isEmpty(Node *Q) {
    if (Q->data == 0 || Q->next == NULL) {
        return 1;
    }
    return 0;
}

int deQueue(Node *Q) {
    if (isEmpty(Q)) {
        return -1;
    } else {
        Node *node = Q->next;
        int data = node->data;
        Q->next = node->next;
        free(node);
        Q->data--;
        return data;
    }
}

int main() {
    Node *Q = initQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);
    printQueue(Q);
    int data = deQueue(Q);
    printf("data = %d\n", data);
    printQueue(Q);
    deQueue(Q);
    deQueue(Q);
    deQueue(Q);
    printQueue(Q);
    return 0;
}
