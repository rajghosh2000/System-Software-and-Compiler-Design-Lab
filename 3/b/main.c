//======================================================================================================================================================
    //Symbol Table and Intermediate Code
    
    //Identifiers
    //1 Immediate- 1bytes
    //2 Symbol- 2bytes
    //3 Literal- depends on the length
    //4 Register- 1bytes
    //Mnemonics- 1bytes
//======================================================================================================================================================




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "token.h"

//======================================================================================================================================================
//    The Global Variables
//======================================================================================================================================================

int count_symbol;
int count_literal;
int location;

//======================================================================================================================================================
//    The different structures used are as folows
//======================================================================================================================================================

struct code
{
    char name[7];
    int id;
    int type;
    int opcode;
};
struct symbol
{
    char name[15][15];
    int address[15];
    char value[5][15];
};
struct literals
{
    char name[15][15];
    int address[15];
};
struct code m[19] = {
    {"START", 1, 1, -1},
    {"STOP", 2, 1, -1},
    {"ADD", 3, 1, -1},
    {"DC", 20, 2, -1},
    {"DS", 19, 2, -1},
    {"END", 24, 3, 0},
    {"LTORG", 23, 3, 1},
    {"SUB", 5, 3, 2},
    {"MULT", 6, 3, 3},
    {"LOAD", 7, 3, 4},
    {"TRIM", 10, 3, 5},
    {"TRANS", 9, 3, 6},
    {"STORE", 8, 3, 7},
    {"DIV", 11, 3, 8},
    {"READ", 12, 3, 9},
    {"PRINT", 13, 3, 10},
    {"LIR", 14, 3, 11},
    {"LOOP", 18, 3, 12},
    {"IIR", 17, 3, 13},
};

//======================================================================================================================================================
//    The structures declaration used are as folows
//======================================================================================================================================================

struct symbol sym;
struct literals lit;

//======================================================================================================================================================
//    The functions
//======================================================================================================================================================

int lex(char *b)
{
    if (!strcmp(b, "START"))
        return (TOK_START);
    else if (!strcmp(b, "STOP"))
        return (TOK_STOP);
    else if (!strcmp(b, "ADD"))
        return (TOK_ADD);
    else if (!strcmp(b, "SUB"))
        return (TOK_SUB);
    else if (!strcmp(b, "MULT"))
        return (TOK_MULT);
    else if (!strcmp(b, "LOAD"))
        return (TOK_LOAD);
    else if (!strcmp(b, "STORE"))
        return (TOK_STORE);
    else if (!strcmp(b, "TRANS"))
        return (TOK_TRANS);
    else if (!strcmp(b, "TRIM"))
        return (TOK_TRIM);
    else if (!strcmp(b, "DIV"))
        return (TOK_DIV);
    else if (!strcmp(b, "READ"))
        return (TOK_READ);
    else if (!strcmp(b, "PRINT"))
        return (TOK_PRINT);
    else if (!strcmp(b, "LIR"))
        return (TOK_LIR);
    else if (!strcmp(b, "IIR"))
        return (TOK_IIR);
    else if (!strcmp(b, ","))
        return (TOK_COMMA);
    else if (!strcmp(b, "LOOP"))
        return (TOK_LOOP);
    else if (!strcmp(b, "DS"))
        return (TOK_DS);
    else if (!strcmp(b, "DC"))
        return (TOK_DC);
    else if (!strcmp(b, "LTORG"))
        return (TOK_LTORG);
    else if (!strcmp(b, "END"))
        return (TOK_END);
    else if (!strcmp(b, "3"))
        return (TOK_R3);
    else if (!strcmp(b, "4"))
        return (TOK_R4);
    else if (isdigit(b[0]))
        return (TOK_NUM);
    else
        return (TOK_VAR);
}
int issymbol(char *b)
{
    int j;
    for (j = 0; j < count_symbol; j++)
    {
        if (!strcmp(b, sym.name[j]))
        {
            return (j);
        }
    }
    return (-1);
}
int isliteral(char *b)
{
    int j;
    for (j = 0; j < count_literal; j++)
    {
        if (!strcmp(b, lit.name[j]))
        {
            return (j);
        }
    }
    return (-1);
}

//======================================================================================================================================================
//    The Main code
//======================================================================================================================================================


int main()
{
    FILE *fp = fopen("read.txt", "r");
    if (fp == NULL)
    {
        printf("Error\n");
        return (1);
    }
    int ch, i = 0;
    char b[7] = "";
    location = 0;
    count_symbol = 0;
    count_literal = 0;
    long int len;
    int count = 0;
    int watch = 0, look, care = 0;
    
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch != 32 && ch != 10 && ch != 44)
            b[i++] = ch;
        else
        {
            int see = lex(b);
            if (see == 4)
            {
                if (b[0] == '\'')
                {
                    char temp[10] = "";
                    int jj = 0;
                    len = strlen(b);
                    for (int ii = 1; ii < len - 1; ii++)
                        temp[ii - 1] = b[ii];
                    if ((jj = isliteral(temp)) > -1)
                    {
                        printf("3 %d ", jj);
                        if (care == 1)
                        {
                            strcpy(sym.value[look], temp);
                            care = 0;
                        }
                        location = location + len + 1;
                    }
                    else
                    {
                        strcpy(lit.name[count_literal], temp);
                        lit.address[count_literal] = -1;
                        printf("3 %d ", count_literal);
                        if (care == 1)
                        {
                            strcpy(sym.value[look], temp);
                            care = 0;
                        }
                        count_literal++;
                        location = location + len + 1;
                    }
                }
                else
                {
                    int pos;
                    if ((pos = issymbol(b)) > -1)
                    {
                        printf("2 %d ", pos);
                        look = pos;
                        if (count == 0)
                        {
                            sym.address[pos] = location;
                        }
                        location = location + 2;
                    }
                    else
                    {
                        strcpy(sym.name[count_symbol], b);

                        if (count == 0)
                        {
                            sym.address[count_symbol] = location;
                        }
                        else
                            sym.address[count_symbol] = -1;
                        strcpy(sym.value[count_symbol], "-1");
                        printf("2 %d ", count_symbol);
                        look = count_symbol;
                        count_symbol++;
                        location = location + 2;
                    }
                }
            }
            else if (see == 15)
            {
                printf("1 %s ", b);
                if (watch == 1)
                {
                    location = location + atoi(b);
                    watch = 0;
                }
                else
                    location = location + 1;
            }

            else if (see == 21)
            {
                printf("4 4 ");
                location = location + 1;
            }

            else if (see == 22)
            {
                printf("4 3 ");
                location = location + 1;
            }
            else
            {
                for (int h = 0; h < 19; h++)
                {
                    if (m[h].id == see)
                    {
                        printf("%d ", h);
                        break;
                    }
                }
                if (see == 19)
                {
                    watch = 1;
                }
                if (see == 20)
                {
                    care = 1;
                }
                location = location + 1;
            }
            memset(b, '\0', sizeof(b));
            i = 0;
            count++;
        }
        if (ch == 10)
        {
            char tt;
            if ((tt = fgetc(fp)) != EOF)
            {
                count = 0;
                printf("%c", ch);
            }
            ungetc(tt, fp);
        }
    }
    fclose(fp);
    printf("\n\nSymbol Table-\n");
    printf("Symbol-------Address-------Value\n");
    int lets;
    for (lets = 0; lets < count_symbol; lets++)
    {
        printf("%s\t|\t%d\t|\t%s\n", sym.name[lets], sym.address[lets], sym.value[lets]);
    }
}

