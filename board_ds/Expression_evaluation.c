//
// Created by 86152 on 2023/6/11.
//

//Author hugo
//Time 2023/6/11 12:25
/*
 * ����ʽ���㣬����Ŀǰ�����ҵ�����ǿ��ı���ʽ����Ĵ�����
 * ������Ȼ�޷������+5+8���������⣬�����Ѿ��ܹ�������5+(-8+5)'����������
 * ����������뻹��ʵ�ֺܶ���������
*/
#include <stdio.h>
#include <string.h>

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>

#ifndef EVIC_H
#define EVIC_H

#include <stdlib.h>

#define MAX_TOKEN_LEN 16

#define EVIC_DEBUG_MODE 0

/* �ַ����� */
typedef struct {
    int TokenClass;
    void *next;

    double number;
    char op[4];
    char token[MAX_TOKEN_LEN];
    double *val;

    double (*pfunc)(double x);
} Token;

/* ����ʽ���� */
typedef struct {
    /* ָ��ͷ���ַ� */
    Token *head;
    /* �Ƿ񱻱���Ϊ��׺����ʽ */
    int compiled;
} EVIC_expr;

/* ������eval�Ա���ʽ��ֵ
expr�Ǳ���ʽ�ַ�����reBuf��Ž��
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Eval(char *expr, double *rtBuf);

/* ��������ʼ������ʽ����
����׺����ʽ�и��һ�����ַ������ֶ��󣬴���ڱ���ʽ������
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Cut(char *expr, EVIC_expr **ec_expr);

/* ��ӡ����ʽ�����ڿ��У��ǵ�free
ʧ�ܷ�NULL */
char *EVIC_Print(EVIC_expr *ec_expr);

/* ������ʽ���ַ��������ϵ
�ɹ���1��ʧ�ܷ�0 */
int EVIC_ValueLink(EVIC_expr *ec_expr, char *tk, double *val);

/* ������ʽ���ַ��������ϵ
�ɹ���1��ʧ�ܷ�0 */
int EVIC_ConstLink(EVIC_expr *ec_expr, char *tk, double ct);

/* ������ʽ���ַ��뺯����ϵ
�ɹ���1��ʧ�ܷ�0 */
int EVIC_FuncLink(EVIC_expr *ec_expr, char *tk, double (*pfunc)(double x));

/* ����ַ�����ϵ��ת��Ϊ��׺����ʽ
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Compile(EVIC_expr **ec_expr);

/* �Ա���ʽ����
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Calculate(EVIC_expr *ec_expr, double *rt);

/* �ͷű���ʽ�ռ�
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Free(EVIC_expr *ec_expr);

#endif

/* ��������ʽ���� */
EVIC_expr *NewExpr();

static int malloc_num, free_num;

enum {
    DEFAULT_TOKEN,
    NUMBER_TOKEN,
    OP_TKOEN,
    UNKNOW_TOKEN,
    VALUE_TOKEN,
    FUNC_TOKEN
};

/* �������ַ������ڿ��� */
Token *NewToken();

/* �����ַ������ڿ��� */
Token *Token_Copy(Token *ptk);

/* �ַ�ֵTODO */
int Token_Value(Token *ptk, double *rt);

/* ������ʽ�����ַ� */
int Expr_Expend(EVIC_expr *ec_expr, Token *ptk);

/* ���ر���ʽ��ĩβ */
Token *Expr_End(EVIC_expr *ec_expr);

/* �ַ�ջ���� */
typedef EVIC_expr *ExprStack;

/* �����ַ�ջ���󣬴��ڿ��У��ǵ�free
headָջ�� */
ExprStack NewExprStack();

/* ����Ԫ�ز���ջ */
int ExprStack_Push(ExprStack est, Token *ptk);

/* ��ջ */
int ExprStack_Pop(ExprStack est, Token **ptk);

/* ����������������ȼ� */
int OpPriority(char ope);

