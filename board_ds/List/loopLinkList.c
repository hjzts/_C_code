//
// Created by 86152 on 2023/6/8.
//

//Author hugo
//Time 2023/6/8 16:27
/*
 *µ¥Ñ­»·Á´±í
*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef struct aNode {
    int data;
    struct aNode *next;
} Node;

Node *initList() {
    Node *L = (Node *) malloc(sizeof(Node));
    L->data = 0;
    L->next = L;
    return L;
}

/**
 * insert item in link list's head
 * @param L the head pointer of link list
 * @param data  the data you want to insert
 */
void headInsert(Node *L, int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = L->next;
    L->next = node;
}
void tailInsert(Node *L, int data) {
    Node *n = L;
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    while (n->next != L){
        n = n->next;
    }
    node -> next = L;
    n->next = node;
}
int delete(Node*L, int data) {
    Node *preNode = L;
    Node *node = L ->next;
    while (node != L){
        if(node->data == data){
            preNode ->next = node->next;
            free(node);
            L->data --;
            return TRUE;
        }
        preNode = node;
        node = node->next;
    }return FALSE;
}
void printList(Node *L) {
    Node *node = L->next;
    while (node != L){
        printf("%d->",node -> data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node *L = initList();
    headInsert(L,1);
    headInsert(L,2);
    headInsert(L,3);
    headInsert(L,4);
    headInsert(L,5);
    tailInsert(L,6);
    tailInsert(L,7);
    printList(L);
    delete(L,4);
    printList(L);
    return 0;
}
