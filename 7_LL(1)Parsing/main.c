/*
//======================================================================================================================================================
    --> This assignment works for the grammer created in the createGrammer function. If you want to make or any other grammer change the create Grammer 
	function and other functions as per requirement.

    --> '#' is used as Epsilon for this assignment.

    The Grammer used here :
            S->ABCDE
            A->a|#
            B->b|#
            C->c
            D->d|#
	    E->e|#
				FIRST : 
					First of S : abc
					First of A : a#
					First of B : b#
					First of C : c
					First of D : d#
					First of E : e#
				FOLLOW : 
					Follow of S: $
					Follow of A: bc
					Follow of B: c
					Follow of C: de$
					Follow of D: e$
					Follow of E: $
//======================================================================================================================================================					
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FALSE 0

//======================================================================================================================================================
//    The Structures
//======================================================================================================================================================

struct LL1_rules
{
	char lhs;
	char rhs[10];
	char firstSet[10];
	char followSet[10];
};

struct LL1_rules grammer[7];

void createGrammar()
{
	grammer[0].lhs = 'S';
	strcpy(grammer[0].rhs, "ABCDE");

	grammer[1].lhs = 'A';
	strcpy(grammer[1].rhs, "a|#");

	grammer[2].lhs = 'B';
	strcpy(grammer[2].rhs, "b|#");

	grammer[3].lhs = 'C';
	strcpy(grammer[3].rhs, "c");

	grammer[4].lhs = 'D';
	strcpy(grammer[4].rhs, "d|#");

	grammer[5].lhs = 'E';
	strcpy(grammer[5].rhs, "e|#");
}

//======================================================================================================================================================
//    The functions
//======================================================================================================================================================

int isChar(char c)
{
	if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e')
		return 1;
	return 0;
}

int isTerminal(char c)
{
	if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == '#')
		return 1;
	return 0;
}

int isEpsilon(char *s)
{
	if (s[strlen(s) - 1] == '#')
		return 1;
	return 0;
}

void first(char N)
{
	int i, k = 0;
	for (i = 0; i < 6; i++)
	{
		if (grammer[i].lhs == N)
		{
			if (N >= 'c')
				grammer[i].firstSet[k] = N;
			else if (isTerminal(grammer[i].rhs[0]))
				grammer[i].firstSet[k++] = grammer[i].rhs[0];
			else if (!isTerminal(grammer[i].rhs[0]))
			{
				int j = 0, index = 0, flag = 0;
				while (j < 6)
				{
					if (grammer[j].lhs == grammer[i].rhs[index])
					{
						int t = 0;
						while (t < strlen(grammer[j].rhs))
						{
							if ((isTerminal(grammer[j].rhs[t])) && (isChar(grammer[j].rhs[t])))
							{
								grammer[i].firstSet[k++] = grammer[j].rhs[t];
							}
							else if (grammer[j].rhs[t] == '#')
							{
								index++;
								flag = 1;
							}
							t++;
						}
					}
					j++;
					if (flag == 1)
					{
						j = 0;
						flag = 0;
					}
				}
			}
			if (isEpsilon(grammer[i].rhs))
				grammer[i].firstSet[k++] = '#';
		}
	}
}

int check(char N, char *temp)
{
	int j;
	for (int j = 0; j < strlen(temp); j++)
	{
		if (temp[j] == N)
		{
			return j;
		}
	}
	return 0;
}

char *find_first(char N)
{
	for (int i = 0; i < 7; ++i)
	{
		if (N == grammer[i].lhs)
		{
			return (grammer[i].firstSet);
		}
	}
}

void follow(char N, int t)
{
	int i = 0, j = 0, current, flag = 0;
	char temp[15], first[150], buf;
	if (N == 'S') // For start character case
	{
		grammer[t].followSet[j++] = '$';
	}
	else
	{
		strcpy(temp, grammer[0].rhs);
		current = check(N, temp);
		if (temp[current + 1] == '\0') // For last character case
		{
			strcpy(grammer[t].followSet, grammer[0].followSet);
		}
		else
		{
			int index = current;
			int srch = 1;

			while (temp[index] != '\0')
			{
				strcpy(first, find_first(temp[index + 1]));
				if (isEpsilon(first))
				{
					grammer[t].followSet[j++] = first[0];
					flag = 1;
				}
				else
				{
					grammer[t].followSet[j++] = first[0];
					break;
				}
				index++;
				if ((temp[index + 1] == '\0') && flag == 1)
				{
					grammer[t].followSet[j++] = '$';
					flag = 0;
				}
			}
		}
	}
}

//======================================================================================================================================================
//    The Main code
//======================================================================================================================================================

int main()
{
	printf("------- The Grammer -------\n");
	int i, j;
	createGrammar();
	for (i = 0; i < 6; i++)
	{
		printf("\t%c -> %s\n", grammer[i].lhs, grammer[i].rhs);
	}
	printf("----------------------------\n");
	printf("------- FIRST -------\n");
	for (i = 0; i < 6; i++)
	{
		first(grammer[i].lhs);
	}
	for (i = 0; i < 6; i++)
	{
		printf("First of %c : ", grammer[i].lhs);
		j = 0;
		printf("{ ");
		while (j < strlen(grammer[i].firstSet))
		{
			if (grammer[i].firstSet[j + 1] == '\0')
			{
				printf("%c ", grammer[i].firstSet[j]);
			}
			else
			{
				printf("%c, ", grammer[i].firstSet[j]);
			}

			j++;
		}
		printf("}\n");
	}
	printf("----------------------------\n");
	printf("------- FOLLOW -------\n");
	for (i = 0; i < 6; i++)
	{
		follow(grammer[i].lhs, i);
	}
	for (i = 0; i < 6; i++)
	{
		for (i = 0; i < 6; i++)
		{
			printf("First of %c : ", grammer[i].lhs);
			j = 0;
			printf("{ ");
			while (j < strlen(grammer[i].followSet))
			{
				if (grammer[i].followSet[j + 1] == '\0')
				{
					printf("%c ", grammer[i].followSet[j]);
				}
				else
				{
					printf("%c, ", grammer[i].followSet[j]);
				}

				j++;
			}
			printf("}\n");
		}
	}
	printf("----------------------------\n");
	
	return 0;
}