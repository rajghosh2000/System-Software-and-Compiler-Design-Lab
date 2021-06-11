#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 1000
#define TYPE int

#define MAX_SIZE 100

//=======================================================================================================
// The While Statement
//=======================================================================================================
char str[MAX_SIZE] = "W(x==5)B7*2-6+8E";
int cnt = 0;


//=======================================================================================================
// Using Stack Based Method To Find The Soltuion 
//=======================================================================================================
typedef struct
{
    TYPE items[SIZE];
    TYPE top;
} stack;
void initialize(stack *s)
{
    s->top = 0;
}
void push(stack *s, TYPE value)
{
    s->items[s->top] = value;
    s->top++;
}
TYPE pop(stack *s)
{
    s->top--;
    return s->items[s->top];
}
TYPE top(stack *s)
{
    return s->items[s->top - 1];
}
TYPE isempty(stack *s)
{
    if (s->top == 0)
        return 1;
    return 0;
}
TYPE peek(stack *s)
{
    TYPE value = pop(s);
    push(s, value);
    return value;
}
TYPE evaluatePostfix(char postfix[])
{
    stack *s = (stack *)malloc(sizeof(stack));
    initialize(s);
    TYPE i;
    for (i = 0; i < strlen(postfix); i++)
    {
        if (isdigit(postfix[i]))
        {
            push(s, postfix[i] - '0');
        }
        else
        {
            TYPE a = pop(s);
            TYPE b = pop(s);
            switch (postfix[i])
            {
            case '+':
                push(s, a + b);
                break;
            case '-':
                push(s, b - a);
                break;
            case '*':
                push(s, a * b);
                break;
            case '/':
                push(s, b / a);
                break;
            default:
                break;
            }
        }
    }
    TYPE y = pop(s);
    return y;
}
TYPE priority(char c)
{
    if (c >= '0' && c <= '9')
        return 0;
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
        return 9;
    default:
        return -1;
    }
}
void infixTopostfix1(char infix[], char postfix[])
{
    stack *p = (stack *)malloc(sizeof(stack));
    char c;
    TYPE index = 0;
    while (c = *infix++)
    {
        TYPE pr = priority(c);
        if (!pr)
            postfix[index++] = c;
        else if (c == '(')
        {
            while (!isempty(p) && peek(p) != ')')
                postfix[index++] = pop(p);
            pop(p);
        }
        else
        {
            while (!isempty(p) && priority(peek(p)) >= pr && peek(p) != '(')
            {
                char value = pop(p);
                if (value != '(')
                    postfix[index++] = value;
            }
            push(p, c);
        }
    }

    while (!isempty(p))
        postfix[index++] = pop(p);
    postfix[index++] = 0;
    for (index = 0; index < strlen(postfix); index++)
        printf("%c ", postfix[index]);
    printf("\n");
}
void infixTopostfix(char infix[], char postfix[])
{
    char ch;
    TYPE index = 0;
    stack *s = (stack *)malloc(sizeof(stack));
    while (ch = *infix++)
    {
        TYPE pr = priority(ch);
        if (!pr)
            postfix[index++] = ch;
        else if (ch == ')') // pop up to (
        {
            while (!isempty(s) && peek(s) != '(')
                postfix[index++] = pop(s);
            pop(s);
        }
        else
        {
            while (!isempty(s) && priority(peek(s)) >= pr && peek(s) != '(')
            {
                char value = pop(s);
                if (value != '(')
                    postfix[index++] = value;
            }
            push(s, ch);
        }
    }
    while (!isempty(s))
        postfix[index++] = pop(s); // remaining
    postfix[index++] = 0;
    printf("\n");
}

//=======================================================================================================
// Main Solving Function
//=======================================================================================================
void eqnSolver(char eqn[])
{
    char str[100];
    char postfix[100];
    infixTopostfix(eqn, postfix);
    printf("Result of the Expression within the While Loop : %d\n", evaluatePostfix(postfix));
}

//=======================================================================================================
// Equation Reciever Function After While Loop Authentication
//=======================================================================================================
void eqnStart()
{
    if (str[cnt] == 'B')
    {
        int t = ++cnt;
        int i = 0;
        char exp[100];
        while (str[t] != 'E')
        {
            exp[i]=str[t];
            t++;
            i++;
        }
        printf("\tmyNum = %s\n",exp);
        printf("    End\n\n");
        printf("==============================================================\n\n");
        eqnSolver(exp);
    }
    else
    {
        printf("Type Err\n");
        exit(0);
    }
}

//=======================================================================================================
// Start Function For Check The While Statement Provided
//=======================================================================================================
void Start()
{
    if (str[cnt] == 'W')
    {
        printf("==============================================================\n");
        printf("Code Found :\n");
        printf("==============================================================\n\n");
        printf("While ");
        cnt++;
        return Start();
    }
    else if (str[cnt] == '(')
    {
        printf("( ");
        cnt++;
        if (str[cnt] == 'x')
        {
            printf("x ");
            if (str[cnt + 1] == '=' && str[cnt + 2] == '=')
            {
                printf("== ");
                cnt = cnt + 3;
                if (isdigit(str[cnt]))
                {
                    printf("%c ", str[cnt]);
                    if (str[++cnt] == ')')
                    {
                        printf(")\n");
                        printf("    Begin : \n");
                        cnt++;
                        eqnStart();
                    }
                    else
                    {
                        printf("Parenthesis Err\n");
                        exit(0);
                    }
                }
                else
                {
                    printf("Comparision Number Missing\n");
                    exit(0);
                }
            }
            else
            {
                printf("Wrong Statement\n");
                exit(0);
            }
        }
        else
        {
            printf("Wrong Statement\n");
            exit(0);
        }
    }
}

//=======================================================================================================
// Main 
//=======================================================================================================
int main()
{
    Start(); 
    return 0;
}
