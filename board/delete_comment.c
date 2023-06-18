#include <stdlib.h>
#include <stdio.h>

enum State {
    CODE, SLASH, SINGLE_COMMENT, MUL_COMMENT, MUL_COMMENT_STAR
};

int main() {
    int ch;
    enum State s = CODE;
    int i;
    while ((ch = getchar()) != EOF) {
        switch (s) {
            case CODE:
                if (ch == '/')
                    s = SLASH;
                else {
                    putchar(ch);
                }
                break;
            case SLASH:
                if (ch == '/') {
                    s = SINGLE_COMMENT;
                } else if (ch == '*') {
                    s = MUL_COMMENT;
                } else{
                    putchar('/');
                    putchar(ch);
                    s = CODE;
                }
                break;
            case SINGLE_COMMENT:
                if(ch=='\n'){
                    s=CODE;
                }else ;
                break;
            case MUL_COMMENT:
                if(ch == '*'){
                    s = MUL_COMMENT_STAR;
                }else ;
                break;
            case MUL_COMMENT_STAR:
                if(ch =='*'){
                    s = MUL_COMMENT_STAR;
                }else if(ch=='\\'){
                    s = CODE;
                } else;
                break;
        }
    }
}