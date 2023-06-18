#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int is_full(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, int x) {
    if (is_full(s)) {
        fprintf(stderr, "Stack is full\n");
        exit(EXIT_FAILURE);
    }
    s->data[++s->top] = x;
}

int pop(Stack *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

int peek(Stack *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top];
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char c) {
    if (c == '*' || c == '/') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else {
        return 0;
    }
}

void infix_to_postfix(char *infix, char *postfix) {
    Stack s;
    init(&s);
    int i, j;
    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (peek(&s) != '(') {
                postfix[j++] = ' ';
                postfix[j++] = pop(&s);
            }
            pop(&s);
        } else if (is_operator(infix[i])) {
            while (!is_empty(&s) && priority(peek(&s)) >= priority(infix[i])) {
                postfix[j++] = ' ';
                postfix[j++] = pop(&s);
            }
            postfix[j++] = ' ';
            push(&s, infix[i]);
        }
    }
    while (!is_empty(&s)) {
        postfix[j++] = ' ';
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}

int evaluate_postfix(char *postfix) {
    Stack s;
    init(&s);
    int i, x, y, result;
    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            push(&s, num);
            i--;
        } else if (is_operator(postfix[i])) {
            y = pop(&s);
            x = pop(&s);
            switch (postfix[i]) {
                case '+':
                    result = x + y;
                    break;
                case '-':
                    result = x - y;
                    break;
                case '*':
                    result = x * y;
                    break;
                case '/':
                    result = x / y;
                    break;
            }
            push(&s, result);
        }
    }
    return pop(&s);
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    scanf("%s", infix);
    infix_to_postfix(infix, postfix);
    printf("%s\n", postfix);
    printf("%d\n", evaluate_postfix(postfix));
    return 0;
}