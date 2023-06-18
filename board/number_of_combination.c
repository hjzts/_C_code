#include <stdio.h>
//求组合数c(n,m) 从m个中选取n个
long long comb_num(int m, int n) {
    if (n == 0 || m == n)
        return 1;
    if (m < n)
        return 0;
    if (n == 1)
        return m;
    return comb_num(m - 1, n) + comb_num(m - 1, n - 1);
}


int main(){
    int m,n;
    while (scanf("%d%d",&m,&n) != EOF){
        printf("%lld\n", comb_num(m,n));
    }
    return 0;
}