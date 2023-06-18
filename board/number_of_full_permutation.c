#include <stdio.h>
int depth;//代表搜索的深度
int res[11];//用于存结果
int fi[11];//用于剪枝
void full_permutation(int);
int n;
int main() {
    //setbuf(stdout, NULL)
    scanf("%d", &n);
    full_permutation(1);
    return 0;
}
void full_permutation(int depth){
    if(depth == n + 1){
        for (int i = 1; i <= n; ++i) {
            printf("%d ",res[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if(fi[i] == 0){
            res[depth] = i;
            fi[i] = 1;
            full_permutation(depth + 1);
            fi[i] = 0;
        }
    }
}