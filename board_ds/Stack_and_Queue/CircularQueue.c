//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 16:30
/*
 *这里使用顺序表模拟实现一个循环队列
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
typedef struct aQueue {
    int front;
    int rear;
    int data[MAXSIZE];
} Queue;

Queue *initQueue() {
    Queue *Q = (Queue *) malloc(sizeof(Queue));
    Q->front = Q->rear = 0;
    return Q;
}

int isFull(Queue *Q) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return 1;
    }
    return 0;
}

int isEmpty(Queue *Q) {
    if (Q->front == Q->rear) {
        return 1;
    }
    return 0;
}

int enQueue(Queue *Q, int data) {
    if (isFull(Q)) {
        return 0;
    } else {
        Q->data[Q->rear] = data;
        Q->rear = (Q->rear + 1) % MAXSIZE;
        return 1;
    }
}

int deQueue(Queue *Q) {
    if (isEmpty(Q)) {
        return -1;          //这里认为队列元素全部非负，如果有负的，用一个很小的数代替
    } else {
        int data = Q->data[Q->front];
        Q->front = (Q->front + 1) % MAXSIZE;
        return data;
    }
}

void printQueue(Queue *Q) {
    //要知道队列当前有多少个元素
    int length = (Q->rear - Q->front + MAXSIZE)%MAXSIZE;
    int index = Q->front;
    for (int i = 0; i < length; ++i) {
        printf("%d -> ",Q->data[index]);
        index = (index + 1) % MAXSIZE;
    }
    printf("NULL\n");
}

int main() {
    Queue *Q = initQueue();
    enQueue(Q,1);
    enQueue(Q,2);
    enQueue(Q,3);
    enQueue(Q,4);
    printQueue(Q);
    deQueue(Q);
    printQueue(Q);
    return 0;
}
