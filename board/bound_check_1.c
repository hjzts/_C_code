#include <stdio.h>

int nums[500005], n;
int left_bound(int);
int right_bound(int );


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &nums[i]);
    }
    int key;
    scanf("%d", &key);
    int left = left_bound(key);
    int right = right_bound(key);
    printf("%d %d",left + 1,right + 1);
    /*    int t, key, l, r;
    scanf("%d%d", &n, &t);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    while (t--) {
        scanf("%d", &key);
        l = left_bound(key);
        r = right_bound(key);
        if (l == -1)
            printf("-1\n");
        else if (l == r)
            printf("%d\n", l);
        else
            printf("%d %d\n", l, r);
    }*/
    return 0;
}
int left_bound(int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    if (left >= n || nums[left] != target)
        return -1;
    return left;
}
int right_bound(int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    if (right < 0 || nums[right] != target)
        return -1;
    return right;
}