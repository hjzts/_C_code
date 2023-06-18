#include <stdio.h>

int main() {
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    char ch;
    printf("#include <stdio.h>\n\n"
           "int main()\n"
           "{\n"
           "\tprintf(\"");

    while ((ch = getchar()) != EOF) {
        if (ch == '\\' || ch == '\'' || ch == '\"') {
            putchar('\\');
            putchar(ch);
        } else if (ch == '%') {
            printf("%%%%");
        } else if (ch == '\n') {
            printf("\\n\"\n\t\t\"");
        } else {
            putchar(ch);
        }
    }

    printf("\");\n"
           "\treturn 0;\n"
           "}\n");
    return 0;
}