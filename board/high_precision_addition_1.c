#include<stdio.h>
#include<string.h>
#define MAX(a,b) a > b ? a : b
#define N 999

char str1[N], str2[N];
int int1[N] , int2[N];//初始化为0，方便后续输出
int result[N];
int main() {
    int i;//循环变量
    int digit;//用来进位
    int len_result;
    int flag = 0;    //使用flag判断最高位并实现输出
    scanf("%s%s", str1, str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len_max = MAX(len1,len2);//len_max用来记录最大字符串长度，以便相加、输出

    //将低位放前面，高位放后面，以便进位
    for (i = 0; i < len1; i++) {
        int1[i] = str1[len1 - 1 - i] - '0';
    }
    for (i = 0; i < len2; i++) {
        int2[i] = str2[len2 - 1 - i] - '0';
    }

    for (i = 0; i <= len_max; i++) {    //不要忘了“=”
        result[i] = int1[i] + int2[i] + digit;
        digit = result[i] / 10;
        result[i] %= 10;
    }

    for (i = len_max; i >= 0; i--) {    //倒序输出
        if (result[i] != 0)
            flag = 1;
        if (flag != 0)
            printf("%d", result[i]);
    }
    if (flag == 0) printf("0");  //特判 0；
    return 0;
}
