//
// Created by 86152 on 2023/6/2.
//

//Author hugo
//Time 2023/6/2 23:52
/*
 *dijkstra算法是一种广义的贪心算法
 * S数组：记录了目标顶点到其他顶点的最短路径是否求得
 * P数组：记录了目标顶点到其他顶点的最短路径的前驱节点
 * D数组：记录了目标顶点到其他顶点的最短路径的长度
 * 先确定起始状态，然后不断更新
 * 从D数组中选n-1次，选出最小的边，然后更新P和D
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
            G->arcs[i][j] = *(arcs + i * G->vexNum + j);
            if (G->arcs[i][j] != 0 && G->arcs[i][j] != MAX)
                G->arcNum++;
        }
    }
    G->arcNum /= 2;
}

/* DFS
 * 找一个节点访问
 * 照这个节点可以访问的节点
 * 重复第一步，直到所有节点访问完毕
 */
void DFS(Graph *G, int *visited, int index) { //index是一个索引
    printf("%c\t", G->vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vexNum; ++i) {
        if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX && !visited[i]) {
            DFS(G, visited, i);
        }
    }
}

int getmin(int *d, int *s, Graph *G) {
    int min = MAX;
    int index;
    for (int i = 0; i < G->vexNum; ++i) {
        if (!s[i] && d[i] < min) {
            min = d[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(Graph *G, int index) {
    //准备辅助数组
    int *s = (int *) malloc(sizeof(int) * G->vexNum);
    int *p = (int *) malloc(sizeof(int) * G->vexNum);
    int *d = (int *) malloc(sizeof(int) * G->vexNum);
    //初始化辅助数组
/*    for (int i = 0; i < G->vexNum; ++i) {
        if (i == index)
            s[i] = 1;
        else s[i] = 0;
    }
    for (int i = 0; i < G->vexNum; ++i) {
        if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX) {
            p[i] = index;
        } else p[i] = -1;
    }
    for (int i = 0; i < G->vexNum; ++i) {
        if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX)
            d[i] = G->arcs[index][i];
        else
            d[i] = MAX;
        if (i == index)
            d[i] = 0;
    }*/
    for (int i = 0; i < G->vexNum; ++i) {
        if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX) {
            d[i] = G->arcs[index][i];
            p[i] = index;
        } else {
            d[i] = MAX;
            p[i] = -1;
        }
        if (index == i) {
            s[i] = 1;
            d[i] = 0;
        } else {
            s[i] = 0;
        }
    }
//    for (int i = 0; i < G->vexNum; ++i) {
//        printf("%d %d %d\n", s[i], p[i], d[i]);
//    }
    for (int i = 0; i < G->vexNum - 1; ++i) {
        int index = getmin(d, s, G);
        s[index] = 1;
        for (int j = 0; j < G->vexNum; ++j) {
            if (!s[j] && d[index] + G->arcs[index][j] < d[j]) {
                d[j] = d[index] + G->arcs[index][j];
                p[j] = index;
            }
        }
    }
    for (int i = 0; i < G->vexNum; ++i) {
        printf("%d %d %d\n", s[i], p[i],d[i]);
    }
}

int main() {
    Graph *G = initGraph(7);
    int *visited = (int *) malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; ++i) {
        visited[i] = 0;      //初始化为0，也可以选择直接calloc
    }
    int arcs[7][7] = {
            0, 12, MAX, MAX, MAX, 16, 14,
            12, 0, 10, MAX, MAX, 7, MAX,
            MAX, 10, 0, 3, 5, 6, MAX,
            MAX, MAX, 3, 0, 4, MAX, MAX,
            MAX, MAX, 5, 4, 0, 2, 8,
            16, 7, 6, MAX, 2, 0, 9,
            14, MAX, MAX, MAX, 8, 9, 0
    };
    createGraph(G, "1234567", (int *) arcs);
    DFS(G, visited, 0);
    printf("\n");
    dijkstra(G, 0);
    return 0;
}