Token *NewToken() {
    malloc_num++;
    Token *ptk = ((Token *) malloc(sizeof(Token)));
    ptk->next = NULL;
    ptk->TokenClass = DEFAULT_TOKEN;
    return ptk;
}

EVIC_expr *NewExpr() {
    malloc_num++;
    return (EVIC_expr *) malloc(sizeof(EVIC_expr));
}

int Expr_Expend(EVIC_expr *ec_expr, Token *ptk) {
    if (ec_expr->head == NULL) {
        ec_expr->head = ptk;
        return 1;
    }

    Token *pttk = ec_expr->head;
    for (; pttk->next != NULL; pttk = pttk->next);
    pttk->next = ptk;
    return 1;
}

Token *Expr_End(EVIC_expr *ec_expr) {
    if (ec_expr->head == NULL) {
        return NULL;
    }

    Token *pttk = ec_expr->head;
    for (; pttk->next != NULL; pttk = pttk->next);
    return pttk;
}

int EVIC_Cut(char *expr, EVIC_expr **ec_expr) {
    EVIC_expr *pt_expr = NewExpr();
    pt_expr->head = NULL;
    pt_expr->compiled = 0;

    char(*pch);
    int offset;
    double lft;
    Token *p_tk, *pt_tk;

    for (pch = expr; (*pch) != '\0';) {
        if (EVIC_DEBUG_MODE)
            printf("parse:|%s\n", pch);
        if ((*pch) >= '0' && (*pch) <= '9') {
            sscanf(pch, "%lf%n", &lft, &offset);
            pt_tk = NewToken();
            pt_tk->TokenClass = NUMBER_TOKEN;
            pt_tk->number = lft;
            Expr_Expend(pt_expr, pt_tk);
            pch += offset;
            continue;
        } else if ((*pch) == '-') {
            Token *pendtk = Expr_End(pt_expr);
            if (pendtk == NULL) {
                if ((*(pch + 1)) >= '0' && (*(pch + 1)) <= '9') {
                    sscanf(pch, "%lf%n", &lft, &offset);
                    pt_tk = NewToken();
                    pt_tk->TokenClass = NUMBER_TOKEN;
                    pt_tk->number = lft;
                    Expr_Expend(pt_expr, pt_tk);
                    pch += offset;
                    continue;
                } else if ((*(pch + 1)) >= 'a' && (*(pch + 1)) <= 'z') {
                    pt_tk = NewToken();
                    pt_tk->TokenClass = NUMBER_TOKEN;
                    pt_tk->number = -1.0;
                    Expr_Expend(pt_expr, pt_tk);
                    pt_tk = NewToken();
                    pt_tk->TokenClass = OP_TKOEN;
                    pt_tk->op[0] = '*';
                    pt_tk->op[1] = '\0';
                    Expr_Expend(pt_expr, pt_tk);
                    pch++;
                    continue;
                } else {
                    return 0;
                }
            } else if (pendtk != NULL) {
                if (pendtk->TokenClass == OP_TKOEN) {
                    if (strcmp(pendtk->op, "(") == 0) {
                        if ((*(pch + 1)) >= '0' && (*(pch + 1)) <= '9') {
                            sscanf(pch, "%lf%n", &lft, &offset);
                            pt_tk = NewToken();
                            pt_tk->TokenClass = NUMBER_TOKEN;
                            pt_tk->number = lft;
                            Expr_Expend(pt_expr, pt_tk);
                            pch += offset;
                            continue;
                        } else if ((*(pch + 1)) >= 'a' && (*(pch + 1)) <= 'z') {
                            pt_tk = NewToken();
                            pt_tk->TokenClass = NUMBER_TOKEN;
                            pt_tk->number = -1.0;
                            Expr_Expend(pt_expr, pt_tk);
                            pt_tk = NewToken();
                            pt_tk->TokenClass = OP_TKOEN;
                            pt_tk->op[0] = '*';
                            pt_tk->op[1] = '\0';
                            Expr_Expend(pt_expr, pt_tk);
                            pch++;
                            continue;
                        } else {
                            return 0;
                        }
                    } else if (strcmp(pendtk->op, ")") == 0) {
                        pt_tk = NewToken();
                        pt_tk->TokenClass = OP_TKOEN;
                        pt_tk->op[0] = *pch;
                        pt_tk->op[1] = '\0';
                        Expr_Expend(pt_expr, pt_tk);
                        pch += 1;
                        continue;
                    } else {

                        sscanf(pch, "%lf%n", &lft, &offset);
                        pt_tk = NewToken();
                        pt_tk->TokenClass = NUMBER_TOKEN;
                        pt_tk->number = lft;
                        Expr_Expend(pt_expr, pt_tk);
                        pch += offset;
                        continue;
                    }
                } else if ((pendtk->TokenClass == NUMBER_TOKEN) ||
                           (pendtk->TokenClass == UNKNOW_TOKEN)) {
                    pt_tk = NewToken();
                    pt_tk->TokenClass = OP_TKOEN;
                    pt_tk->op[0] = *pch;
                    pt_tk->op[1] = '\0';
                    Expr_Expend(pt_expr, pt_tk);
                    pch += 1;
                    continue;
                } else {
                    return 0;
                }
            }
        } else if (
                ((*pch) == '(') ||
                ((*pch) == ')') ||
                ((*pch) == '+') ||
                ((*pch) == '*') ||
                ((*pch) == '/') ||
                ((*pch) == '^')) {
            pt_tk = NewToken();
            pt_tk->TokenClass = OP_TKOEN;
            pt_tk->op[0] = *pch;
            pt_tk->op[1] = '\0';
            Expr_Expend(pt_expr, pt_tk);
            pch += 1;
            continue;
        } else if ((*pch) >= 'a' && (*pch) <= 'z') {
            int t;
            pt_tk = NewToken();
            pt_tk->TokenClass = UNKNOW_TOKEN;
            for (t = 0; pch[t] >= 'a' && pch[t] <= 'z'; t++) {
                pt_tk->token[t] = pch[t];
            }
            pt_tk->token[t] = '\0';
            Expr_Expend(pt_expr, pt_tk);
            pch += t;
            continue;
        } else if ((*pch) == ' ') {
            pch++;
            continue;
        } else {
            return 0;
        }
    }

    *ec_expr = pt_expr;
    return 1;
}

