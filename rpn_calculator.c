#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACKSIZE  128
#define TABLESIZE 64
#define WORDSIZE 32
#define BUFFSIZE 16

typedef struct name_value {
	
	char *name;
	int value;
	
} entry;

int pop(void);
void push(int);

int getint(int);
void getword(char*);

char getch(void);
void ungetch(char);

int install(char*,int);
int lookup(char*);

int stack[STACKSIZE];
char buffer[BUFFSIZE];
char word[WORDSIZE];
entry wordtable[TABLESIZE];

void resetstack(void);
void resettable(void);
void resetword(void);

int stackp;
int bufp;

int main()
{
    double op1, op2, value;
    char c, *store, *name;
    int i, asg;
	
    asg = 0;
    bufp = 0;
    stackp = 0;

    resetstack();
	resettable();
	resetword();
	
    while((c = getchar()) != '\0'){
		
        if(c == '\n' && !asg){
            printf("%d\n",stack[stackp - 1]);
			continue;
		}
		asg = 0;
		
        if(isspace(c)){
			continue;
		}
            
        if(isdigit(c)){
            value = getint(c - '0');
            push(value);
            continue;
        }
		
		if(isalpha(c)){
			
			store = word;
			*store++ = c;
			getword(store);
			
			if((i = lookup(word))){
				push(i);
				continue;
			}

			name = (char *)malloc((strlen(store) + 1) * sizeof(char));
			strcpy(name, word);
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
				break;
				
			case '?':
				op1 = pop();
				value = sqrt(op1);
				push(value);
				break;

			case '%':
				op2 = pop();
				op1 = pop();
				value = (int)op1 % (int)op2;
				push(value);
				break;

			case '<':
				op2 = pop();
				op1 = pop();
				value = (op1 < op2);
				push(value);
				break;

			case '>':
				op2 = pop();
				op1 = pop();
				value = (op1 > op2);
				push(value);
				break;

			case '=':
				op2 = pop();
				install(name,op2);
				asg = 1;
				break;
			
			case '@':
				resetstack();
				break;

			case '$':
				return 0;
				break;

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

void getword(char *to)
{
	
	while(!isspace(*to++ = getchar()))
		;
	
	to = '\0';
	
}

int install(char *name, int value)
{
	int i;
	char *s;
	
	i = 0;
	for(; i < TABLESIZE && strcmp(wordtable[i].name,""); i++){
		
		if(!strcmp(name,wordtable[i].name)){
			wordtable[i].value = value;
			return 1;
		}

	}
	
	s = (char *)malloc((strlen(name) + 1) * sizeof(char));
	strcpy(s, name);
	
	wordtable[i].name = s;
	wordtable[i].value = value;
	
	return 0;
}

int lookup(char *word)
{
	int i;
	
	i = 0;
	for(; i < TABLESIZE; i++){
		if(strcmp(word,wordtable[i].name) == 0){
			return wordtable[i].value;
		}
	}
		
	return 0;
}

void resetstack(void)
{	


	int i;
	for(i = 0; i < STACKSIZE; i++){
		stack[i] = 0;
    }
}

void resettable(void)
{
	int i;
    for(i = 0; i < TABLESIZE; i++){
		wordtable[i].name = "";
		wordtable[i].value = 0;
    }
}

void resetword(void)
{
	int i;
    for(i = 0; i < WORDSIZE; i++){
		word[i] = 0;
    }
}

int pop(void)
{
    int n;
    n = stack[--stackp];
    stack[stackp] = 0;
    return n;
}

void push(int value)
{
    stack[stackp++] = value;
}

char getch(void)
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(char c)
{
    buffer[bufp++] = c;
}

