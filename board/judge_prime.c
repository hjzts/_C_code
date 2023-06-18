#include <stdio.h>
//int prime(int x);
int main() {
    int p;
    scanf("%d", &p);
    int i, prime_flag = 1, step;
    if (p > 2 && (p % 2 == 0))
        prime_flag = 0;
    else {
        if (p > 5 && (p % 3 == 0 || p % 5 == 0))
            prime_flag = 0;
        else {
            step = 2;
            for (i = 7; i * i <= p; i += step) {
                if (p % i == 0) {
                    prime_flag = 0;
                    break;
                }
                step = 6 - step;
            }
        }
    }
    if (prime_flag == 1) printf("this is a prime !");
    else printf("this isn't a prime !");
    return 0;
}

/*int prime(int x) {
    int i, prime_flag = 1;
    if (x > 2 && (x % 2 == 0)) //x为大于2的偶数
        prime_flag = 0;
    else // x为大于3的奇数的情况
    {// 仅判断x是否被奇数整除
        for (i = 3; i * i < x; i += 2) {
            if (x % i == 0) {
                prime_flag = 0;
                break;
            }
        }
    }
    return prime_flag;
}*/
