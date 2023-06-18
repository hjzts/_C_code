#include <stdio.h>
#include <stdlib.h>
//qsort()中的cmp函数
int fall_double(const void *p1, const void *p2)
{
    if ( *(double *)p1 > *(double *)p2 ) return -1;
    if ( *(double *)p1 < *(double *)p2 ) return 1;
    return 0;
}//降序
int rise_double(const void *p1, const void *p2)
{
    if ( *(double *)p1 < *(double *)p2 ) return -1;
    if ( *(double *)p1 > *(double *)p2 ) return 1;
    return 0;
}//升序

//qsort()中的cmp函数
int fall_int(const void *p1, const void *p2)
{
    if ( *(int *)p1 > *(int *)p2 ) return -1;
    if ( *(int *)p1 < *(int *)p2 ) return 1;
    return 0;
}//降序

//qsort()中的cmp函数
int fall_char(const void *p1, const void *p2)
{
    if ( *(char *)p1 > *(char *)p2 ) return -1;
    if ( *(char *)p1 < *(char *)p2 ) return 1;
    return 0;
}//降序
int rise_char(const void *p1, const void *p2)
{
    if ( *(int *)p1 < *(int *)p2 ) return -1;
    if ( *(int *)p1 > *(int *)p2 ) return 1;
    return 0;
}//升序

int a[50];
int main(){
    for (int i = 1; i <= 50; ++i) {
        scanf("%d",&a[i]);
    }
    qsort(a,51, sizeof(int), fall_int);
    for (int i = 1; i <= 50; ++i) {
        printf("%d ",a[i]);
    }
    return 0;
}
/*
4 5 4 6 8 9 7 25 45 65 32 98 45 81 92 63 64 31 97 35 82 65 54 25 65 25 65 54 64 54 65 45 1 6 2 3 5 4 8 9 5 4 5 5 6 2 3 6 6 6
 */