char *EVIC_Print(EVIC_expr *ec_expr) {
    char *info = (char *) malloc(sizeof(char) * 1024);
    info[0] = '\0';

    Token *pttk = ec_expr->head;
    char ts[64];

    strcat(info, "[");
    for (; pttk != NULL; pttk = pttk->next) {
        switch (pttk->TokenClass) {
            case NUMBER_TOKEN:
                sprintf(ts, "%.2lf,", pttk->number);
                strcat(info, ts);
                break;
            case OP_TKOEN:
                sprintf(ts, "%s,", pttk->op);
                strcat(info, ts);
                break;
            case UNKNOW_TOKEN:
                sprintf(ts, "%s,", pttk->token);
                strcat(info, ts);
                break;
            case VALUE_TOKEN:
                sprintf(ts, "%s(=%.2lf),", pttk->token, *(pttk->val));
                strcat(info, ts);
                break;
            case FUNC_TOKEN:
                sprintf(ts, "(linked)%s,", pttk->token);
                strcat(info, ts);
                break;
            default:
                break;
        }
    }
    strcat(info, "]\n");

    return info;
}

int EVIC_Free(EVIC_expr *ec_expr) {
    if (ec_expr->head != NULL) {
        Token *pttk, *nextpttk;
        for (pttk = ec_expr->head; pttk != NULL; pttk = nextpttk) {
            nextpttk = pttk->next;
            free_num++;
            free(pttk);
        }
    }
    free_num++;
    free(ec_expr);

    return 1;
}

