#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define ElemType int
ElemType STACK[MAXSIZE];
int Top;//Top变量需要在多个函数间共享，为了保持函数接口简洁，在此定义为全局变量
//初始化堆栈
void initStack() {
    Top = -1;
}

//测试堆栈是否为空
int isEmpty() {
    return Top == -1;//栈空,返回1,否则,返回0
}

//测试堆栈是否为满
int isFull() {
    return Top == MAXSIZE - 1;//栈满,返回1,否则,返回0
}

void Error(char s[]) {
    printf("%s\n", s);
    exit(-1);
}

//进栈
void push(ElemType s[], ElemType item) {
    if (isFull()) {
        Error("Full Stack!");
    } else
        s[++Top] = item;//入栈成功
}
//出栈
ElemType pop(ElemType s[]) {
    if (isEmpty()) {
        Error("Empty Stack!");
    } else return s[Top--];//出栈成功
}

int main() {

    return 0;
}