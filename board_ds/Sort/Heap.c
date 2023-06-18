#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HNode *Heap;    //堆的类型定义
typedef int ElementType;

struct HNode {
    ElementType *Data;   //存储元素的数组
    int Size;            //堆中当前元素个数
    int Capacity;       //堆的最大容量
};
typedef Heap MaxHeap;   //最大堆，大根堆

#define MAXDATA 1000  //该值应该根据具体情况定义为大于堆中所有可能元素的值
#define ERROR -1

MaxHeap CreateHeap(int MaxSize) {    //创建容量为Maxsize的空的最大堆
    MaxHeap H = (MaxHeap) calloc((MaxSize + 1) , sizeof(ElementType));
    H->Data = (ElementType *) calloc((MaxSize + 1) ,sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MAXDATA;
    return H;
}

bool isFull(MaxHeap H) {
    return (H->Size == H->Capacity);
}

bool Insert(MaxHeap H, ElementType X) {   //将元素X插入最大堆H，其中H->Data[0]已经定义为哨兵
    int i;
    if (isFull(H)) {
        return false;
    }
    i == ++H->Size;
    for (; H->Data[i / 2] < X; i /= 2) {
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i] = X;
    return true;
}

bool isEmpty(MaxHeap H) {
    return (H->Size == 0);
}

ElementType DeleteMax(MaxHeap H) {
    int Parent, Child;
    ElementType MaxItem, X;
    if (isEmpty(H)) {
        return ERROR;
    }
    MaxItem = H->Data[1];
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if (Child != H->Size && H->Data[Child] < H->Data[Child + 1]) {
            Child++;
        }
        if (X >= H->Data[Child])
            break;
        else
            H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;
    return MaxItem;
}

int main() {
    MaxHeap A;
    A = CreateHeap(MAXDATA);
    //插入数据
    Insert(A, 4);
    Insert(A, 5);
    Insert(A, 1);
    Insert(A, 2);
    Insert(A, 3);
    Insert(A, 6);
    Insert(A, 7);
    Insert(A, 16);
    Insert(A, 37);
    //抛出最大值
    for (int i = 0; i < 9; i++) {
        int X = DeleteMax(A);
        printf("%d\n", X);
    }
    printf("isFull=%d\n", isFull(A));
    printf("isEmpty=%d\n", isEmpty(A));
    return 0;
}