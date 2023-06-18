#include <stdio.h>

const int N = 1e6 + 5;
int tr[N][26], cou[N], idx;//其实应该用指针去连接每个节点，但是做题其实一般不考虑空间所以用数组模拟即可，tr数组就是字典树
//cou[i]表示以i节点字符结尾的字符串个数，idx表示根节点，但是也表示接下来要存储的节点下标其实
char str[N];

void insert(char *s) {//存储操作
    int p = 0;//当前节点下标或者说编号，从根节点开始
    for (int i = 0; s[i]; i++) {//遍历整个要插入的字符串
        int u = (s[i] - 'a');//讲字符串转换成数字
        if (!tr[p][u])tr[p][u] = ++idx;//如果p节点的儿子节点没有要插入的这个字符那就开辟一个分支用来存储这个字符
        p = tr[p][u];//将当前节点更新成当前结点的那个儿子节点然后继续往下存储
    }
    cou[p]++;//最终存储完p就是这个字符串最后一个字符存储的节点编号，cou[p]++就表示以这个节点编号结尾的字符串数量+1
}

int query(char *s) {//查询操作
    int p = 0;//当前节点下标或者说编号，从根节点开始
    for (int i = 0; s[i]; i++) {//遍历整个要插入的字符串
        int u = (s[i] - 'a');//讲字符串转换成数字
        if (!tr[p][u])return 0;//如果p节点的儿子节点没有要插入的这个字符那就表示当前Trie树不存在这个字符串那就返回0
        p = tr[p][u];////将当前节点更新成当前结点的那个儿子节点然后继续往下查找
    }
    return cou[p];//如果找到了就返回字符个数
}

int main() {

    int t;
    char op;
    scanf("%d", &t);
    while (t--) {
        scanf(" %c %s", &op, str);
        if (op == 'I') {
            insert(str);
        } else {
            printf("%d\n", query(str));
        }
    }

    return 0;
}