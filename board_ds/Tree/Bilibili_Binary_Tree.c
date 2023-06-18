//
// Created by 86152 on 2023/6/16.
//

//Author hugo
//Time 2023/6/16 17:06
/*
 *����ʵ���˶������Ĵ����ͱ���
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
    //������ĳ�*index++;�ͻᱨ������
    *index += 1;
    if (ch == '#') {
        //��ʱΪ�սڵ�
        *T = NULL;
    } else {
        //��ʱ��Ϊ��
        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T)->data = ch;
        //�������������߼�һ�£����еݹ�
        createTree(&((*T)->lchild), data, index);
        //�������������߼�һ�£����еݹ�
        createTree(&((*T)->rchild), data, index);
    }
}

void preOrder(TreeNode *T) {
    if (T == NULL) {
        return;
    } else {
        // �Ȱ���
        printf("%c", T->data);
        // ��������
        preOrder(T->lchild);
        // �����Һ���
        preOrder(T->rchild);
    }
}
void inOrder(TreeNode *T){
    if (T == NULL) {
        return;
    } else {
        // ��������
        inOrder(T->lchild);
        // �а���
        printf("%c", T->data);
        // �����Һ���
        inOrder(T->rchild);
    }
}
void postOrder(TreeNode*T){
    if (T == NULL) {
        return;
    } else {
        // ��������
        preOrder(T->lchild);
        // �����Һ���
        preOrder(T->rchild);
        // �����
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
