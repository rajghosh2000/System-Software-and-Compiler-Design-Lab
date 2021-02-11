#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SPACE 50

void fgetc_print(FILE *fp)
{
        char c;
        int i = 1;

        printf("1. ");
        while(!feof(fp))
        {
                c = fgetc(fp);

                if(c == '\n')
                {
                        printf("%c", c);

                        printf("\n%d. ", ++i);

                        continue;
                }

                printf("%c", c);
        }
        printf("\n");

}

int main()
{
        FILE *fp;
        int choice, i;
        char str[SPACE], c;

        fp = fopen("file.txt", "r");

        if(fp == NULL)
        {
                printf("Can't open file.");
                exit(0);
        }

        else
        {
                printf("\nPrint using fgets : \n");
                fgetc_print(fp);
        }
        return 0;
}