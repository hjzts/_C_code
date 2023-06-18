//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 23:06
/*
 * 中序线索二叉树
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

void inThreadTree(TreeNode *T, TreeNode **pre) {
    if (T) {
        inThreadTree(T->lchild, pre);
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
        inThreadTree(T->rchild, pre);
    }
}

TreeNode *getfirst(TreeNode *T) {
    while (T->ltag == 0) {
        T = T->lchild;
    }
    return T;
}

TreeNode *getNext(TreeNode *node) {
    if (node->rtag == 1) {  //后继
        return node->rchild;
    } else {
        return getfirst(node->rchild);
    }
}

/*
 * AB##C##
 *       A
 *     B   C
 *    # # # #
 *
 * ABD##E##CF##G##
 *            A
 *      B            C
 *   D     E      F     G
 *  # #   # #    # #   # #
 */
int main(int argc, char *argv[]) {
    TreeNode *T;
    TreeNode *pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index);
    inThreadTree(T, &pre);
    pre->rtag = 1;
    pre->rchild = NULL;
    for (TreeNode *node = getfirst(T); node != NULL; node = getNext(node)) {
        printf("%c ", node->data);
    }
    putchar(10);
    return 0;
}
