#include <stdio.h>

typedef int ElemType;
#define MAXSIZE 1000
typedef struct SLinked {
    ElemType data;      //数据域
    int cur;            //指针域
} SLinkedList[MAXSIZE];

//若空闲链表非空，则返回分配的结点下标，否则返回0
int AllocNode(SLinkedList space) {
    int i;
    i = space[0].cur;
    if (i == 0) return 0;
    space[0].cur = space[i].cur;
    return i;
}
//将下标为i的空闲结点回收到备用链表,即空闲链表
void FreeNode(SLinkedList space ,int i){
    space[i].cur = space[0].cur;        //相当于头插法插到了空闲表头的后面
    space[0].cur = i;
}


//1.静态链表的初始化；在存储数组中建立空闲链表。
void InitList(SLinkedList space) {
    for (int i = 0; i < MAXSIZE - 1; ++i) {
        space[i].cur = i + 1;
    }
    space[MAXSIZE].cur = 0;
}
//2.创建一个含有n个节点的静态链表，返回表头在存储数组中的位置
int CreateList(SLinkedList space,int n){
    int head,p,r;
    p = AllocNode(space);
    head = p;
    for (int i = 1; i <= n; ++i) {
        r = AllocNode(space);
        scanf("%d",&space[r].data);
        space[p].cur = r;
        p = r;
    }
    space[p].cur = 0;
    return  head;
}
//3.创建一个含有n个节点的静态链表，在第i个节点之前插入一个值为x的新节点
int Insert(SLinkedList space, int head, int i, ElemType x) {
    if(i < 1) return 0;
    int p = head;
    int j = 0;      //  计数器
    while (p != 0 && j < i - 1){
        p = space[p].cur;
        j++;
    }
    if(p == 0) return 0; //没有第i个节点，也就是说没有空间可插入
    int q = AllocNode(space);//从空闲链表中获得节点，q为该节点下标
    if(q != 0){
        space[q].data = x;
        space[q].cur = space[p].cur;
        space[p].cur = q;
        return 1;
    }
    else return 0;
}
//4.在以head为表头的静态链表中，删除静态链表中的第i个节点
int Delete(SLinkedList space,int head ,int i,ElemType * e){
    if(i < 1) return 0;
    int p = head;
    int j = 0;
    while (p && j < i -1){
        j++;
        p = space[p].cur;
    }
    if(!space[p].cur) return 0;     //不能让p指向最后一个节点
    int q = space[p].cur;
    *e = space[q].data;
    space[p].cur = space[q].cur;
    FreeNode(space,q);
    return 1;
}
//5.在以head为表头的静态链表中，确定第一个值为x的节点的位置
int Locate(SLinkedList space,int head ,ElemType x){
    int p = space[head].cur;
    while (space[p].cur != x && p ){
        p = space[p].cur;
    }
    if(!p) return 0;
    return p;
}

SLinkedList s;

void MergeAB(SLinkedList space,int ha,int hb){
    int k = space[hb].cur;
    int x,i,e;
    while (k){
        x = space[k].data;
        i = Locate(space,ha,x);
        if(!i){
            Insert(space ,ha,1,x);
        }else{
            int m = space[ha].cur;
            int j = 1;
            while (space[m].data != x){
                j++;
                m = space[m].cur;
            }
            Delete(space,ha,j,&e);
        }
        k = space[k].cur;
    }
}

int main() {

    return 0;
}