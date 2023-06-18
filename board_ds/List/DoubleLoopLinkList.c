//
// Created by 86152 on 2023/6/8.
//

//Author hugo
//Time 2023/6/8 17:36
/*
 *双循环链表
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
        //链表为空
        node->pre = L;
        node->next = L;
        L->pre = node;
        L->next = node;
        L->data++;
    } else {
        //链表不为空
        node->next = L->next;
        node->pre = L;
        L->next->pre = node;
        L->next = node;
        L->data++;
    }
}

void tailInsert(Node *L, int data) {
    Node *node = L;
    Node *n = (Node *) malloc(sizeof(Node));
    n->data = data;
    while (node->next != L) {
        node = node->next;
    }
    n->pre = node;
    n->next = L;
    L->pre = n;
    node->next = n;
    L->data++;
}

int delete(Node *L, int data) {
    Node *node = L->next;
    while (node != L) {
        if (node->data == data) {
            //删除操作
            if(node->next != L){
                node->pre->next = node->next;
                node->next->pre = node->pre;
                free(node);
                L->data--;
            }else{
                node->pre->next = L;
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
    while (node != L) {
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
    headInsert(L, 5);
    tailInsert(L, 6);
    tailInsert(L, 7);
    printList(L);
    delete(L,2);
    delete(L,4);
    delete(L,7);
    printList(L);
    return 0;
}
