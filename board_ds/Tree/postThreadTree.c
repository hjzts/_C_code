//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 23:50
/*
 * 后序线索二叉树
*/
#include <stdio.h>
#include <stdlib.h>

//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 23:06
/*
 * 后序线索二叉树
 * 将树变为了三叉链表
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aTreeNode {
    char data;
    struct aTreeNode *lchild;
    struct aTreeNode *rchild;
    struct aTreeNode *parent;
    int ltag;
    int rtag;
} TreeNode;

void createTree(TreeNode **T, char *data, int *index,TreeNode*parent) {
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
        (*T)->parent = parent;
        //创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index,*T);
        //创建左子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index,*T);
    }
}

void postThreadTree(TreeNode *T, TreeNode **pre) {
    if (T) {
        postThreadTree(T->lchild, pre);
        postThreadTree(T->rchild, pre);
        //do something
        if (T->lchild == NULL) {
            T->ltag = 1;
            T->lchild = *pre;
        }
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;
    }
}
TreeNode *getFirst(TreeNode *T) {
    while (T ->ltag == 0) {
        T = T->lchild;
    }
    if(T ->rtag == 0) {
        return getFirst(T->rchild);
    }else{
        return T;
    }
}
TreeNode *getNext(TreeNode*node) {
    if(node->rtag == 1){
        return node->rchild;
    }else{
        // 如果是根节点
        if(node->parent == NULL){
            return NULL;
        }
        // 如果是右孩子
        else if (node->parent->rchild == node){
            return node->parent;
        }
        // 如果是左孩子
        else{
            if(node->parent->rtag == 0){
                return getFirst(node->parent->rchild);
            }else{
                return node->parent;
            }
        }
    }
}
int main(int argc, char *argv[]) {
    TreeNode *T;
    TreeNode *pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index,NULL);
    postThreadTree(T, &pre);
    //后序不能有这个
//    pre->rtag = 1;
//    pre->rchild = NULL;
    for (TreeNode *node= getFirst(T);  node != NULL ; node = getNext(node)){
        printf("%c ",node->data);
    }
    putchar(10);
    return 0;
}

