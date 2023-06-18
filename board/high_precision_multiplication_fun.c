#include <stdio.h>
#include <string.h>
#define N 1005
#define M 1000005
char str1[N],str2[N];
int int1[N], int2[N];
int result[M];
int len1,len2;

void high_precision_multiplication()     //高是指高精度乘高精度
{
    len1 = strlen(str1);
    len2 = strlen(str2);
    memset(int1,0,sizeof(int1));   //清零数组
    memset(int2,0,sizeof(int2));
    memset(result,0,sizeof(result));

    for (int i = 0 ; i < len1 ; i++)
        int1[len1 - i - 1] = str1[i] - '0';    //将字符串转化为数组
    for (int i = 0 ; i < len2 ; i++)
        int2[len2 - i - 1] = str2[i] - '0';

    memset(result,0,sizeof(result));   //清零
    for (int i = 0 ; i < len1 ; i++)
        for (int j = 0 ; j < len2 ; j++)
            result[i + j] += int1[i] * int2[j];       //运算（这个就有一点复杂了）

    int l = len1 + len2 - 1;    //l是结果的最高位数
    for (int i = 0 ; i < l ;i++)
    {
        result[i + 1] += result[i] / 10;    //保证每一位的数都只有一位，并进位
        result[i] %= 10;
    }
    if (result[l] > 0) l++;     //保证最高位数是对的
    while (result[l - 1] >= 10)
    {
        result[l] = result[l - 1] / 10;
        result[l - 1] %= 10;
        l++;
    }
    while (result[l - 1] == 0 && l > 1)
        l--;                             //while去零法
    printf("%s * %s = ",str1,str2);
    for (int i = l - 1; i >= 0 ; i--)    //输出结果
        printf("%d",result[i]);
}

int main()
{
    while (scanf("%s%s",str1,str2) != EOF)
    {
        high_precision_multiplication();    //引用高精度乘法函数
        printf("\n");                 //换行
    }
    return 0;
}

