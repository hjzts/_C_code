#include <stdio.h>
#define N 1005
int main(){
    int prime[N], cnt, notPrime[N+1]; // 意义同上
    for(int i = 2; i < N; i++)
    {
        if(!notPrime[i]) prime[cnt++] = i; // 记录素数
        for(int j = 0; j < cnt && prime[j] <= n / i; j++) // j 是一个编号而已，prime[j] 才是上文说的 p
        {
            not_prime[i*prime[j]] = 1; // 筛掉
            if(i % prime[j] == 0) break; // 如果 prime[j] | i，说明这是 i 的最小质因子，更大的素数就不需要了
        }
    }
    return 0;
}