int EVIC_ValueLink(EVIC_expr *ec_expr, char *tk, double *val) {
    if (ec_expr->head == NULL) {
        return 1;
    }

    Token *pttk = ec_expr->head;
    for (; pttk != NULL; pttk = pttk->next) {
        if (pttk->TokenClass == UNKNOW_TOKEN) {
            if (strcmp(pttk->token, tk) == 0) {
                pttk->TokenClass = VALUE_TOKEN;
                pttk->val = val;
            }
        }
    }
    return 1;
}

int EVIC_ConstLink(EVIC_expr *ec_expr, char *tk, double ct) {
    if (ec_expr->head == NULL) {
        return 1;
    }

    Token *pttk = ec_expr->head;
    for (; pttk != NULL; pttk = pttk->next) {
        if (pttk->TokenClass == UNKNOW_TOKEN) {
            if (strcmp(pttk->token, tk) == 0) {
                pttk->TokenClass = NUMBER_TOKEN;
                pttk->number = ct;
            }
        }
    }
    return 1;
}

int EVIC_FuncLink(EVIC_expr *ec_expr, char *tk, double (*pfunc)(double x)) {
    if (ec_expr->head == NULL) {
        return 1;
    }

    Token *pttk = ec_expr->head;
    for (; pttk != NULL; pttk = pttk->next) {
        if (pttk->TokenClass == UNKNOW_TOKEN) {
            if (strcmp(pttk->token, tk) == 0) {
                pttk->TokenClass = FUNC_TOKEN;
                pttk->pfunc = pfunc;
            }
        }
    }
    return 1;
}

ExprStack NewExprStack() {
    malloc_num++;
    ExprStack est = (ExprStack) malloc(sizeof(EVIC_expr));
    est->head = NULL;
    return est;
}

int ExprStack_Push(ExprStack est, Token *ptk) {
    Token *tptk = Token_Copy(ptk);
    if (est->head == NULL) {
        est->head = tptk;
    } else {
        tptk->next = est->head;
        est->head = tptk;
    }
    return 1;
}

int ExprStack_Pop(ExprStack est, Token **ptk) {
    if (est->head == NULL) {
        return 0;
    } else {
        (*ptk) = est->head;
        est->head = est->head->next;
        (*ptk)->next = NULL;
    }
    return 1;
}

int OpPriority(char ope) {
    switch (ope) {
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        case '^':
            return 3;
            break;
        default:
            return -1;
            break;
    }
}

int Token_Value(Token *ptk, double *rt) {
    switch (ptk->TokenClass) {
        case NUMBER_TOKEN:
            *rt = ptk->number;
            break;
        case VALUE_TOKEN:
            *rt = *(ptk->val);
            break;
        default:
            return 0;
            break;
    }
    return 1;
}

Token *Token_Copy(Token *ptk) {
    Token *tptk = NewToken();
    tptk->TokenClass = ptk->TokenClass;

    switch (ptk->TokenClass) {
        case NUMBER_TOKEN:
            tptk->number = ptk->number;
            break;
        case OP_TKOEN:
            strcpy(tptk->op, ptk->op);
            break;
        case UNKNOW_TOKEN:
            strcpy(tptk->token, ptk->token);
            break;
        case VALUE_TOKEN:
            strcpy(tptk->token, ptk->token);
            tptk->val = ptk->val;
            break;
        case FUNC_TOKEN:
            strcpy(tptk->token, ptk->token);
            tptk->pfunc = ptk->pfunc;
            break;
        default:
            break;
    }
    return tptk;
}

