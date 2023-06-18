#include <stdio.h>

int find_lowerbound(int dst[], int key, int lef, int rit) {//左边界查找函数
    int mid = (lef + rit) / 2; //为了找左边界，一般向左端取整
    while (lef < rit)//左右位置索引相同时表示找到唯一可能边界
    {
        if (dst[mid] >= key)//中间值大于等于key
// 向左搜索
        {
            rit = mid;
        } else //中间值小于key
        {
            lef = mid + 1; //由于是左端取整，需要对左位置索引+1以保证能够搜到边界
        }
        mid = (lef + rit) / 2;//保证向左端取整
    }
//判断边界是否可行
    if (dst[mid] == key)
        return mid;
    else
        return -1;
}

int find_upperbound(int dst[], int key, int lef, int rit) {//右边界查找函数
    int mid = (lef + rit + 1) / 2; //向右端取整
    while (lef < rit) {
        if (dst[mid] > key)//中间值大于key
// 向左搜索
        {
            rit = mid - 1;
        } else //中间值小于等于key
        {
            lef = mid;
        }
        mid = (lef + rit + 1) / 2;
    }
    if (dst[mid] == key)
        return mid;
    else
        return -1;
}

int main() {
    int n, a[50];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    int key;
    scanf("%d", &key);
    int left = find_lowerbound(a, key, 0, n - 1);
    int right = find_upperbound(a, key, 0, n - 1);
    printf("%d %d",left + 1,right + 1);
    return 0;
}