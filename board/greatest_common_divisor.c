#include <stdio.h>
int gcd(int a, int b) {
    int r;
    if (b == 0)
        return a < 0 ? -a : a;
    while ((r = a % b) != 0) {
        a = b;
        b = r;
    }
    return b < 0 ? -b : b;
}
int main(){
    int a,b;
    while ((scanf("%d%d",&a,&b)) > 0){
        printf("%d\n", gcd(a,b));
    }
    return 0;
}