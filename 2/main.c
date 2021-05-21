#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

void tokenGet(char str[]){

    if(!strcmp(str,"STOP")){
        printf("%d ",TOK_STOP);
        return;
    }
    
    else if(!strcmp(str,"ADD")){
        printf("%d  ",TOK_ADD);
        return;
    }
    
    else if(!strcmp(str,"SUB")){
        printf("%d ",TOK_SUB);
        return;
    }

    else if(!strcmp(str,"MULT")){
        printf("%d ",TOK_MULT);
        return;
    }

    else if(!strcmp(str,"LOAD")){
        printf("%d ",TOK_LOAD);
        return;
    }

    else if(!strcmp(str,"STORE")){
        printf("%d ",TOK_STORE);
        return;
    }

    else if(!strcmp(str,"TRANS")){
        printf("%d ",TOK_TRANS);
        return;
    }

    else if(!strcmp(str,"TRIM")){
        printf("%d ",TOK_TRIM);
        return;
    }

    else if(!strcmp(str,"DIV")){
        printf("%d ",TOK_DIV);
        return;
    }

    else if(!strcmp(str,"READ")){
        printf("%d ",TOK_READ);
        return;
    }

    else if(!strcmp(str,"PRINT")){
        printf("%d ",TOK_PRINT);
        return;
    }

    else if(!strcmp(str,"LIR")){
        printf("%d ",TOK_LIR);
        return;
    }

    else if(!strcmp(str,"IIR")){
        printf("%d ",TOK_IIR);
        return;
    }

    else if(!strcmp(str,"LOOP")){
        printf("%d ",TOK_LOOP);
        return;
    }

    else if(!strcmp(str,"START")){
        printf("%d ",TOK_START);
        return;
    }

    else if(!strcmp(str,"END")){
        printf("%d ",TOK_END);
        return;
    }

    else if(!strcmp(str,"LTORG")){
        printf("%d ",TOK_LTORG);
        return;
    }

    else if(!strcmp(str,"DS")){
        printf("%d ",TOK_DS);
        return;
    }

    else if(!strcmp(str,"DC")){
        printf("%d ",TOK_DC);
        return;
    }

    else if(isdigit(str[0])){
        printf("%d(%s) ",TOK_NUM, str);
        return;
    }

    
    else{
        
        printf("%d(%s) ",TOK_ID, str);
        return;
    }

}

void readfile(FILE *fp)
{
    

}

int main()
{
    
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Error in opening file. \n");
    }
    else
    {

        printf("File opened successfully. \n\n");
        char arr[100];
	 int i = 0;
	    char ch;
	    while (!feof(fp))
	    {
		ch = fgetc(fp);
		if (isalpha(ch))
		{
		    while (isalpha(ch) || isdigit(ch))
		    {

		        arr[i] = ch;
		        i++;
		        ch = fgetc(fp);
		    }
		    if(ch==',')
		    printf("%d ",TOK_COMA);
		    arr[i] = '\0';
		    tokenGet(arr);
		    i = 0;
		    arr[0] = '\0';
		}
		
		else if (isdigit(ch))
		{
		    while (isdigit(ch))
		    {

		        arr[i] = ch;
		        i++;
		        ch = fgetc(fp);
		    }

		    if(ch==',')
		    printf("%d ",TOK_COMA);

		    arr[i] = '\0';
		    tokenGet(arr);
		    i = 0;
		    arr[0] = '\0';
		}
		
	    }
    }
    printf("\n");
}
