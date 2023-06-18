/*
 *
1 2.3
0.04 0.56  //会输出.6
7 8
 */
#include <stdio.h>
#include <string.h>
#define N 401
int a[N]={0},b[N]={0},c[N]={0},d[N]={0};
int main()
{
    char str1[N],str2[N];
    while (scanf("%s %s",str1,str2)!=EOF)
    {
        int i,j,k;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(c,0,sizeof(c));
        memset(d,0,sizeof(d));
        int len1=strlen(str1),len2=strlen(str2);
        for (i=0;str1[i]!='.'&&i<len1;i++);
        k=0;
        for (j=i+1;j<len1;j++)  //小数从高位到低位
            a[k++]=str1[j]-'0';
        k=0;
        for (j=i-1;j>=0;j--)        //整数从低位到高位
            b[k++]=str1[j]-'0';
        k=0;
        for (i=0;str2[i]!='.'&&i<len2;i++);
        for (j=i+1;j<len2;j++)  //小数从高位到低位
            c[k++]=str2[j]-'0';
        k=0;
        for (j=i-1;j>=0;j--)        //整数从低位到高位
            d[k++]=str2[j]-'0';
        k=0;
        for (i=N-1;i>=0;i--)      //小数部分相加
        {
            a[i]+=c[i];
            if (i!=0&&a[i]>9)
            {
                a[i]%=10;
                a[i-1]++;
            }
            else if (i==0&&a[i]>9)
            {
                a[i]%=10;
                b[0]++;
            }
        }
        for (i=0;i<N;i++)       //处理整数部分相加
        {
            b[i]+=d[i];
            if (b[i]>9)
            {
                b[i]%=10;
                b[i+1]++;
            }
        }
        for (i=N-1;i>=0&&b[i]==0;i--); //输出整数部分
        for (j=i;j>=0;j--)
            printf("%d",b[j]);
        for (i=N-1;i>=0&&a[i]==0;i--);    //输出小数部分
        if (i>=0)
        {
            printf(".");
            for (j=0;j<=i;j++)
            {
                printf("%d",a[j]);
            }
        }
        printf("\n");
    }
    return 0;
}