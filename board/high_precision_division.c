#include<stdio.h>
#include<string.h>

#define N 1000
//注意输出的变化 ,输出商时，数组最高位为整数位数
//商的最高位，存储在数组的1号元素
void output(int a[],int sign){
    int i=1;

    if(sign<0)
        printf("-");
    //跳过商整数部分的前导0
    while(a[i]==0&&i<a[N-1])
        i++;
    for(;i<=a[0];i++){
        if(i==a[N-1]+1)
            printf(".");
        printf("%d",a[i]);
    }
    printf("\n");
}

//判断字符串是否为数字串，允许符号位，是返回1否返回0
int allDigit(char *s) {
    int flag=1;//标志读取的是否第一个字符
    while(*s) {
        //如果是第一个字符，允许是 + -
        if(flag) {
            flag=0;
            if(*s=='+'||*s=='-'){
                s++;
                continue;
            }
        }

        if(!(*s>='0'&&*s<='9'))
            return 0;
        s++;
    }
    return 1;
}

//将数字串s拆分为单个数字保存在整型数组，从1号开始
//整型数组0号元素记录数字长度
//存储时去除所有的前导0
void input(char s[],int p[]){
    int sign=1;//符号位
    int len=strlen(s),i=0;

    //len表示s中数字字符的个数
    if(s[0]=='+') {
        i=1;
        len--;
    }
    if(s[0]=='-'){
        i=1;
        len--;
        sign=-1;
    }

    //跳过符号位之后所有的前导0
    //无+号时，从0号开始检测
    while(s[i]=='0'&&len>1){
        i++;
        len--;
    }

    //i为s中除符号位第一个非0字符的下标
    //若s中全0，i为最后一个0的下标
    int j=0;
    //注意条件是j<len，不能是i<len
    for(;j<len;j++){
        p[len-j]=s[i]-'0';
        i++;
    }

    //0位记录数字长度，1..len记录数字
    //N-1位记录符号1或-1
    //考虑运算时两个数可能不等长,符号位不能设置在len+1
    p[0]=len;
    p[N-1]=sign;
}
// a/b结果存放在c
void division(int a[],int b,int c[]){
    int i,j,t;

    if(b==0){
        printf("input error\n");
        return ;
    }

    //除法从高位开始计算
    //商从C数组的1位开始存储，即1位是商的最高位
    j=1;t=0;
    for(i=a[0];i>=1;i--){
        t=t*10+a[i];
        c[j++]=t/b;
        t=t%b;
    }

    c[N-1]=j-1; //整数位数长度

    //若能整除
    if(t==0) {
        c[0]=j-1;
        return ;
    }

    //计算小数点后k位
    int k=1;
    while(k<=500) {
        t=t*10;
        c[j++]=t/b;
        t=t%b;
        if(t==0) break;
        k++;
    }
    c[0]=j-1;	//整数+小数位数
}


int main(){
    char s[N];
    int a[N]={0},c[2*N]={0};
    int b;
    int i,sign;

//    printf("请输入数字串1：\n");
    do{
        gets(s);
        if(allDigit(s))
            break;
//        printf("请输入数字串1：\n");
    }while(1);
    input(s,a);

//    printf("请输入除数：\n");
    scanf("%d",&b);

    division(a,b,c);

    output(c,1);

    return 0;
}
