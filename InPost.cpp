#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

//Contoh kalo mau dicoba a+b*(c^d-e)^(f+g*h)-i
//Harusnya keluar abcd^e-fgh*+^*+i-

typedef struct {
    char items[MAX][MAX];
    int top;
} Stack;

void push(Stack *s, const char *str) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    strcpy(s->items[++(s->top)], str);
}

char *pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return "";
    }
    return s->items[(s->top)--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void infixToPostfix(char *infix, char *postfix) {
    Stack opStack;
    opStack.top = -1;
    int j = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];  
        } else if (infix[i] == '(') {
            push(&opStack, "(");
        } else if (infix[i] == ')') {
            while (opStack.top != -1 && strcmp(opStack.items[opStack.top], "(") != 0) {
                postfix[j++] = pop(&opStack)[0];
            }
            pop(&opStack);  // ini buat '('
        } else if (isOperator(infix[i])) {
            while (opStack.top != -1 && precedence(opStack.items[opStack.top][0]) >= precedence(infix[i])) {
                postfix[j++] = pop(&opStack)[0];
            }
            char temp[2] = {infix[i], '\0'};
            push(&opStack, temp);
        }
    }
    
    while (opStack.top != -1) {
        postfix[j++] = pop(&opStack)[0];
    }
    
    postfix[j] = '\0';
}

void postfixToInfix(char *postfix, char *infix) {
    Stack exprStack;
    exprStack.top = -1;
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char temp[2] = {postfix[i], '\0'};
            push(&exprStack, temp);
        } else if (isOperator(postfix[i])) {
            char operand2[MAX], operand1[MAX], expr[MAX];
            
            strcpy(operand2, pop(&exprStack));
            strcpy(operand1, pop(&exprStack));
            
            sprintf(expr, "(%s%c%s)", operand1, postfix[i], operand2);
            push(&exprStack, expr);
        }
    }
    
    strcpy(infix, pop(&exprStack));
}

int main() {
    char infix[MAX], postfix[MAX], convertedInfix[MAX];
    
    printf("Enter an infix expression (NO SPACES): \n");
    scanf("%s", infix);
    
    printf("\n");
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: \n%s\n", postfix);
    
    printf("\n");
    postfixToInfix(postfix, convertedInfix);
    printf("Converted back to Infix: \n%s\n", convertedInfix);
    
    return 0;
}
