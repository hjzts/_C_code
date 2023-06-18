//
// Created by 86152 on 2023/6/2.
//

//Author hugo
//Time 2023/6/2 18:30
/*
 * 使用邻接矩阵来创建图并进行遍历
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
typedef struct aGraph {
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
} Graph;

Graph *initGraph(int vexNum) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    G->vexs = (char *) malloc(sizeof(char) * vexNum);
    G->arcs = (int **) malloc(sizeof(int *) * vexNum);
    for (int i = 0; i < vexNum; ++i) {
        G->arcs[i] = (int *) malloc(sizeof(int) * vexNum);
    }
    G->vexNum = vexNum;
    G->arcNum = 0;
    return G;
}

void createGraph(Graph *G, char *vexs, int *arcs) {
    for (int i = 0; i < G->vexNum; ++i) {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexNum; ++j) {
            G->arcs[i][j] = *(arcs + i * (G->vexNum) + j);
            if (G->arcs[i][j] != 0) {
                G->arcNum++;
            }
        }
    }
    G->arcNum /= 2;
}
/* DFS
 * 找一个节点访问
 * 照这个节点可以访问的节点
 * 重复第一步，直到所有节点访问完毕
 */
void DFS(Graph * G,int *visited,int index){ //index是一个索引
    printf("%c\t",G->vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vexNum; ++i) {
        if(G->arcs[index][i] == 1 && !visited[i]) {
            DFS(G,visited,i);
        }
    }
}
/* BFS
 * 类似树的层次遍历
 * 利用到队列
 */
typedef struct aQueue{
    int front;
    int rear;
    int data[MAXSIZE];
}Queue;
Queue  * initQueue(){
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->front = Q->rear = 0;
    return Q;
}
int isFull(Queue * Q){
    if((Q->rear + 1 )% MAXSIZE == Q->front){
        return 1;
    }
    return 0;
}
int isEmpty(Queue * Q){
    if(Q->front== Q-> rear){
        return 1;
    }
    return 0;
}
int enQueue(Queue *Q,int data){
    if(isFull(Q)){
        return 0;
    }else{
        Q ->data[Q->rear] = data;
        Q->rear = (Q->rear + 1) % MAXSIZE;
        return 1;
    };
}
int deQueue(Queue *Q){
    if(isEmpty(Q)){
        return -1;
    }
    else{
        int data = Q->data[Q->front];
        Q ->front  = (Q->front + 1) % MAXSIZE;
        return data;
    }
}
void BFS(Graph *G,int* visited,int index){
    Queue *Q = initQueue();
    printf("%c\t",G->vexs[index]);
    visited[index] = 1;
    enQueue(Q,index);
    while (!isEmpty(Q)){
        int i = deQueue(Q);
        for (int j = 0; j < G->vexNum; ++j) {
            if(G -> arcs[i][j] == 1 && !visited[j]){
                printf("%c\t",G->vexs[j]);
                visited[j] = 1;
                enQueue(Q,j);
            }
        }
    }
}
int main() {
    Graph *G = initGraph(5);
    int *visited = (int *)malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; ++i) {
        visited[i] = 0;      //初始化为0，也可以选择直接calloc
    }
    int arcs[5][5] = {
            0, 1, 1, 1, 0,
            1,  0, 1, 1, 1,
            1, 1, 0, 0, 0,
            1, 1, 0, 0, 1,
            0, 1, 0, 1, 0
    };
    createGraph(G,"ABCDE",(int*)arcs);
    DFS(G,visited,0);
    printf("\n");
    for (int i = 0; i < G->vexNum; ++i) {
        visited[i] = 0;
    }
    BFS(G,visited,0);
    printf("\n");
    return 0;
}
