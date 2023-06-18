//
// Created by 86152 on 2023/6/10.
//

//Author hugo
//Time 2023/6/10 17:33
/*
 *�����������ģ�������
 * �����½��
 * ������ͷ�������½��
 * ɾ��������������Ϊ item �����н��
 * ��ת��������
 * �������������ݹ�ʵ�֣�
 * ��������ֵ�������еķǿ���������ϲ�Ϊһ����ֵ�������������
 * �Ĳ�����
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// �����½��
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// ������ͷ�������½��
void insertHead(Node **head, int data) {
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// ɾ��������������Ϊ item �����н��
void deleteNodes(Node **head, int item) {
    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->data == item) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            Node *temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// ��ת��������
void reverseList(Node **head) {
    Node *prev = NULL;
    Node *current = *head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

// �������������ݹ�ʵ�֣�
Node *copyList(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    Node *newNode = createNode(head->data);
    newNode->next = copyList(head->next);
    return newNode;
}

// ��������ֵ�������еķǿ���������ϲ�Ϊһ����ֵ�������������
Node *mergeSortedLists(Node *head1, Node *head2) {
    if (head1 == NULL) {
        return head2;
    }
    if (head2 == NULL) {
        return head1;
    }

    Node *mergedHead = NULL;

    if (head1->data < head2->data) {
        mergedHead = head1;
        head1 = head1->next;
    } else {
        mergedHead = head2;
        head2 = head2->next;
    }

    Node *current = mergedHead;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            current->next = head1;
            head1 = head1->next;
        } else {
            current->next = head2;
            head2 = head2->next;
        }
        current = current->next;
    }

    if (head1 != NULL) {
        current->next = head1;
    } else {
        current->next = head2;
    }

    return mergedHead;
}
int main() {
    Node *head1 = NULL;
    insertHead(&head1, 5);
    insertHead(&head1, 3);
    insertHead(&head1, 1);

    Node *head2 = NULL;
    insertHead(&head2, 6);
    insertHead(&head2, 4);
    insertHead(&head2, 2);

    Node *mergedHead = mergeSortedLists(head1, head2);

    printf("Merger Link List :\n");
    Node *current = mergedHead;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    return 0;
}