//
// Created by 86152 on 2023/6/8.
//

//Author hugo
//Time 2023/6/8 16:50
/*
 *双链表
*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef struct aNode {
    int data;
    struct aNode *pre;
    struct aNode *next;
} Node;

Node *initList() {
    Node *L = (Node *) malloc(sizeof(Node));
    L->data = 0;
    L->pre = NULL;
    L->next = NULL;
    return L;
}

void headInsert(Node *L, int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    if (L->data == 0) {
        node->next = L->next;
        node->pre = L;
        L->next = node;
        L->data++;
    } else {
        node->pre = L;
        node->next = L->next;
        L->next->pre = node;
        L->next = node;
        L->data++;
    }
}

void tailInsert(Node *L, int data) {
    Node *node = L;
    Node *n = (Node *) malloc(sizeof(Node));
    n->data = data;
    while (node->next != NULL) {
        node = node->next;
    }
    n->next = node->next;
    node->next = n;
    n->pre = node;
    L->data++;
}

int delete(Node *L, int data) {
    Node *node = L->next;
    while (node) {
        if (node->data == data) {
            //删除操作,不需要和单链表一样记录两个结点
            if (node->next != NULL) {
                node->pre->next = node->next;
                node->next->pre = node->pre;
                free(node);
                L->data--;
            } else {
                node->pre->next = NULL;
                free(node);
                L->data--;
            }
            return TRUE;
        }
        node = node->next;
    }
    return FALSE;
}

void printList(Node *L) {
    Node *node = L->next;
    while (node) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node *L = initList();
    headInsert(L, 1);
    headInsert(L, 2);
    headInsert(L, 3);
    headInsert(L, 4);
    tailInsert(L, 5);
    tailInsert(L, 6);
    printList(L);
    delete(L, 1);
    delete(L, 3);
    delete(L,6);
    printList(L);
    return 0;
}
