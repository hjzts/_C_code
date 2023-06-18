#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}
void reverse(char *str, int begin, int end) {
    while (begin < end) {
        swap(&str[begin], &str[end]);
        begin++;
        end--;
    }
}
int next_permutation(char *str, int n) {
    int i;
    for (i = n - 2; i >= 0; i--) {
        if (str[i] < str[i + 1]) {
            break;
        }
    }
    if (i < 0) {
        return 0;
    }
    int j;
    for (j = n - 1; j > i; j--) {
        if (str[j] > str[i]) {
            break;
        }
    }
    swap(&str[i], &str[j]);
    reverse(str, i + 1, n - 1);
    return 1;
}
int main() {
    char str[] = "abd";
    int len = strlen(str);
    do {
        printf("%s\n", str);
    } while (next_permutation(str, len));
    return 0;
}