%{
#include<stdio.h>
#include "token.h"
%}

%%

[\n \t] {continue;}
"STOP" {printf("%d ",TOK_STOP);}
"ADD" {printf("%d ",TOK_ADD);}
"SUB" {printf("%d ",TOK_SUB);}
"MULT" {printf("%d ",TOK_MULT);}
"LOAD" {printf("%d ",TOK_LOAD);}
"STORE" {printf("%d ",TOK_STORE);}
"TRANS" {printf("%d ",TOK_TRANS);}
"TRIM" {printf("%d ",TOK_TRIM);}
"DIV" {printf("%d ",TOK_DIV);}
"READ" {printf("%d ",TOK_READ);}
"PRINT" {printf("%d ",TOK_PRINT);}
"LIR" {printf("%d ",TOK_LIR);}
"IIR" {printf("%d ",TOK_IIR);}
"LOOP" {printf("%d ",TOK_LOOP);}
"START" {printf("%d ",TOK_START);}
"END" {printf("%d ",TOK_END);}
"LTORG" {printf("%d ",TOK_LTORG);}
"DS" {printf("%d ",TOK_DS);}
"DC" {printf("%d ",TOK_DC);}
"," {printf("%d ",TOK_COMA);}
[0-9]+ {printf("%d(%s) ",TOK_NUM,yytext);}
[a-zA-Z][a-zA-Z0-9]* {printf("%d(%s) ",TOK_ID,yytext);}

%%

int yywrap(void){}

int main()
{  
        extern FILE *yyin;    // yyin as pointer of File type
         
        yyin = fopen("file.txt","r");  /* yyin points to the file
                                           testtest.c and opens it
                                           in read mode.*/
            // The function that starts the analysis
        yylex();
        printf("\n");
 
        return 0;
}

