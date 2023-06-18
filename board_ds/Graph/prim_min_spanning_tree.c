//
// Created by 86152 on 2023/6/2.
//

//Author hugo
//Time 2023/6/2 20:08
/*
 * ����prim�㷨ʵ����С������
 * MST���ʣ�(V,E)��һ����ͨͼ����ô����U��V��һ���ǿ��Ӽ���(u,v)��һ����СȨֵ�ıߣ���ô���u����U,v����V-U,��ô����(u,v)��������С��������
 * prim�ҵ㷨�����ǴӼ����и��ݱߵ�Ȩֵ�ҵ�
 * ͼ����֮�䲻ͨ����ô�ڽӾ����ֵΪMAX
 * ����������Լ�������ôֵΪ0
 * ʵ��prim�㷨��
 * ��¼��ǰU���ϵ�״̬
 * ѡ����С���Լ�������뵽U������
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
    char vex;       //��¼U���ϵ���С�ߵ���ʼ�ڵ�
    int weight;     //��¼��С��
} Edge;
/*
 * ��ʼ��ʱ�����ж������Ϣ����edge[i].vex
 * ͬʱ����index�����е�weight����ʱ��weight
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
 * ��edge.weight = 0ʱ����������뵽U���ϵ���
 * ��������û�м��뵽�ü��ϵĶ���
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
        //����һ������min֮��ѭ��һȦ����weight
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

void DFS(Graph *G, int *visited, int index) { //index��һ������
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
        visited[i] = 0;      //��ʼ��Ϊ0��Ҳ����ѡ��ֱ��calloc
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

