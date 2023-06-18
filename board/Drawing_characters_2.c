#include <stdio.h>
char c;
int main(void) {
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    freopen("AA.c", "w", stdout);
    puts("#include <stdio.h>");
    puts("int main()");
    puts("{");
    while (~(c = getchar())) {
        printf(" puts(\"");
        for (; c != '\n'; c = getchar()) {
            if (c == 34 || c == 39 || c == 92)
                putchar(92);
            putchar(c);
        }
        puts("\");");
    }
    puts(" return 0;");
    puts("}");
    return 0;
}