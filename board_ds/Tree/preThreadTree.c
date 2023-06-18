//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 23:33
/*
 * 先序线索二叉树
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
    //把这里改成*index++;就会报错？？？
    *index += 1;
    if (ch == '#') {
        //此时为空节点
        *T = NULL;
    } else {
        //此时不为空
        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T)->data = ch;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        //创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index);
        //创建左子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index);
    }
}

//线索化的过程实际上就是一个遍历的过程
void preThreadTree(TreeNode *T, TreeNode **pre) {
    if (T) {
        //do something
        if (T->lchild == NULL) {
            T->ltag = 1;
            T->lchild = *pre;       //在这里已经改变了左孩子
        }
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;
        if (T->ltag == 0)       //需要补充这个
            preThreadTree(T->lchild, pre);
        preThreadTree(T->rchild, pre);
    }
}

TreeNode *getNext(TreeNode *node) {
    if (node->rtag == 1 || node->ltag == 1) {
        return node->rchild;
    } else {
        return node->lchild;
    }//下面这个精简化之后
/*    if (node->rtag == 1) {
        return node->rchild;
    } else {
        if (node->ltag == 0) {
            return node->lchild;       //根左右
        } else {
            return node->rchild;        //左子树遍历完之后为右子树
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