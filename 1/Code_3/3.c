#include<stdio.h>
#include<stdlib.h>

struct student
{
    char name[20];
    int roll_no;
};

struct student input_to_struct(int i)
{
    struct student temp;

    printf("\nEnter name of student no. %d: " , i + 1);
    scanf("%s", temp.name);

    printf("\nEnter roll no. of student no. %d: ", i + 1);
    scanf("%d", &temp.roll_no);

    return temp;
}

void input_to_file(FILE *fp, int choice, struct student var)
{
    int i;

    for(i=0; i<2; i++)
    {
        var = input_to_struct(i);

        fwrite(&var, sizeof(struct student), 1, fp);
    }
}

int main()
{
    FILE *fp;
    struct student var;

    int choice;

    printf("Enter 1 to save the file in binary format and 2 for text format: ");
    scanf("%d", &choice);

    if(choice == 1)
        fp = fopen("Student_record.txt", "w");

    else if(choice == 2)
        fp = fopen("Student_record.bin", "wb");

    else
    {
        printf("\nWrong option.");
        exit(0);
    }

    if(fp == NULL)
    {
        printf("\nCan't open file.");
        exit(0);
    }

    else
    {
        input_to_file(fp, choice, var);
    }
}