#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

//=======================================================================================================
// The Precedence Order for the Operartors. Also check for the same associativity.
//=======================================================================================================
int checkPrecednce(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 0;
    case '*':
    case '/':
        return 1;
    case '^':
        return 2;
    }
    return INT_MAX;
}

//=======================================================================================================
// The Calculation Function
//=======================================================================================================
double calculate(char opr, double n1, double n2)
{
    double output;
    switch (opr)
    {
    case '+':
        output = n1 + n2;
        break;
    case '-':
        output = n1 - n2;
        break;
    case '*':
        output = n1 * n2;
        break;
    case '/':
        output = n1 / n2;
        break;
    default:
        printf("Invalid opr. Sorry opr Not Found\n");
        exit(-1);
    }
    return output;
}

//=======================================================================================================
// Checks if the character passed is a NUM or "." or not
//=======================================================================================================
char isNum(char ch)
{
    if ((ch >= '0' && ch <= '9') || ch == '.')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//=======================================================================================================
// Main Parser Precedence Function for the calculator
//=======================================================================================================
double oprParserEvaluation(char expr[])
{
    double arr[5];
    int k = 0, j = 0, i = 0;
    char opr[5], numbuffer[16], ch;

    for (; (ch = expr[i]) != 0;)
    {
        if (!isNum(ch))
        {
            while ((j > 0) && (checkPrecednce(ch) <= checkPrecednce(opr[j - 1])))
            {
                arr[k - 2] = calculate(opr[j - 1], arr[k - 2], arr[k - 1]);
                j--;
                k--;
            }
            opr[j++] = ch;
        }
        else
        {
            numbuffer[k++] = ch;
            if (!isNum(expr[i + 1]))
            {
                numbuffer[k] = 0;
                k = 0;
                sscanf(numbuffer, "%lf", &arr[k++]);
            }
        }
        i++;
    }

    for (; j > 0; j--)
    {
        arr[k - 2] = calculate(opr[j - 1], arr[k - 2], arr[k - 1]);
        k--;
    }
    return arr[0];
}

//=======================================================================================================
// Main 
//=======================================================================================================
int main()
{
    char expression[100];

    printf("Enter Expression : ");
    scanf("%[^\n]", expression);

    double res = oprParserEvaluation(expression);
    printf("Result = %lf\n", res);
    return 0;
}