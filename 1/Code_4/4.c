#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
        FILE *fp;
        char ch;

        if(argc<2)
        	{
        		printf("Some arguments arent provided.\n");
        		exit(1);
        	}

        fp=fopen(argv[1], "rb");
        if(fp == NULL)
        {
                printf("Can't open file.");
                exit(0);
        }

		int lines = 0;
		while(1)
		{
			fread(&ch, sizeof(ch), 1, fp);
			if(feof(fp)) break;
				if(lines % 16 == 0){
					printf("\n%.7o ", lines);
				}
				printf("%.3o ", ch);
				lines++;
		}

        fclose(fp);

        return 0;
}