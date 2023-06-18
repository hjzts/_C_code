//
// Created by 86152 on 2023/6/10.
//

//Author hugo
//Time 2023/6/10 17:22
/*
 *C语言的线性表的模板
 * 实现了一些基本操作和逆转顺序表中的所有元素的功能
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

// 初始化线性表
void initList(SeqList *list) {
    list->length = 0;
}

// 在线性表的指定位置插入元素
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

// 删除线性表的指定位置的元素
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

// 查找线性表中指定元素的位置
int find(SeqList *list, int elem) {
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] == elem) {
            return i;
        }
    }
    return -1;
}

// 逆转顺序表中的所有元素
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
