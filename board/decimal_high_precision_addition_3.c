/*
 *
1 2.3
0.04 0.56
7 8
 */
#include <stdio.h>
#include <string.h>
#define N 401

int f=0;
int a[N],b[N],c[N],d[N];

void store(char str[N],int decimal[N],int integer[N])
{
    int i,j,k=0;
    int len = strlen(str);
    for (i=0;i<len;i++)
    {
        if (str[i]=='.')
        {
            f=1;
            break;
        }
    }
    for (j=i+1;j<len;j++)
        decimal[k++]=str[j]-'0';
    k=0;
    for (j=i-1;j>=0;j--)
        integer[k++]=str[j]-'0';
}

int main()
{
    char str1[N],str2[N];
    while (scanf("%s%s",str1,str2)!=EOF)
    {
        memset(a,0,N);
        memset(b,0,N);
        memset(c,0,N);
        memset(d,0,N);
        store(str1,a,b);
        store(str2,c,d);
        int i,j=0;
        for (i=N-1;i>=0;i--)
        {
            a[i]+=c[i];
            if (i!=0&&a[i]>=10)
            {
                a[i]-=10;
                a[i-1]++;
            }
            if (i==0&&a[i]>=10)
            {
                a[i]-=10;
                b[0]++;
            }
        }
        for (i=0;i<N;i++)
        {
            b[i]+=d[i];
            if (b[i]<=0)
            {
                break;
            }
            else if (b[i]>=10)
            {
                b[i]-=10;
                b[i+1]++;
            }
        }
        for (i=N-1;i>=0;i--)
        {
            if (b[i]!=0)
                j=1;
            if (j)
                printf("%d",b[i]);
        }
        if (!j)
            printf("0");
        for (i=N-1;i>=0;i--)
            if (a[i])
                break;
        if (i>-1)
            printf(".");
        if (i>=0)
            for (j=0;j<=i;j++)
                printf("%d",a[j]);
        printf("\n");
    }
    return 0;
}