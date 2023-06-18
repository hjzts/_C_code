#include <stdio.h>

//快速排序
void quick_sort(int num[], int low, int high) {
    int i, j, temp;
    int tmp;
    i = low;
    j = high;
    tmp = num[low];   //任命为中间分界线，左边比他小，右边比他大,通常第一个元素是基准数
    if (i > j) {  //如果下标i大于下标j，函数结束运行
        return;
    }
    while (i != j) {
        while (num[j] <= tmp && j > i) {
            j--;
        }
        while (num[i] >= tmp && j > i) {
            i++;
        }
        if (j > i) {
            temp = num[j];
            num[j] = num[i];
            num[i] = temp;
        }
    }
    num[low] = num[i];
    num[i] = tmp;
    quick_sort(num, low, i - 1);
    quick_sort(num, i + 1, high);
}

int a[50];
int main(){
    for (int i = 0; i < 50; ++i) {
        scanf("%d",&a[i]);
    }
    quick_sort(a,0,49);
    for (int i = 0; i < 50; ++i) {
        printf("%d ",a[i]);
    }
    return 0;
}
/*
4 5 4 6 8 9 7 25 45 65 32 98 45 81 92 63 64 31 97 35 82 65 54 25 65 25 65 54 64 54 65 45 1 6 2 3 5 4 8 9 5 4 5 5 6 2 3 6 6 6
 */
