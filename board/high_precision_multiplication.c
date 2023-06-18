#include<stdio.h>
#include<string.h>

#define N 1005
#define M 1000005//N * N

char str1[N], str2[N];//存放两个大整数的字符
int int1[N], int2[N];//按低位到高位存放两个大整数的数组
int result[M];//乘积结果数组 ,按低位到高位存放
int main() {
    int i, j;//循环变量
    int digit;//进位n
    int b;//存放按位乘的结果
    int subscript;//结果数组的下标
    int len_result;
//获取两个大整数
    scanf("%s%s", str1, str2);
//按低位到高位存放两个大整数
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    for (i = 0, j = len1 - 1; i < len1; i++, j--) {
        int1[j] = str1[i] - '0';
    }
    for (i = 0, j = len2 - 1; i < len2; i++, j--) {
        int2[j] = str2[i] - '0';
    }
//char字符数组长度等于对应的int字符数组长度
//模拟竖式相乘
    for (i = 0; i < len2; i++) {
        digit = 0;//一开始相乘,进位为0
        subscript = i;
        for (j = 0; j < len1; j++) {
            b = int2[i] * int1[j] + digit + result[subscript];
            result[subscript] = b % 10;//本位
            subscript++;//为下一次做准备
            digit = b / 10;//进位
        }
        if (digit > 0) { //一次相乘，最后一次的进位
            result[subscript] = digit;
        }
    }
//输出结果
    len_result = len1 + len2;
    while (result[len_result] == 0 && len_result > 0) { // 删除前导符0
        len_result--;
    }
    for (i = len_result; i >= 0; i--) {
        printf("%d", result[i]);
    }
    return 0;
}


