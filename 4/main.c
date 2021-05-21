#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tokenKeeper
{
    char name[40];
};


int main()
{
    FILE *fp = fopen("file.txt", "r");
    struct tokenKeeper token[50];
    if (fp == NULL)
    {
        printf("File can't be Opened\a");
        exit(0);
    }
    char ch,flag[40];
    int i=0,j=0,cntToken=0;
    while (!feof(fp))
    {
        ch=fgetc(fp);
        if(ch == '\n' || ch == ' ')
        {
            token[i].name[j]='\0';
            cntToken++;
            i++;
            j=0;
        }
        else
        {
            token[i].name[j] = ch;
            j++;
        }
    }
    token[i].name[j-1]='\0';
    cntToken++;
    printf("No of Tokens : %d\n",cntToken);
    for(i=0;i<cntToken;i++)
    {
        flag[i]=0;
    }

    printf("\nTHE TEXT READ FROM THE ASSEMBLY FILE : \n\n");
    for(i=0;i<cntToken;i++)
    {
            printf("%s\n",token[i].name);
    }

    for(i=0;i<cntToken;i++)
    {
        if((strcmp("DEFINE",token[i].name))==0)
        {
            char originalText[20],copiedText[20];
            strcpy(originalText,token[i+1].name);
            strcpy(copiedText,token[i+2].name);
            for(j=i+2;j<cntToken;j++)
            {
                if((strcmp(originalText,token[j].name))==0)
                {
                    strcpy(token[j].name,copiedText);
                    flag[j]=1;
                }
            }
        }
    }

    printf("\nTHE TEXT AFTER REPLACEMENT : \n\n");
    for(i=0;i<cntToken;i++)
    {
        if(flag[i]==1)
        {
            printf("%s <--------------- Changed Text As Per DEFINE Statement \n",token[i].name);    
        }
        else
        {
            printf("%s\n",token[i].name);
        }
    }

    fclose(fp);
}
