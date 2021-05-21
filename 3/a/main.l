//CSB18012 Q3a

%{
#include<stdio.h>
#include "opcodeList.h"

const struct opcodeKeeper opCode[] = {
	{0,{0,0}},
	{1,{0,1}},
	{2,{0,2}},
	{3,{0,3}},
	{4,{0,4}},
	{5,{0,5}},
	{6,{0,6}},
	{7,{0,7}},
	{8,{0,8}},
	{9,{0,9}},
	{10,{1,0}},
	{11,{1,3}},
	{12,{1,2}},
	{13,{1,3}}
};
%}

%%

[\n \t"START""END""LTORG""DS""DC"","] {continue;}
"STOP" {
	printf("%d%d ",opCode[0].opCodePrint[0],opCode[0].opCodePrint[1]);
	fwrite(&opCode[0],sizeof(struct opcodeKeeper),1,yyout);
}
"ADD" {
	printf("%d%d ",opCode[1].opCodePrint[0],opCode[1].opCodePrint[1]);
	fwrite(&opCode[1],sizeof(struct opcodeKeeper),1,yyout);
}
"SUB" {
	printf("%d%d ",opCode[2].opCodePrint[0],opCode[2].opCodePrint[1]);
	fwrite(&opCode[2],sizeof(struct opcodeKeeper),1,yyout);
}
"MULT" {
	printf("%d%d ",opCode[3].opCodePrint[0],opCode[3].opCodePrint[1]);
	fwrite(&opCode[3],sizeof(struct opcodeKeeper),1,yyout);
}
"LOAD" {
	printf("%d%d ",opCode[4].opCodePrint[0],opCode[4].opCodePrint[1]);
	fwrite(&opCode[4],sizeof(struct opcodeKeeper),1,yyout);
}
"STORE" {
	printf("%d%d ",opCode[5].opCodePrint[0],opCode[5].opCodePrint[1]);
	fwrite(&opCode[5],sizeof(struct opcodeKeeper),1,yyout);
}
"TRANS" {
	printf("%d%d ",opCode[6].opCodePrint[0],opCode[6].opCodePrint[1]);
	fwrite(&opCode[6],sizeof(struct opcodeKeeper),1,yyout);
}
"TRIM" {
	printf("%d%d ",opCode[7].opCodePrint[0],opCode[7].opCodePrint[1]);
	fwrite(&opCode[7],sizeof(struct opcodeKeeper),1,yyout);
}
"DIV" {
	printf("%d%d ",opCode[8].opCodePrint[0],opCode[8].opCodePrint[1]);
	fwrite(&opCode[8],sizeof(struct opcodeKeeper),1,yyout);
}
"READ" {
	printf("%d%d ",opCode[9].opCodePrint[0],opCode[9].opCodePrint[1]);
	fwrite(&opCode[9],sizeof(struct opcodeKeeper),1,yyout);
}
"PRINT" {
	printf("%d ",OPCODE_PRINT);
	fwrite(&opCode[10],sizeof(struct opcodeKeeper),1,yyout);
}
"LIR" {
	printf("%d ",OPCODE_LIR);
	fwrite(&opCode[11],sizeof(struct opcodeKeeper),1,yyout);
}
"IIR" {
	printf("%d ",OPCODE_IIR);
	fwrite(&opCode[12],sizeof(struct opcodeKeeper),1,yyout);
}
"LOOP" {
	printf("%d ",OPCODE_LOOP);
	fwrite(&opCode[13],sizeof(struct opcodeKeeper),1,yyout);
}
[0-9]+ {continue;}
[a-zA-Z][a-zA-Z0-9]* {continue;}

%%

int yywrap(void){}

int main()
{  
        extern FILE *yyin,*yyout;    // yyin as pointer of File type
         
        yyin = fopen("file.txt","r");  /* yyin points to the file
                                           testtest.c and opens it
                                           in read mode.*/
            // The function that starts the analysis
        yyout = fopen("binfile.bin","wb");
        yylex();
        printf("\n");
 
        return 0;
}
