//
// Created by 86152 on 2023/6/17.
//

//Author hugo
//Time 2023/6/17 18:28
/*
 * 哈夫曼树
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
typedef struct aTreeNode {
    int weight;
    int parent;
    int lchild;
    int rchild;
} TreeNode;

typedef struct aHFTree {
    TreeNode *data;
    int length;
} HFTree;

HFTree *initTree(int *weight, int length) {
    HFTree *T = (HFTree *) malloc(sizeof(HFTree));
    T->data = (TreeNode *) malloc(sizeof(TreeNode) * (2 * length - 1));
    T->length = length;
    for (int i = 0; i < length; ++i) {
        T->data[i].weight = weight[i];
        T->data[i].parent = 0;
        T->data[i].lchild = -1;
        T->data[i].rchild = -1;
    }
    return T;
}

int *selectMin(HFTree *T) {
    int min = MAX;
    int secondMin = MAX;
    int minIndex;
    int secondIndex;
    for (int i = 0; i < T->length; ++i) {
        if (T->data[i].parent == 0) {
            if (T->data[i].weight < min) {
                min = T->data[i].weight;
                minIndex = i;
            }
        }
    }
    for (int i = 0; i < T->length; ++i) {
        if (T->data[i].parent == 0 && i != minIndex) {
            if (T->data[i].weight < secondMin) {
                secondMin = T->data[i].weight;
                secondIndex = i;
            }
        }
    }
    int *res = (int *) malloc(sizeof(int) * 2);
    res[0] = minIndex;
    res[1] = secondIndex;
    return res;
}

void createHFTree(HFTree *T) {
    int *res;
    int min;
    int secondMin;
    int length = T->length * 2 - 1;
    for (int i = T->length; i < length; ++i) {
        res = selectMin(T);
        min = res[0];
        secondMin = res[1];
        T->data[i].weight = T->data[min].weight + T->data[secondMin].weight;
        T->data[i].lchild = min;
        T->data[i].rchild = secondMin;
        T->data[i].parent = 0;
        T->data[min].parent = i;
        T->data[secondMin].parent = i;
        T->length++;
    }
}
void preOrder(HFTree*T,int index){      //初始化是index为-1
    if(index != -1){
        printf("%d ",T->data[index].weight);
        preOrder(T,T->data[index].lchild);
        preOrder(T,T->data[index].rchild);
    }
}
int main() {
    int weight[7] = {5,1, 3,6,11,2,4};
    int length = 7;
    HFTree *T = initTree(weight, length);
//    int *res = selectMin(T);
//    printf("res[0] = %d\n",res[0]);
//    printf("res[1] = %d",res[1]);
    createHFTree(T);
    //最后一个创建的节点为length-1
    preOrder(T,T->length - 1);
    putchar(10);
    return 0;
}