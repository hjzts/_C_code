#include <stdio.h>
//冒泡排序
void bubble(int a[],int n) {
    int j, hold, flag = 0;
    if (n <= 1) // 只剩一个数，已排序，直接返回
        return;
    for (j = 0; j < n - 1; j++) // 一遍扫描，找最大值
        if (a[j] > a[j + 1]) // a 是全局数组
        {
            hold = a[j];
            a[j] = a[j + 1];
            a[j + 1] = hold;
            flag = 1;
        }
    if (0 == flag)
        return; // 无交换，则已排好序，返回
    bubble(a,n - 1);// 递归，对剩下n-1个数继续冒泡
}//递归冒泡
void _bubble(int a[],int n) {
    int tmp;
    for (int i = 1; i < n; ++i) {
        int flag = 0;
        for (int j = 0; j < n - 1; ++j) {
            if(a[j] > a[j + 1]){
                flag = 1;
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
        if(0 == flag){
            break;
        }
    }
}//循环冒泡
//冒泡排序通用版
int greater(const int *e1,const int *e2){
    return *e1 > *e2;
}//整型形降序
int lower(const int *e1,const int *e2){
    return *e1 < *e2;
}//整型形升序
void swap_elem(void *e1, void *e2, int elemSize){
    int i;
    char tmp;
    for (i = 0; i < elemSize; ++i)
    {
        tmp = *(char *)(e1 + i);
        *(char *)(e1 + i) = *(char *)(e2 + i);
        *(char *)(e2 + i) = tmp;
    }
}
void Bubbel_plus(void *array,int len ,int elemSize ,int (*cmp)(const void *,const void *)){
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len - i; ++j) {
            if(cmp(array + (j + 1) * elemSize,array + j * elemSize))
                swap_elem(array + j * elemSize,array + (j + 1) *elemSize,elemSize);
        }
    }
}

int a[50];
int main(){
    for (int i = 0; i < 50; ++i) {
        scanf("%d",&a[i]);
    }
//    bubble(a,50);
//    _bubble(a,50);
    Bubbel_plus(a,49,sizeof (int ),lower);
    for (int i = 0; i < 50; ++i) {
        printf("%d ",a[i]);
    }
    return 0;
}
/*
4 5 4 6 8 9 7 25 45 65 32 98 45 81 92 63 64 31 97 35 82 65 54 25 65 25 65 54 64 54 65 45 1 6 2 3 5 4 8 9 5 4 5 5 6 2 3 6 6 6
 */