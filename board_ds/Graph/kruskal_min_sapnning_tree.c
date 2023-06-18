//
// Created by 86152 on 2023/6/2.
//

//Author hugo
//Time 2023/6/2 20:51
/*
 * MST性质，(V,E)是一个连通图，那么假设U是V的一个非空子集，(u,v)是一条具有最小权值的边，那么如果u属于U,v属于V-U,那么必有(u,v)包含在最小生成树中
 * kusukal找边法，对边排序然后选边
 * 维护一个边的数组并排序
 * 判断一个图是否连通
 *  --->需要一个辅助数组，来去记录当前索引的节点所属于哪个连通分量
 *
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
    int start;
    int end;
    int weight;
} Edge;

Edge *initEdge(Graph *G) {
    int index = 0;
    Edge *edge = (Edge *) malloc(sizeof(Edge) * G->arcNum);
    for (int i = 0; i < G->vexNum; ++i) {
        for (int j = i + 1; j < G->vexNum; ++j) {       //考虑到无向图的邻接矩阵的对称性，我们只需要对于后面的一部分进行赋值即可
            if (G->arcs[i][j] != MAX) {
                edge[index].start = i;
                edge[index].end = j;
                edge[index].weight = G->arcs[i][j];
                index++;
            }
        }
    }
    return edge;
}

//对边进行排序
void sortEdge(Edge *edge, Graph *G) {
    Edge temp;
    for (int i = 0; i < G->arcNum - 1; ++i) {
        for (int j = 0; j < G->arcNum - i - 1; ++j) {
            if (edge[j].weight > edge[j + 1].weight) {
                temp = edge[j];
                edge[j] = edge[j + 1];
                edge[j + 1] = temp;
            }
        }
    }
}

void kruskal(Graph *G) {
    int *connected = (int *) malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; ++i) {
        connected[i] = i;
    }
    //连通分量
    Edge *edge = initEdge(G);
    sortEdge(edge, G);
    for (int i = 0; i < G->arcNum; ++i) {
        //开始选边
        int start = connected[edge[i].start];
        int end = connected[edge[i].end];
        if (start != end) {
            printf("v%c --> v%c weight = %d\n", G->vexs[edge[i].start], G->vexs[edge[i].end], edge[i].weight);
            //更新连通分量
            for (int j = 0; j < G->vexNum; ++j) {
                if (connected[j] == end) {
                    connected[j] = start;
                }
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
    setbuf(stdout, NULL);
    Graph *G = initGraph(6);
    int *visited = (int *) malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; ++i) {
        visited[i] = 0;      //初始化为0，也可以选择直接calloc
    }
    int arcs[6][6] = {
            0, 6, 1, 5, MAX, MAX,
            6, 0, 5, MAX, 3, MAX,
            1, 5, 0, 5, 6, 4,
            5, MAX, 5, 0, MAX, 2,
            MAX, 3, 6, MAX, 0, 6,
            MAX, MAX, 4, 2, 6, 0
    };
    createGraph(G, "123456", (int *) arcs);
    DFS(G, visited, 0);
    printf("\n");
    kruskal(G);
    return 0;
}
