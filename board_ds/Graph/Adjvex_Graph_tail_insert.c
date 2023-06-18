//
// Created by 86152 on 2023/6/5.
//

//Author hugo
//Time 2023/6/5 15:28
/*
 * 这里是用邻接表来表示图
 * 本题是需要寻找独立路径，问题在于本题中出现了多重图，因此用邻接矩阵不便于解决这个问题
 * 我们采用更加合适的数据结构也就是邻接表来表示图
 * 同时我这个插入一条边是采取的尾插法，因此我插入一条边是比较麻烦
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1001
#define arc_length 3    //表示我输入的arcs中一行有以几个分量，也就是arcs有几列

//我的图封装得很好哈哈哈哈
typedef struct aGraph {
    struct arcNode {
        int adjvex;                 //记录边节点指向的节点
        struct arcNode *nextArc;
        int num;                    //记录边节点的编号
    };
    struct vexNode {
        int data;
        struct arcNode *firstArc;
    };
    struct vexNode *vexs;
    int vexNum;
    int arcNum;
} Graph;

Graph *initGraph(int vexNum, int arcNum) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    G->vexs = (struct VexNode *) malloc(sizeof(struct vexNode) * vexNum);
    for (int i = 0; i < vexNum; i++) {
        G->vexs[i].data = 0;
        G->vexs[i].firstArc = NULL;
    }
    G->vexNum = vexNum;
    G->arcNum = arcNum;
    return G;
}

void createGraph(Graph *G, int *vexs, int *arcs) {

    for (int i = 0; i < G->vexNum; ++i) {
        G->vexs[i].data = vexs[i];
    }

    for (int i = 0; i < G->arcNum; ++i) {
        int k = arcs[arc_length * i + arc_length - 2];
        struct arcNode *p = G->vexs[k].firstArc;
        if (p == NULL) {
            p = (struct arcNode *) malloc(sizeof(struct arcNode));
            p->adjvex = arcs[arc_length * i + arc_length - 1];
            p->num = arcs[arc_length * i];
            p->nextArc = NULL;
            G->vexs[k].firstArc = p;
        } else {
            struct arcNode *q = p;
            while (p != NULL) {
                q = p;
                p = p->nextArc;
            }
            p = (struct arcNode *) malloc(sizeof(struct arcNode));
            p->adjvex = arcs[arc_length * i + arc_length - 1];
            p->num = arcs[arc_length * i];
            p->nextArc = NULL;
            q->nextArc = p;
        }

        k = arcs[arc_length * i + arc_length - 1];
        p = G->vexs[k].firstArc;
        if (p == NULL) {
            p = (struct arcNode *) malloc(sizeof(struct arcNode));
            p->adjvex = arcs[arc_length * i + arc_length - 2];
            p->num = arcs[arc_length * i];
            p->nextArc = NULL;
            G->vexs[k].firstArc = p;
        } else {
            struct arcNode *q = p;
            while (p != NULL) {
                q = p;
                p = p->nextArc;
            }
            p = (struct arcNode *) malloc(sizeof(struct arcNode));
            p->adjvex = arcs[arc_length * i + arc_length - 2];
            p->num = arcs[arc_length * i];
            p->nextArc = NULL;
            q->nextArc = p;
        }
    }

}

void printGraph(Graph *G) {
    for (int i = 0; i < G->vexNum; ++i) {
        struct arcNode *p = G->vexs[i].firstArc;
        if (p == NULL) continue;
        else {
            printf("%d : ", G->vexs[i].data);
            while (p != NULL) {
                printf("%d ", p->adjvex);
                p = p->nextArc;
            }
            putchar(10);
        }
    }
}

void findPath(Graph *G, int index, int v_end, int *visited, int *path, int depth) {
    if (index == v_end) {
        for (int i = 0; i < depth; ++i) {
            printf("%d ", path[i]);
        }
        putchar(10);
        return;
    } else {
        struct arcNode *p;
        for (p = G->vexs[index].firstArc; p != NULL; p = p->nextArc) {
            if (!visited[p->adjvex]) {
                path[depth] = p->num;
                visited[p->adjvex] = 1;
                findPath(G, p->adjvex, v_end, visited, path, depth + 1);
                visited[p->adjvex] = 0;
            }
        }
    }
}

int main() {

    setbuf(stdout,0);
    int vexNum, arcNum;
    scanf("%d%d", &vexNum, &arcNum);

    Graph *G = initGraph(vexNum, arcNum);
    int *visited = (int *) malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; ++i) {
        visited[i] = 0;
    }
    visited[0] = 1;
    int *path = (int *) malloc(sizeof(int) * G->vexNum);
    int arcs[MAXSIZE][arc_length];
    for (int i = 0; i < arcNum; ++i) {
        for (int j = 0; j < arc_length; ++j) {
            scanf("%d", &arcs[i][j]);
        }
    }


    int *vexs = (int *) malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; ++i) {
        vexs[i] = i;
    }
    createGraph(G, vexs, (int *) arcs);

    printGraph(G);

    findPath(G, 0, vexNum - 1, visited, path, 0);
    return 0;
}