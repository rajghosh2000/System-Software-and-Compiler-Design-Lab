/*
//======================================================================================================================================================
    --> This assignment works for the grammer as written. If you want to make or any other grammer change the main part and other functions as per requirement.
    --> '$' is used as end of string for this assignment.

          The entered string is checked for this given grammer for this assignmnet : 
                E->E+E 
                E->E*E 
                E->(E) 
                E->id
//======================================================================================================================================================					
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>

int i = 0, c = 0;
char a[16], arr[20], stack[15], act[10];

//======================================================================================================================================================
//    The Check Function That Checks The String Entered
//======================================================================================================================================================
void check()
{
  strcpy(arr, "REDUCE TO E");
  int j = 0;
  for (j = 0; j < c; j++)
    if (stack[j] == 'i' && stack[j + 1] == 'd')
    {
      stack[j] = 'E';
      stack[j + 1] = '\0';
      printf("\n$%s\t%s$\t%s", stack, a, arr);
      j++;
    }
  for (j = 0; j < c; j++)
    if (stack[j] == 'E' && stack[j + 1] == '+' && stack[j + 2] == 'E')
    {
      stack[j] = 'E';
      stack[j + 1] = '\0';
      stack[j + 2] = '\0';
      printf("\n$%s\t%s$\t%s", stack, a, arr);
      i = i - 2;
    }
  for (j = 0; j < c; j++)
    if (stack[j] == 'E' && stack[j + 1] == '*' && stack[j + 2] == 'E')
    {
      stack[j] = 'E';
      stack[j + 1] = '\0';
      stack[j + 1] = '\0';
      printf("\n$%s\t%s$\t%s", stack, a, arr);
      i = i - 2;
    }
  for (j = 0; j < c; j++)
    if (stack[j] == '(' && stack[j + 1] == 'E' && stack[j + 2] == ')')
    {
      stack[j] = 'E';
      stack[j + 1] = '\0';
      stack[j + 1] = '\0';
      printf("\n$%s\t%s$\t%s", stack, a, arr);
      i = i - 2;
    }
}

//======================================================================================================================================================
//    The Main code
//======================================================================================================================================================
int main()
{
  int j = 0, k = 0;
  puts("The GRAMMAR is:\n\t\t E->E+E \n\t\t E->E*E \n\t\t E->(E) \n\t\t E->id");
  puts("Enter the Input String: ");
  gets(a);
  c = strlen(a);
  strcpy(act, "SHIFT->");
  printf("\nProcessing and Checking.....\n");
  sleep(5);
  puts("\nstack \t input \t action");
  for (k = 0, i = 0; j < c; k++, i++, j++)
  {
    if (a[j] == 'i' && a[j + 1] == 'd')
    {
      stack[i] = a[j];
      stack[i + 1] = a[j + 1];
      stack[i + 2] = '\0';
      a[j] = ' ';
      a[j + 1] = ' ';
      printf("\n$%s\t%s$\t%sid", stack, a, act);
      check();
    }
    else
    {
      stack[i] = a[j];
      stack[i + 1] = '\0';
      a[j] = ' ';
      printf("\n$%s\t%s$\t%ssymbols", stack, a, act);
      check();
    }
  }
  printf("\n");
}
