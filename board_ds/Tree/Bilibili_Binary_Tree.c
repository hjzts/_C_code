//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 17:06
/*
 *这里实现了二叉树的创建和遍历
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aTreeNode {
    char data;
    struct aTreeNode *lchild;
    struct aTreeNode *rchild;
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
        //创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index);
        //创建左子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index);
    }
}

void preOrder(TreeNode *T) {
    if (T == NULL) {
        return;
    } else {
        // 先办事
        printf("%c", T->data);
        // 处理左孩子
        preOrder(T->lchild);
        // 处理右孩子
        preOrder(T->rchild);
    }
}
void inOrder(TreeNode *T){
    if (T == NULL) {
        return;
    } else {
        // 处理左孩子
        inOrder(T->lchild);
        // 中办事
        printf("%c", T->data);
        // 处理右孩子
        inOrder(T->rchild);
    }
}
void postOrder(TreeNode*T){
    if (T == NULL) {
        return;
    } else {
        // 处理左孩子
        preOrder(T->lchild);
        // 处理右孩子
        preOrder(T->rchild);
        // 后办事
        printf("%c", T->data);
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
    int index = 0;
    createTree(&T, argv[1], &index);
    printf("preOrder:\t");
    preOrder(T);
    putchar(10);
    printf("inOrder:\t");
    inOrder(T);
    putchar(10);
    printf("postOrder:\t");
    postOrder(T);
    return 0;
}
