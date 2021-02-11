#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
    	perror("Usage: ./a.out <filename>"); //For this I have used text.txt
    	exit(1);
    }

    int f_no; //Field Number

    printf("Enter the Field Number: \n");
    scanf("%d", &f_no);

    FILE* file = fopen(argv[1], "r");

    if(file == NULL)
    {
	    perror("File Error\n");
	    exit(1);
    }

    int count = 0;
    char ch, prev_c;

    while((ch = fgetc(file)) != EOF)
    {
	    if(ch == '\n')
	    {
	        printf("\n");
	        count = 0;
	    }
	    if(ch == ' ' && prev_c != ' ' && prev_c != '\n')
	    {
	        count++;
	    }
	    if(count == f_no - 1)
	    {
	        printf("%c", ch);
	    }
	    prev_c = ch;
    }
}