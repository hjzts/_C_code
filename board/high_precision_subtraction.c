#include<stdio.h>
#include<string.h>
#define MAX(a,b) a > b ? a : b
#define N 999

char str1[N], str2[N], temp[N];
int int1[N], int2[N];
int result[N];

int main(void) {
    int i;
    int flag = 0;
    scanf("%s%s", str1, str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len_max = MAX(len1,len2);
    if (strlen(str2) > strlen(str1) || (strlen(str1) == strlen(str2) && strcmp(str2, str1) > 0)) {
        //使被减数大于减数，长度相同时需用函数strcmp判断大小
        strcpy(temp, str1);
        strcpy(str1, str2);
        strcpy(str2, temp);
        //交换数据
        printf("-");  //结果为负
    }

    for (i = 0; i < strlen(str1); i++) {
        int1[i] = str1[strlen(str1) - 1 - i] - '0';
    }
    for (i = 0; i < strlen(str2); i++) {
        int2[i] = str2[strlen(str2) - 1 - i] - '0';
    }

    for (i = 0; i <= len_max; i++) {
        result[i] = int1[i] - int2[i];
        if (result[i] < 0) {
            result[i] += 10;    //向上借位
            int1[i + 1]--;
        }
    }
    for (i = len_max; i >= 0; i--) {  //逆序打印
        if (result[i] != 0)
            flag = 1;
        if (flag != 0)
            printf("%d", result[i]);
    }
    if (flag == 0) printf("0");  //特判！
    return 0;
}
