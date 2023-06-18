#include<stdio.h>

int fact(int n);
int permutation(int n,int m);

int main()
{
    int n,m;
    while (scanf("%d%d",&n,&m) != EOF){
        printf("%d\n",permutation(n,m));
    }
}

int fact(int n)                               //自定义fact函数，用来求n的阶乘
{
    if(n<0)
        return 0;
    else if(n==0 || n==1)
        return 1;
    else
        return n*fact(n-1);
}

int permutation(int n,int m)
{
    int A;
    A=fact(n)/fact(n-m);
    return A;
}