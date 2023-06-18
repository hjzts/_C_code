#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int maxBit(const int *a, int n) {
    int max = *a;
    for (int i = 1; i < n; i++) {
        max = *(a + i) > max ? *(a + i) : max;
    }
    int d = 1;
    while (max > 10) {
        max /= 10;
        d++;
    }
    return d;
}

void radixSort(int *a, int n) {
    int bucket[10];

    int *p[2] = {a};
    p[1] = (int *)malloc(n * sizeof(int));
    if (p[1] == NULL) {
        printf("\nWarning:The length is too large!\n");
        return;
    }
    int d = maxBit(a, n);
    int rate = 1, now = 0;
    for (int i = 0; i < d; i++) {
        memset(bucket, 0, sizeof(bucket));
        for (int j = 0; j < n; j++) {
            bucket[(*(p[now] + j) / rate) % 10]++;
        }
        for (int j = 1; j < 10; j++) {
            bucket[j] += bucket[j - 1];
        }
        for (int j = n - 1; j >= 0; j--) {
            int k = (*(p[now] + j) / rate) % 10;
            *(p[now ^ 1] + bucket[k] - 1) = *(p[now] + j);
            bucket[k]--;
        }
        rate *= 10;
        now ^= 1;
    }
    if (now) {
        for (int i = 0; i < n; i++) {
            *(a + i) = *(p[1] + i);
        }

    }
    free(p[1]);
    return;
}
int a[50];
int main(){
    for (int i = 0; i < 50; ++i) {
        scanf("%d",&a[i]);
    }
    radixSort(a,50);
    for (int i = 0; i < 50; ++i) {
        printf("%d ",a[i]);
    }
    return 0;
}
/*
4 5 4 6 8 9 7 25 45 65 32 98 45 81 92 63 64 31 97 35 82 65 54 25 65 25 65 54 64 54 65 45 1 6 2 3 5 4 8 9 5 4 5 5 6 2 3 6 6 6
 */