#include <stdio.h>
#include <math.h>

#define mod 998244353
typedef struct {
    long long a11, a12, a21, a22;
} ma;

/*
 * 结界，新人勿入
 * 注意数据范围1 <= n <= 10^15
 * 题解使用矩阵乘法的快速幂
 */

int main() {
    int a1 = 1, a2 = 1;
    ma p = { 1, 1, 1, 0 };
    long long i;
    {
        ma ans = { 1, 0, 0, 1 }, ret = p, temp;
        scanf("%lld", &i);
        while (i) {
            if (i & 1) {
                temp.a11 = (ret.a11 * ans.a11 % mod + ret.a12 * ans.a21) % mod;
                temp.a12 = (ret.a11 * ans.a12 % mod + ret.a12 * ans.a22) % mod;
                temp.a21 = (ret.a21 * ans.a11 % mod + ret.a22 * ans.a21) % mod;
                temp.a22 = (ret.a21 * ans.a12 % mod + ret.a22 * ans.a22) % mod;
                ans = temp;
            }
            temp.a11 = (ret.a11 * ret.a11 % mod + ret.a12 * ret.a21) % mod;
            temp.a12 = (ret.a11 * ret.a12 % mod + ret.a12 * ret.a22) % mod;
            temp.a21 = (ret.a21 * ret.a11 % mod + ret.a22 * ret.a21) % mod;
            temp.a22 = (ret.a21 * ret.a12 % mod + ret.a22 * ret.a22) % mod;
            ret = temp;
            i >>= 1;
        }
        printf("%lld", (ans.a11 * a2 + ans.a12 * a1 - 1) % mod);
    }
    return 0;
}