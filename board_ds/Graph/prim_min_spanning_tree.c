//
// Created by 86152 on 2023/6/2.
//

//Author hugo
//Time 2023/6/2 20:08
/*
 * 利用prim算法实现最小生成树
 * MST性质，(V,E)是一个连通图，那么假设U是V的一个非空子集，(u,v)是一条最小权值的边，那么如果u属于U,v属于V-U,那么必有(u,v)包含在最小生成树中
 * prim找点法，我们从集合中根据边的权值找点
 * 图顶点之间不通，那么邻接矩阵的值为MAX
 * 如果顶点是自己本身，那么值为0
 * 实现prim算法：
 * 记录当前U集合的状态
 * 选择最小边以及顶点加入到U集合中
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 32767
typedef struct aGraph {
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
} Graph;

typedef struct aEdge {
    char vex;       //记录U集合到最小边的起始节点
    int weight;     //记录最小边
} Edge;
/*
 * 初始化时将所有顶点的信息存入edge[i].vex
 * 同时存入index的所有的weight即此时的weight
 */
Edge *initEdge(Graph*G,int index){
    Edge *edge = (Edge*)malloc(sizeof(Edge) * G->vexNum);
    for (int i = 0; i < G->vexNum; ++i) {
        edge[i].vex = G->vexs[index];
        edge[i].weight = G->arcs[index][i];
    }
    return edge;
}
/*
 * 当edge.weight = 0时，代表顶点加入到U集合当中
 * 对于所有没有加入到该集合的顶点
*/
int getMinEdge(Edge *edge,Graph *G){
    int index;
    int min = MAX;
    for (int i = 0; i < G->vexNum; ++i) {
        if(edge[i].weight != 0 && min > edge[i].weight){
            min = edge[i].weight;
            index = i;
        }
    }
    return index;
}
void prim(Graph *G,int index){
    int min;
    Edge *edge = initEdge(G,index);
    for (int i = 0; i < G->vexNum - 1; ++i) {
        min = getMinEdge(edge,G);
        printf("v%c --> v%c,weight = %d\n",edge[min].vex,G->vexs[min],edge[min].weight);
        edge[min].weight = 0;
        //加入一个顶点min之后，循环一圈更新weight
        for (int j = 0; j < G->vexNum; ++j) {
            if(G ->arcs[min][j] < edge[j].weight){
                edge[j].weight = G->arcs[min][j];
                edge[j].vex = G->vexs[min];
            }
        }
    }
}
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
            if (G->arcs[i][j] != 0 && G->arcs[i][j] != MAX) {
                G->arcNum++;
            }
        }
    }
    G->arcNum /= 2;
}

void DFS(Graph *G, int *visited, int index) { //index是一个索引
    printf("%c\t", G->vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vexNum; ++i) {
        if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX && !visited[i]) {
            DFS(G, visited, i);
        }
    }
}

int main() {
    Graph *G = initGraph(6);
    int *visited = (int *) malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; ++i) {
        visited[i] = 0;      //初始化为0，也可以选择直接calloc
    }
    int arcs[6][6] = {
            0, 600, 100, 500, MAX, MAX,
            600, 0, 500, MAX, 300, MAX,
            100, 500, 0, 500, 600, 400,
            500, MAX, 500, 0, MAX, 200,
            MAX, 300, 600, MAX, 0, 600,
            MAX, MAX, 400, 200, 600, 0
    };
    createGraph(G, "123456", (int *) arcs);
    DFS(G,visited,0);
    printf("\n");
    prim(G,0);
    return 0;
}

