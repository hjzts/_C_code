//
// Created by 86152 on 2023/6/8.
//

//Author hugo
//Time 2023/6/8 20:27
/*
 *用链表来实现栈
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aNode {
    int data;
    struct aNode *next;
} Node;

Node *initStack() {
    Node *S = (Node *) malloc(sizeof(Node));
    S->data = 0;
    S->next = NULL;
    return S;
}

int isEmpty(Node *S) {
    if (S->data == 0 || S->next == NULL) {
        return 1;
    }
    return 0;
}

int getTop(Node *S) {
    if (isEmpty(S)) {
        return -1;
    } else {
        return S->next->data;
    }
}

int pop(Node *S) {
    if (isEmpty(S)) {
        return -1;
    } else {
        Node *node = S->next;
        int data = node->data;
        S->next = node->next;
        free(node);
        return data;
    }
}

void push(Node *S, int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = S->next;
    S->next = node;
    S->data++;
}

void printStack(Node *S) {
    Node *node = S->next;
    while (node) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node *S = initStack();
    push(S, 1);
    push(S, 2);
    push(S, 3);
    push(S, 4);
    printStack(S);
    int i = pop(S);
    printf("Current elem = %d\n", i);
    printStack(S);
    return 0;
}
