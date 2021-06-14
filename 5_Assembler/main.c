/*
//======================================================================================================================================================
    ***Program may/maynot have redundant logic***
    ***This is demo code as per the given question***

    Here  5-7 machine instructions is allowed, and also three addressing modes for operands- register, immediate (one byte), and memory have been allowed. 
    There are 8 registers, and memory addresses are 16-bits. Allowed forward referencing. The machine instructions is quite compact and as per the input txt. 

  Data Structures Used:
	1. Symbol Table 
	2. Mnemonic Table 
  3. Macro Table

  This code generates the output in the machine.txt file and records the output of the given input in the input .txt

//======================================================================================================================================================					
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int location = 1000;

//======================================================================================================================================================
//    The Structures
//======================================================================================================================================================
struct macro
{
  int appearence;
  char macro_name[50];
  char macro_val[100];
};

struct mnemonics
{
  char name[10];
  int type;
  char opcode[5];
  char op1[4];
  char op2[4];
};

struct symbol
{
  int id;
  char sym[10];
  int address;
  int type;
  int size;
};


//======================================================================================================================================================
//    The functions
//======================================================================================================================================================
long decimalToBinary(int decimal)
{
  long binary = 0;
  int rem, temp = 1;

  while (decimal != 0)
  {
    rem = decimal % 2;
    decimal = decimal / 2;
    binary = binary + rem * temp;
    temp = temp * 10;
  }
  return binary;
}

int tokenDetect(char str[])
{

  if (!strcmp(str, "STOP"))
  {
    return 1;
  }

  else if (!strcmp(str, "ADD"))
  {
    return 2;
  }

  else if (!strcmp(str, "SUB"))
  {
    return 3;
  }

  else if (!strcmp(str, "MULT"))
  {
    return 4;
  }

  else if (!strcmp(str, "LOAD"))
  {
    return 5;
  }

  else if (!strcmp(str, "STORE"))
  {
    return 6;
  }

  else if (!strcmp(str, "TRANS"))
  {
    return 7;
  }

  else if (!strcmp(str, "TRIM"))
  {
    return 8;
  }

  else if (!strcmp(str, "DIV"))
  {
    return 9;
  }

  else if (!strcmp(str, "READ"))
  {
    return 10;
  }

  else if (!strcmp(str, "PRINT"))
  {
    return 11;
  }

  else if (!strcmp(str, "LIR"))
  {
    return 12;
  }

  else if (!strcmp(str, "IIR"))
  {
    return 13;
  }

  else if (!strcmp(str, "LOOP"))
  {
    return 14;
  }

  else if (!strcmp(str, "START"))
  {
    return 15;
  }

  else if (!strcmp(str, "END"))
  {
    return 16;
  }

  else if (!strcmp(str, "LTORG"))
  {
    return 17;
  }

  else if (!strcmp(str, "DS"))
  {
    return 18;
  }

  else if (!strcmp(str, "DC"))
  {
    return 19;
  }

  else if (isdigit(str[0]))
  {
    return 20;
  }

  else if (!strcmp(str, "DEFINE"))
  {
    return 22;
  }
  else if (!strcmp(str, "MOV"))
  {
    return 23;
  }
  else if (!strcmp(str, "R0"))
  {
    return 23;
  }

  else if (!strcmp(str, "R1"))
  {
    return 23;
  }

  else
  {

    return 21;
  }
}
int table_fill(FILE *fp, struct macro *table)
{
  int macro_count = 0;
  char yytext[100];
  int i = 0;
  char ch;
  while (!feof(fp))
  {
    char name[50];
    char value[100];
    ch = fgetc(fp);
    if (isalpha(ch))
    {
      while (isalpha(ch) || isdigit(ch))
      {

        yytext[i] = ch;
        i++;
        ch = fgetc(fp);
      }

      yytext[i] = '\0';
      i = 0;
      if (!strcmp(yytext, "DEFINE"))
      {
        char ch1, ch2;
        int name_count = 0;
        int val_count = 0;
        while (1)
        {
          ch1 = fgetc(fp);
          if (ch1 == ' ')
            break;
          name[name_count] = ch1;
          name_count++;
        }
        name[name_count] = '\0';
        name_count = 0;
        val_count = 0;
        while (1)
        {

          ch2 = fgetc(fp);
          if (ch2 == '\n')
            break;
          value[val_count] = ch2;
          val_count++;
        }
        value[val_count] = '\0';
        val_count = 0;

        strcpy(table[macro_count].macro_name, name);
        strcpy(table[macro_count].macro_val, value);
        table[macro_count].appearence = 0;
        macro_count++;
      }

      yytext[0] = '\0';
    }
  }

  return macro_count;
}

void print_table(FILE *fp, struct macro *table, int macro_count)
{
  FILE *fp2 = fopen("output.txt", "w");
  if (fp2 == NULL)
  {
    printf("Error in opening file. \n");
    exit(0);
  }
  char yytext[100];
  int i = 0;
  char ch;
  while (!feof(fp))
  {
    ch = fgetc(fp);
    if (isalpha(ch))
    {
      while (isalpha(ch) || isdigit(ch))
      {

        yytext[i] = ch;
        i++;
        ch = fgetc(fp);
      }

      yytext[i] = '\0';
      int flag = tokenDetect(yytext);
      int flag2 = 0;
      if (flag == 21)
      {
        for (int iter = 0; iter < macro_count; iter++)
        {
          if (!strcmp(table[iter].macro_name, yytext))
          {
            if (table[iter].appearence == 0)
            {
              fputs(yytext, fp2);
              flag2 = 1;
              table[iter].appearence++;
              break;
            }
            else
            {
              fputs(table[iter].macro_val, fp2);
              flag2 = 1;
              break;
            }
          }
        }
      }
      if (flag2 == 0)
      {
        fputs(yytext, fp2);
      }
      if (ch == ',')
        fputs(",", fp2);
      if (ch == '\n')
        fputs("\n", fp2);
      if (ch == ' ')
        fputs(" ", fp2);
      i = 0;
      yytext[0] = '\0';
    }

    else if (isdigit(ch))
    {
      while (isdigit(ch))
      {

        yytext[i] = ch;
        i++;
        ch = fgetc(fp);
      }

      yytext[i] = '\0';
      fputs(yytext, fp2);
      if (ch == ',')
        fputs(",", fp2);
      if (ch == '\n')
        fputs("\n", fp2);
      if (ch == ' ')
        fputs(" ", fp2);
      i = 0;
      yytext[0] = '\0';
    }
  }
  fclose(fp2);
}

void init_table(struct mnemonics *mnemonics_table)
{
  strcpy(mnemonics_table[0].name, "START");
  mnemonics_table[0].type = 1;
  strcpy(mnemonics_table[0].opcode, "NONE");
  strcpy(mnemonics_table[0].op1, "010");
  strcpy(mnemonics_table[0].op2, "000");

  strcpy(mnemonics_table[1].name, "DB");
  mnemonics_table[1].type = 2;
  strcpy(mnemonics_table[1].opcode, "NONE");
  strcpy(mnemonics_table[1].op1, "010");
  strcpy(mnemonics_table[1].op2, "000");

  strcpy(mnemonics_table[2].name, "ADD");
  mnemonics_table[2].type = 3;
  strcpy(mnemonics_table[2].opcode, "0001");
  strcpy(mnemonics_table[2].op1, "111");
  strcpy(mnemonics_table[2].op2, "101");

  strcpy(mnemonics_table[3].name, "MULT");
  mnemonics_table[3].type = 3;
  strcpy(mnemonics_table[3].opcode, "0010");
  strcpy(mnemonics_table[3].op1, "111");
  strcpy(mnemonics_table[3].op2, "101");

  strcpy(mnemonics_table[5].name, "PRINT");
  mnemonics_table[5].type = 2;
  strcpy(mnemonics_table[5].opcode, "NONE");
  strcpy(mnemonics_table[5].op1, "101");
  strcpy(mnemonics_table[5].op2, "000");
}

int isEntry(char str[], struct symbol *obj, int size_table, int size_str)
{
  char temp[10];
  strcpy(temp, str);
  if (temp[size_str - 1] == ':')
    temp[size_str - 1] = '\0';
  for (int i = 0; i < size_table; i++)
  {
    if (!strcmp(str, obj[i].sym))
      return 1;
  }
  return 0;
}

int printSymTable(FILE *fp, struct symbol *table, struct macro *macro_table, int macro_count)
{
  int count = 0;
  char yytext[100];
  int i = 0;
  char ch;
  while (!feof(fp))
  {
    int flag = 0;
    ch = fgetc(fp);
    if (isalpha(ch))
    {
      while (isalpha(ch) || isdigit(ch) || ch == ':')
      {

        yytext[i] = ch;
        i++;
        ch = fgetc(fp);
      }
      yytext[i] = '\0';
      //handling forward reference
      if (!strcmp(yytext, "DB"))
      {
        char temp[100] = {'\0'};
        char ch1;
        int flag3 = 0;
        char num[100];
        int counter = 0;

        while (1)
        {
          ch1 = fgetc(fp);
          temp[counter] = ch1;
          counter++;
          ch1 = fgetc(fp);
          if (ch1 == ' ')
            break;
        }

        temp[counter] = '\0';

        counter = 0;

        while (1)
        {
          ch1 = fgetc(fp);
          num[counter] = ch1;
          counter++;
          ch1 = fgetc(fp);
          if (ch1 == '\n')
            break;
        }
        num[counter] = '\0';
        int rn;
        sscanf(num, "%d", &rn);

        for (int iter1 = 0; iter1 < count; iter1++)
        {
          if (!strcmp(table[iter1].sym, temp))
          {
            table[iter1].address = location + rn;
            table[iter1].size = rn;
            location = location + rn;
            flag3 = 1;
            break;
          }
        }

        if (flag3 == 0)
        {
          strcpy(table[count].sym, temp);
          table[count].type = 2;
          table[count].size = 4;
          table[count].id = count + 1;
          table[count].size = rn;
          table[count].address = location + rn;
          location = location + rn;
          flag3 = 0;
          count++;
        }
      }
      //forward reference handling complete

      else
      {
        for (int iter = 0; iter < macro_count; iter++)
        {
          if (!strcmp(macro_table[iter].macro_name, yytext) || !strcmp(macro_table[iter].macro_val, yytext))
          {
            flag = 1;
            break;
          }
        }
        if (flag == 0)
        {
          if (tokenDetect(yytext) == 21)
          {
            if (isEntry(yytext, table, count, i))
            {
              //do  nothing
            }

            else if (yytext[i - 1] == ':')
            {
              yytext[i - 1] = '\0';
              strcpy(table[count].sym, yytext);
              table[count].type = 1;
              table[count].size = -1;
              table[count].id = count + 1;
              int random = (rand() % 10) + 1;
              table[count].address = location + random;
              location = location + random;
              count++;
            }
            else
            {
              strcpy(table[count].sym, yytext);
              table[count].type = 2;
              table[count].id = count + 1;
              count++;
            }
          }
        }
      }
      i = 0;
      yytext[0] = '\0';
    }
  }
  return count;
}

void printMachineCode(struct mnemonics *mnemonics_table, struct symbol *symbol_table, int symbol_table_size)
{
  FILE *fp1 = fopen("output.txt", "r");
  FILE *fp2 = fopen("machine.txt", "w");
  char yytext[100];
  int i = 0;
  char ch;
  char val1[100] = {'\0'};
  char val2[100] = {'\0'};
  while (!feof(fp1))
  {
    int flag1 = 0;
    int flag2 = 0;
    ch = fgetc(fp1);
    if (isalpha(ch))
    {
      while (isalpha(ch) || isdigit(ch))
      {

        yytext[i] = ch;
        i++;
        ch = fgetc(fp1);
      }
      yytext[i] = '\0';
      if (!strcmp(yytext, "DB") || !strcmp(yytext, "START") || !strcmp(yytext, "PRINT") || !strcmp(yytext, "DEFINE"))
      {
        while (1)
        {
          ch = fgetc(fp1);
          if (ch == '\n')
            break;
        }
        i = 0;
        yytext[0] = '\0';
      }
      else
      {
        for (int iter = 0; iter < 6; iter++)
        {
          if (!strcmp(mnemonics_table[iter].name, yytext))
          {
            if (mnemonics_table[iter].type == 3)
            {
              fputs(mnemonics_table[iter].opcode, fp2);
              flag1 = 1;
              break;
            }
          }
        }

        if (flag1 == 0)
        {
          if (!strcmp("R0", yytext))
          {
            int flag2 = 1;
            fputs("01", fp2);
            if (val1[0] == '\0')
            {
              strcpy(val1, "00000001");
            }
            else if (val2[0] == '\0')
              strcpy(val2, "00000001");
          }
          else if (!strcmp("R1", yytext))
          {
            flag2 = 1;
            fputs("01", fp2);
            if (val1[0] == '\0')
              strcpy(val1, "00000010");
            else if (val2[0] == '\0')
              strcpy(val2, "00000010");
          }
        }

        if (flag2 == 0 && flag1 == 0)
        {

          for (int iter = 0; iter < symbol_table_size; iter++)
          {
            if (!strcmp(symbol_table[iter].sym, yytext))
            {
              fputs("11", fp2);
              if (val1[0] == '\0')
                sprintf(val1, "%ld", decimalToBinary(symbol_table[iter].address));

              else if (val2[0] == '\0')
                sprintf(val2, "%ld", decimalToBinary(symbol_table[iter].address));
            }
          }
        }

        i = 0;
        yytext[0] = '\0';
        if (ch == '\n')
        {

          if (val1[0] != '\0')
          {
            fputs("\n", fp2);
            fputs(val1, fp2);
          }
          if (val2[0] != '\0')
          {
            fputs("\n", fp2);
            fputs(val2, fp2);
          }
          fputs("\n", fp2);
          val1[0] = '\0';
          val2[0] = '\0';
        }

        else if (isdigit(ch))
        {
          while (isdigit(ch))
          {

            yytext[i] = ch;
            i++;
            ch = fgetc(fp1);
          }

          yytext[i] = '\0';
          fputs("00", fp2);
          if (val1[0] == '\0')
            strcpy(val1, yytext);

          else if (val2[0] == '\0')
            strcpy(val2, yytext);

          i = 0;
          yytext[0] = '\0';
          if (ch == '\n')
          {
            if (val1[0] != '\0')
            {
              fputs("\n", fp2);
              fputs(val1, fp2);
            }
            if (val2[0] != '\0')
            {
              fputs("\n", fp2);
              fputs(val2, fp2);
            }
            fputs("\n", fp2);
            val1[0] = '\0';
            val2[0] = '\0';
          }
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
  struct macro table[10];
  int macro_count;
  //preprocessing starts
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error in opening file. \n");
  }
  else
  {
    //printf("Input File opened successfully.\n");
    macro_count = table_fill(fp, table);
  }
  fclose(fp);

  FILE *fp1 = fopen("input.txt", "r");
  if (fp1 == NULL)
  {
    printf("Error in opening file.\n");
  }
  else
  {
    printf("Input File opened successfully.\n");
    print_table(fp1, table, macro_count);
  }
  printf("\n======================================================================================================================================================\n");
  printf("Processing and Assembling....\n");
  printf("***This may take some time***\n");
  printf("\n======================================================================================================================================================\n");
  
  //initializing manual mnemonics table
  struct mnemonics mnemonics_table[6];
  init_table(mnemonics_table);
  //mnemonic table has been initialised

  //creating sybol table
  struct symbol symbol_table[10];
  int symbol_table_size = printSymTable(fp1, symbol_table, table, macro_count); 

  printMachineCode(mnemonics_table, symbol_table, symbol_table_size);
  sleep(5);
  printf("\nOutput file named as machine.txt\n");
  printf("\n======================================================================================================================================================\n");
  fclose(fp1);
  remove("output.txt");
}