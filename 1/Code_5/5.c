#include<stdio.h>
#include<stdlib.h>

int main()
{
       char ch;
       if(argc<2)
    	{
    		printf("Some arguments arent provided.\n");
    		exit(1);
    	}
    	FILE *fp=fopen(argv[1], "rb");

        if(fp == NULL)
        {
                printf("Can't open file.");
                exit(0);
        }
        else
        {
                while((ch = fgetc(fp)) != EOF)
                {
                        if((ch >= 65 && ch <= 90) || (ch  >= 97 && ch <= 122))
                                putchar(ch);

                        else if(ch == '\n')
                                putchar(ch);

                }
        }

        fclose(fp);

        return 0;
}