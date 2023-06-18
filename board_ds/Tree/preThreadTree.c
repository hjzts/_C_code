//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 23:33
/*
 * ��������������
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aTreeNode {
    char data;
    struct aTreeNode *lchild;
    struct aTreeNode *rchild;
    int ltag;
    int rtag;
} TreeNode;

void createTree(TreeNode **T, char *data, int *index) {
    char ch;
//    scanf("%c\n", &ch);
    ch = data[*index];
    //������ĳ�*index++;�ͻᱨ������
    *index += 1;
    if (ch == '#') {
        //��ʱΪ�սڵ�
        *T = NULL;
    } else {
        //��ʱ��Ϊ��
        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T)->data = ch;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        //�������������߼�һ�£����еݹ�
        createTree(&((*T)->lchild), data, index);
        //�������������߼�һ�£����еݹ�
        createTree(&((*T)->rchild), data, index);
    }
}

//�������Ĺ���ʵ���Ͼ���һ�������Ĺ���
void preThreadTree(TreeNode *T, TreeNode **pre) {
    if (T) {
        //do something
        if (T->lchild == NULL) {
            T->ltag = 1;
            T->lchild = *pre;       //�������Ѿ��ı�������
        }
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;
        if (T->ltag == 0)       //��Ҫ�������
            preThreadTree(T->lchild, pre);
        preThreadTree(T->rchild, pre);
    }
}

TreeNode *getNext(TreeNode *node) {
    if (node->rtag == 1 || node->ltag == 1) {
        return node->rchild;
    } else {
        return node->lchild;
    }//�����������֮��
/*    if (node->rtag == 1) {
        return node->rchild;
    } else {
        if (node->ltag == 0) {
            return node->lchild;       //������
        } else {
            return node->rchild;        //������������֮��Ϊ������
        }
    }*/
}

int main(int argc, char *argv[]) {
    TreeNode *T;
    TreeNode *pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index);
    preThreadTree(T, &pre);
    for (TreeNode  *node=  T; node != NULL ;node = getNext(node)) {
        printf("%c ",node->data);
    }
    putchar(10);
    return 0;
}