int EVIC_Compile(EVIC_expr **ec_expr) {
    ExprStack opst, numst;
    Token *pttk, *tpttk, *tpnextk;

    if ((*ec_expr)->head == NULL) {
        return 1;
    }

    int rrr = 0;
    rrr += 1 - EVIC_ConstLink(*ec_expr, "e", M_E);
    rrr += 1 - EVIC_ConstLink(*ec_expr, "pi", M_PI);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "sin", sin);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "cos", cos);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "tan", tan);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "asin", asin);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "acos", acos);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "atan", atan);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "sinh", sinh);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "cosh", cosh);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "tanh", tanh);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "exp", exp);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "ln", log);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "log10", log10);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "sqrt", sqrt);
    rrr += 1 - EVIC_FuncLink(*ec_expr, "abs", fabs);
    if (rrr > 0) {
        return 0;
    }

    for (pttk = (*ec_expr)->head; pttk != NULL; pttk = pttk->next) {
        if (pttk->TokenClass == UNKNOW_TOKEN) {
            return 0;
        }
    }

    opst = NewExprStack();
    numst = NewExprStack();

    for (pttk = (*ec_expr)->head; pttk != NULL; pttk = (Token *) (pttk->next)) {

        /* ��������ɨ��һ��׺����ʽ */
        /* ����ȡ���ǲ�������
        ���жϸò����������ͣ������ò����������������ջ */
        switch (pttk->TokenClass) {
            case NUMBER_TOKEN:
                ExprStack_Push(numst, pttk);
                break;

            case OP_TKOEN:
                switch (pttk->op[0]) {
                    case '(':
                        /* �������Ϊ������"("��
                        ��ֱ�Ӵ����������ջ */
                        ExprStack_Push(opst, pttk);
                        break;
                    case ')':
                        /* �������Ϊ������")"��
                        ������������ջ�е����������������ջ��ֱ������������Ϊֹ */
                        while (ExprStack_Pop(opst, &tpttk)) {
                            if (tpttk->TokenClass == OP_TKOEN) {
                                if (tpttk->op[0] == '(') {
                                    free_num++;
                                    free(tpttk);
                                    break;
                                }
                            }
                            ExprStack_Push(numst, tpttk);
                            free_num++;
                            free(tpttk);
                        }
                        if (opst->head != NULL) {
                            if (opst->head->TokenClass == FUNC_TOKEN) {
                                ExprStack_Pop(opst, &tpttk);
                                ExprStack_Push(numst, tpttk);
                                free_num++;
                                free(tpttk);
                            }
                        }
                        break;
                    default:
                        /* �������Ϊ����������� */
                        if (opst->head != NULL) {
                            if (opst->head->TokenClass == OP_TKOEN) {
                                if (opst->head->op[0] == '(') {
                                    /* ���������ջջ���������Ϊ���ţ�
                                    ��ֱ�Ӵ����������ջ */
                                    ExprStack_Push(opst, pttk);
                                } else if (
                                        OpPriority((pttk->op)[0]) >
                                        OpPriority((opst->head->op)[0])) {
                                    /* �����������ջջ������������ȼ��ߣ�
                                    ��ֱ�Ӵ����������ջ */
                                    ExprStack_Push(opst, pttk);
                                } else if (
                                        OpPriority((pttk->op)[0]) <=
                                        OpPriority((opst->head->op)[0])) {
                                    /* �����������ջջ������������ȼ��ͻ�����ȣ�
                                    ���������ջ�����������������ջ��
                                    ֱ��һ�����ȼ������͵��������������Ϊֹ
                                    ������ǰ�����ѹ���������ջ */
                                    while (opst->head != NULL) {
                                        if ((OpPriority((pttk->op)[0]) <=
                                             OpPriority((opst->head->op)[0])) ||
                                            ((opst->head->op)[0] != '(')) {
                                            ExprStack_Pop(opst, &tpttk);
                                            ExprStack_Push(numst, tpttk);
                                            free_num++;
                                            free(tpttk);
                                        } else {
                                            break;
                                        }
                                    }
                                    ExprStack_Push(opst, pttk);
                                } else {
                                    return 0;
                                }
                            } else {
                                return 0;
                            }
                        } else {
                            /* ջ�գ���ջ */
                            ExprStack_Push(opst, pttk);
                        }
                        break;
                }
                break;

            case VALUE_TOKEN:
                ExprStack_Push(numst, pttk);
                break;

            case FUNC_TOKEN:
                tpnextk = (Token *) pttk->next;
                if (pttk->next != NULL) {
                    if (tpnextk->TokenClass == OP_TKOEN) {
                        if ((tpnextk->op)[0] == '(') {
                            ExprStack_Push(opst, pttk);
                            ExprStack_Push(opst, tpnextk);
                            pttk = tpnextk;
                        } else {
                            return 0;
                        }
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
                break;
            default:
                return 0;
                break;
        }
        if (EVIC_DEBUG_MODE) {
            char *info1, *info2;
            info1 = EVIC_Print(numst);
            info2 = EVIC_Print(opst);
            printf("step:\nnumst:|%sopst :|%s", info1, info2);
            free(info1);
            free(info2);
        }
    }

    /* ������ʽ��ȡ��ɺ��������ջ�����������ʱ��
    ������ȡ�����������������ջ��ֱ���������ջΪ�� */
    while (ExprStack_Pop(opst, &tpttk)) {
        ExprStack_Push(numst, tpttk);
        free_num++;
        free(tpttk);
    }
    EVIC_Free(opst);
    EVIC_Free(*ec_expr);

    *ec_expr = NewExpr();
    (*ec_expr)->head = NULL;
    (*ec_expr)->compiled = 1;

    while (ExprStack_Pop(numst, &tpttk)) {
        ExprStack_Push(*ec_expr, tpttk);
        free_num++;
        free(tpttk);
    }
    EVIC_Free(numst);

    return 1;
}

int EVIC_Calculate(EVIC_expr *ec_expr, double *rt) {
    ExprStack numst;
    Token *pttk, *tpttk, *aptk, *bptk, *cptk;
    double a, b, c;

    numst = NewExprStack();

    for (pttk = ec_expr->head; pttk != NULL; pttk = pttk->next) {
        switch (pttk->TokenClass) {
            case NUMBER_TOKEN:
                ExprStack_Push(numst, pttk);
                break;
            case VALUE_TOKEN:
                ExprStack_Push(numst, pttk);
                break;
            case OP_TKOEN:
                switch (pttk->op[0]) {
                    case '+':
                        ExprStack_Pop(numst, &aptk);
                        ExprStack_Pop(numst, &bptk);
                        Token_Value(aptk, &a);
                        Token_Value(bptk, &b);

                        tpttk = NewToken();
                        tpttk->TokenClass = NUMBER_TOKEN;
                        tpttk->number = b + a;
                        ExprStack_Push(numst, tpttk);
                        free_num += 3;
                        free(tpttk);
                        free(aptk);
                        free(bptk);
                        break;
                    case '-':
                        ExprStack_Pop(numst, &aptk);
                        ExprStack_Pop(numst, &bptk);
                        Token_Value(aptk, &a);
                        Token_Value(bptk, &b);

                        tpttk = NewToken();
                        tpttk->TokenClass = NUMBER_TOKEN;
                        tpttk->number = b - a;
                        ExprStack_Push(numst, tpttk);
                        free_num += 3;
                        free(tpttk);
                        free(aptk);
                        free(bptk);
                        break;
                    case '*':
                        ExprStack_Pop(numst, &aptk);
                        ExprStack_Pop(numst, &bptk);
                        Token_Value(aptk, &a);
                        Token_Value(bptk, &b);

                        tpttk = NewToken();
                        tpttk->TokenClass = NUMBER_TOKEN;
                        tpttk->number = b * a;
                        ExprStack_Push(numst, tpttk);
                        free_num += 3;
                        free(tpttk);
                        free(aptk);
                        free(bptk);
                        break;
                    case '/':
                        ExprStack_Pop(numst, &aptk);
                        ExprStack_Pop(numst, &bptk);
                        Token_Value(aptk, &a);
                        Token_Value(bptk, &b);

                        tpttk = NewToken();
                        tpttk->TokenClass = NUMBER_TOKEN;
                        tpttk->number = b / a;
                        ExprStack_Push(numst, tpttk);
                        free_num += 3;
                        free(tpttk);
                        free(aptk);
                        free(bptk);
                        break;
                    case '^':
                        ExprStack_Pop(numst, &aptk);
                        ExprStack_Pop(numst, &bptk);
                        Token_Value(aptk, &a);
                        Token_Value(bptk, &b);

                        tpttk = NewToken();
                        tpttk->TokenClass = NUMBER_TOKEN;
                        tpttk->number = pow(b, a);
                        ExprStack_Push(numst, tpttk);
                        free_num += 3;
                        free(tpttk);
                        free(aptk);
                        free(bptk);
                        break;
                    default:
                        return 0;
                        break;
                }
                break;
            case FUNC_TOKEN:
                ExprStack_Pop(numst, &aptk);
                Token_Value(aptk, &a);
                tpttk = NewToken();
                tpttk->TokenClass = NUMBER_TOKEN;
                tpttk->number = (*(pttk->pfunc))(a);
                ExprStack_Push(numst, tpttk);
                free_num += 2;
                free(tpttk);
                free(aptk);
                break;
            default:
                return 0;
                break;
        }
        if (EVIC_DEBUG_MODE) {
            char *info1;
            info1 = EVIC_Print(numst);
            printf("step:\nnumst:|%s", info1);
            free(info1);
        }
    }
    ExprStack_Pop(numst, &aptk);
    Token_Value(aptk, rt);
    EVIC_Free(numst);
    free_num++;
    free(aptk);
    return 1;
}

int EVIC_Eval(char *expr, double *rtBuf) {
    malloc_num = free_num = 0;

    EVIC_expr *ec_expr;
    char *info;
    int rt;
    double rrr;

    rt = EVIC_Cut(expr, &ec_expr);
    if (rt == 0) {
        return 0;
        if (EVIC_DEBUG_MODE)
            printf("cut failed\n");
    } else {
        if (EVIC_DEBUG_MODE) {
            info = EVIC_Print(ec_expr);
            printf(info);
            free(info);
        }
    }

    rt = EVIC_Compile(&ec_expr);
    if (rt == 0) {
        return 0;
        if (EVIC_DEBUG_MODE)
            printf("compile failed\n");
    } else {
        if (EVIC_DEBUG_MODE) {
            printf("------------------------\nresult:\n");
            info = EVIC_Print(ec_expr);
            printf(info);
            free(info);
        }
    }

    rt = EVIC_Calculate(ec_expr, &rrr);
    if (rt == 0) {
        return 0;
        if (EVIC_DEBUG_MODE)
            printf("calculat failed\n");
    } else {
        if (EVIC_DEBUG_MODE)
            printf("------------------------\nresult: %lf\n", rrr);
    }

    EVIC_Free(ec_expr);
    *rtBuf = rrr;

    // printf("malloc:%d\nfree:%d\n", malloc_num, free_num);
    return 1;
}

int main(int argc, char const *argv[]) {
    // ��������rt��
    double rt;
    //-----hugo
    char myexpr[1000];
    scanf("%s", myexpr);
    char myexpr_next[1000];
    double delta = 0.0;
    if (myexpr[0] == '+' || myexpr[0] == '-') {
        strcpy(myexpr_next, myexpr + 1);
        if (myexpr_next[0] == '+') {
            delta = 0.0;
        } else {
            int x = atoi(myexpr_next);
            delta = -2.0 * x;
        }
    } else {
        strcpy(myexpr_next, myexpr);
    }
    //------hugo,���ҷ�첹�����������Ժ󣬻������ܹ�ʵ�����ܹ��뵽�������
    // �Ա���ʽ(ln(e)*ln(e^2))^(20*sin(pi/(3*ln(e^2))))��ֵ
    if (
            EVIC_Eval(
                    myexpr_next,
                    &rt
            )
            ) {
        printf("result: %lf\n", rt + delta);
    } else {
        printf("eval failed\n");
    }
}