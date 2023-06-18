#include <stdio.h>
#include <string.h>

#define N 1005

char str1[N], str2[N];//用str数组来接收两个数
int int1[N], int2[N];//准备两个数组准备倒序
int result[N];//准备一个数组用来存入两数相加后的数据
int len1, len2, len_result;

int inverse_order(char str[], int len, int k);//倒序初始数组
int MAX(int x, int y);//比大小函数
void sum(int ARR1[], int ARR2[], int ARR3[]);//加法函数
void print(int final_arr[]);//倒序打印函数

int main() {
    int i;//循环变量
    scanf("%s%s", str1, str2);
    //倒序
    len1 = strlen(str1);
    len2 = strlen(str2);

    for (i = 0; i < len1; i++) {
        int1[i] = inverse_order(str1, len1, i);
    }
    for (i = 0; i < len2; i++) {
        int2[i] = inverse_order(str2, len2, i);
    }

    //将两数和的数据存入sum1中
    sum(int1, int2, result);

    //倒序打印存有两数和的数组
    print(result);
    return 0;
}

int inverse_order(char str[], int len, int k) {
    return (str[len - 1 - k] - '0');
}

int MAX(int x, int y) {
    return x > y ? x : y;
}

void sum(int ARR1[], int ARR2[], int ARR3[]) {
    int i;
    len_result = MAX(len1, len2);
    int tmp = 0;
    for (i = 0; i < len_result + 1; i++) {
        ARR3[i] = (ARR1[i] + ARR2[i] + tmp) % 10;
        tmp = (ARR1[i] + ARR2[i] + tmp) / 10;
    }
    if (tmp != 0) {
        ARR3[++len_result]++;
    }
}

void print(int final_arr[]) {
    int left = 0;
    int right = len_result;
    int i;
    for (i = len_result; i > 0; i--) {
        if (final_arr[i] != 0) {
            right = i;
            break;
        }
    }
    while (left <= right) {
        printf("%d", final_arr[right]);
        right--;
    }
}