//
// Created by 86152 on 2023/6/10.
//

//Author hugo
//Time 2023/6/10 17:22
/*
 *C���Ե����Ա��ģ��
 * ʵ����һЩ������������ת˳����е�����Ԫ�صĹ���
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

// ��ʼ�����Ա�
void initList(SeqList *list) {
    list->length = 0;
}

// �����Ա��ָ��λ�ò���Ԫ��
int insert(SeqList *list, int pos, int elem) {
    if (list->length == MAX_SIZE) {
        return -1;
    }
    if (pos < 0 || pos > list->length) {
        return -1;
    }
    for (int i = list->length; i > pos; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[pos] = elem;
    list->length++;
    return 0;
}

// ɾ�����Ա��ָ��λ�õ�Ԫ��
int delete(SeqList *list, int pos) {
    if (pos < 0 || pos >= list->length) {
        return -1;
    }
    for (int i = pos; i < list->length - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    return 0;
}

// �������Ա���ָ��Ԫ�ص�λ��
int find(SeqList *list, int elem) {
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] == elem) {
            return i;
        }
    }
    return -1;
}

// ��ת˳����е�����Ԫ��
void reverse(SeqList *list) {
    int temp;
    for (int i = 0; i < list->length / 2; i++) {
        temp = list->data[i];
        list->data[i] = list->data[list->length - 1 - i];
        list->data[list->length - 1 - i] = temp;
    }
}

int main() {
//    system ("chcp 65001");
    SeqList list;
    initList(&list);
    insert(&list, 0, 1);
    insert(&list, 1, 2);
    insert(&list, 2, 3);
    insert(&list, 3, 4);
    insert(&list, 4, 5);

    printf("before\n");
    for (int i = 0; i < list.length; i++) {
        printf("%d ", list.data[i]);
    }
    printf("\n");

    reverse(&list);

    printf("after\n");
    for (int i = 0; i < list.length; i++) {
        printf("%d ", list.data[i]);
    }
    printf("\n");

    return 0;
}
