//
// Created by 86152 on 2023/6/17.
//

//Author hugo
//Time 2023/6/17 00:16
/*
 * ¶ş²æ²éÕÒÊ÷
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct aTreeNode {
    int data;
    struct aTreeNode *lchild;
    struct aTreeNode *rchild;
} TreeNode;

TreeNode *bstSearch(TreeNode *T, int data) {
    if (T) {
        if (T->data == data) {
            return T;
        } else if (data < T->data) {
            return bstSearch(T->lchild, data);
        } else {
            return bstSearch(T->rchild, data);
        }
    }
}

void bstInsert(TreeNode **T, int data) {
    if (*T == NULL) {
        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T)->data = data;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
    } else if (data == (*T)->data) {
        return;
    } else if (data < ((*T)->data)) {
        bstInsert(&((*T)->lchild), data);
    } else {
        bstInsert(&((*T)->rchild), data);
    }
}

void preOrder(TreeNode *T) {
    if (T != NULL) {
        printf("%d ", T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}
/*
 *      4
 *    2   5
 *          19
 *         8   23
 */
int main() {
    TreeNode *T = NULL;
    int nums[6] = {8,6,10,9,11,23};
//    int nums[6] = {4, 5, 19, 23, 2, 8};
    for (int i = 0; i < 6; i++) {
        bstInsert(&T, nums[i]);
    }
    preOrder(T);
    putchar(10);
    return 0;
}