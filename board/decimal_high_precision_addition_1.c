#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b
#define FOR(i, a, b) for (int i = a; i <= b; i++)
// 14min
int main() {
    char in1[600];
    char in2[2000];
    while (scanf("%s%s", in1, in2) == 2) {
        int l1 = strlen(in1);
        int l2 = strlen(in2);
        int flag1 = 0, flag2 = 0;
        int base[600] = {};
        FOR(i, 0, l1 - 1) if (in1[i] == '.') flag1 = i;
        FOR(i, 0, l2 - 1) if (in2[i] == '.') flag2 = i;
        if (flag1 == 0) {
            FOR(i, 0, l1 - 1) base[200 + i - l1 + 1] += in1[i] - 48;  // base[200] gewei
        } else {
            int delta = -flag1 + 1;
            FOR(i, 0, l1 - 1) base[200 + i + delta] += in1[i] - 48;
        }
        if (flag2 == 0) {
            FOR(i, 0, l2 - 1) base[200 + i - l2 + 1] += in2[i] - 48;  // base[200] gewei
        } else {
            int delta = -flag2 + 1;
            FOR(i, 0, l2 - 1) base[200 + i + delta] += in2[i] - 48;
        }
        base[201] = 0;
        FOR(i, 0, 400) {
            int j = 400 - i;
            if (base[j] > 9)
                base[j] -= 10, base[j - 1]++;
            if (base[201])
                base[201]--, base[200]++;
        }
        int l = -1;
        int r = -1;
        FOR(i, 0, 400) if (base[i]) r = i;
        FOR(i, 0, 400) if (base[400 - i]) l = 400 - i;
        if (l > 201)
            l = 200;
        if (r < 200)
            r = 200;
        if (l == -1) {
            printf("0\n");
            continue;
        }
        FOR(i, l, r) {
            if (i == 201) {
                printf(".");
            } else
                putchar(base[i] + 48);
        }
        putchar(10);     //换行
    }
}