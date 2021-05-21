#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SPACE 50

void fgets_print(FILE *fp)
{
        char str[MAX];
        int i = 0;

        while(fgets(str, MAX, fp) != NULL)
                printf("\n%d. %s", ++i, str);
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
                fgets_print(fp);
        }
        return 0;
}