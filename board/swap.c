#include <stdio.h>

// 
void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 void swap(int &a,int &b)
 {
    a ^= b;
    b ^= a;
    a ^ =b;
}
*/

void swap_long_long(long long *a, long long *b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void swap_char(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}
//void swap_string_(char *pstr1[], char *pstr2[]) {
//    char *tmp;
//    tmp = *pstr1;
//    *pstr1 = *pstr2;
//    *pstr2 = tmp;
//}
//
void swap_string(char **pstr1, char **pstr2) {
    printf("%p %p\n", pstr1, pstr2);
    char *tmp;
    tmp = *pstr1;
    *pstr1 = *pstr2;
    *pstr2 = tmp;
}


int main() {
//    int a, b;
//    scanf("%d%d",&a,&b);
//    swap_int(&a,&b);
//    printf("%d\n%d",a,b );
    char s1[] = "hello", s2[] = "world";
    char *p1 = s1,*p2 = s2;
//    char s1[10] = "hello",s2[10] = "world";
//    scanf("%s %s",s1,s2);
    swap_string(&p1, &p2);
    printf("%s\n%s\n", p1, p2);
//    swap_string(&s1,&s2);
//    swap_string_(&s1,&s2);
//    printf("%p %p\n", &s1, &s2);
//    printf("%p %p\n", &p1, &p2);
//    printf("%s\n%s",s1,s2);
    return 0;
}
