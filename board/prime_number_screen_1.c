#include <stdio.h>
int main()
{
    int Not_Prime[10020] = {}, Prime[10020] = {}, cnt = 0;
// Not_Prime表示判定一个数是否不是质数，若NotPrime[i]=1表示i不是质数，0则是
// Prime为质数表，cnt为质数的计数器
    for (int i = 2; i <= 10000; i++) //统计10000以内的质数
    {
        if (Not_Prime[i]) //如果不是质数，则跳过，继续判断下一个数
            continue;
        Prime[cnt++] = i;
//如果是质数，那么Prime[cnt] = i，记录这个质数。在这之后，cnt++，计数器加一
        for (int j = 2; i * j <= 10000; j++)
            Not_Prime[i * j] = 1; //给这个质数的倍数标记为非质数
    }
    int t, n;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        scanf("%d", &n);
        int flag = 1; //记录是否找到
        for (int j = 0; j < cnt && flag; j++) //若找到，即flag为0时跳出循环
        { //遍历质数表,
            for (int k = cnt - 1; Prime[j] + Prime[k] >= n && flag; k--)
//若找到，即flag为0时跳出循环。
            { // cnt为质数的数量，而质数从表Prime[0]开始存储，所以k的初始值为cnt-1
                if (Prime[j] + Prime[k] == n)
                {
                    printf("%d %d\n", Prime[j], Prime[k]);
                    flag = 0;
                }
            }
        }
    }
    return 0;
}