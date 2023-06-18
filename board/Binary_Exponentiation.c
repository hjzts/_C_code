/*
#include <stdio.h>
//递归
typedef long long ll;
ll binaryPow(ll a, ll b, ll m){
    if(b == 0) return 1;
    else if(b % 2 == 1)  return a * binaryPow(a, b - 1, m) % m;
    else{
        ll num = binaryPow(a, b/2, m) % m;
        return num * num % m;
    }

}
//非递归
long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
*/
#include <stdio.h>
long long quick_pow(long long a , long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans =ans * a ;
        b >>= 1;
        a = a * a;
    }
    return ans;
}

int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    long long ans = 1;
    while (b){
        if( b & 1)
          ans = ans * a;
        b >>=1;
        a = a * a;
    }
    printf("%lld",ans);
    return 0;
}