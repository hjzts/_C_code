//现在是a年b月c日d时e分f秒，求距离g年h月i日j时k分l秒还有多少秒
#include <stdio.h>

#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define LL long long
// 16min
LL tti(int t[]) {
    LL ans = 0, day = 0;
    FOR(i, 0, 9999) FOR(j, 1, 12) FOR(k, 1, 31) {
                if (i == t[0] && j == t[1] && k == t[2])
                    goto NEXT;
                int r = 0;
                if ((i % 4 == 0) && !(i % 100 == 0))
                    r = 1;
                if (i % 400 == 0)
                    r = 1;
                if (j == 4 || j == 6 || j == 9 || j == 11)
                    if (k == 31)
                        continue;
                if (j == 2 && k > 28 + r)
                    continue;
                day++;
            }
    NEXT:
    ans = (t[5]) + 60 * (t[4]) + 3600 * (t[3]) + 86400 * day;
    return ans;
}
int main() {
    int a[15];
    FOR(i, 1, 12) { scanf("%d", a + i); }
    LL a1 = tti(a + 1);
    LL a2 = tti(a + 7);
    printf("%lld", max(a1 - a2, a2 - a1));
}