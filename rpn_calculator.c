#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define STACKSIZE  128
#define PUSHBACK 16

int pop(void);
void push(int);

int getint(int);

char getch(void);
void ungetch(char);

int stack[STACKSIZE];
char pushback[PUSHBACK];

int stack_p;
int push_p;

int main()
{
    double op1, op2, value;
    int  i;
    char c;

    push_p = 0;
    stack_p = 0;

    for(i = 0; i < STACKSIZE; i++)
        stack[i] = 0;

    while((c = getchar()) != '\0'){

        if(c == '\n')
            printf("%d\n",stack[stack_p-1]);

        if(isspace(c))
            continue;

        if(isdigit(c)){
            value = getint(c - '0');
            push(value);
            continue;
        }

        switch(c){

            case '+':
                op2 = pop();
                op1 = pop();
                push(op1 + op2);
                break;

            case '-':
                op2 = pop();
                op1 = pop();
                push(op1 - op2);
                break;

            case '*':
                op2 = pop();
                op1= pop();
                push(op1 * op2);
                break;

            case '/':
                op2 = pop();
                op1 = pop();
                if(op2)
                    push(op1 / op2);
                break;

            case '^':
                op2 = pop();
                op1 = pop();
                value = pow(op1,op2);
                push(value);
        }

    }

    return 0;

}

int getint(int n)
{

    char c;

    while(isdigit(c = getch())){
        n = n * 10 + (c - '0');
    }

    return n;

}

int pop()
{
    int n;
    n = stack[--stack_p];
    stack[stack_p] = 0;
    return n;
}

void push(int value)
{
    if(stack_p < STACKSIZE - 1)
        stack[stack_p++] = value;
}

char getch(void)
{
    return push_p  == 0 ? getchar() : pushback[push_p--];
}

void ungetch(char c)
{
    stack[push_p] = c;
}











