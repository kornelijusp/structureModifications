/**
 * @file Source.c
 * @author Kornelijus Petronis
 * @brief 
 * @version 1.3
 * @date 2019-12-12
 * 
 * @copyright Copyright (c) 2019
 * 
 * 
 * <<<<# This program read bank customers list from csv file and write back to file after modification #>>>>
 * 
 * You can change value of tax and this program subtract tax from balance
 * 
 */

// Library list
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define tax_value 21.0 // %

/**
 * @brief Structure
 * 
 */
struct personalData
{
    char address[100];
    long int phone;
    char birthday[20];
};
struct bank_custumers_details
{
    char name[20];
    char IBAN[30];
    double balance;
    struct personalData pData;
};

// Prototypes
void readFile(struct bank_custumers_details[]);
int countRows();
void writeToFileOnly(struct bank_custumers_details[], int);
void checkErr(FILE *fp);
void tax(struct bank_custumers_details[], double, int);

void main()
{

    int sizeOfArray = countRows() + 1;

    struct bank_custumers_details bank[sizeOfArray];

    readFile(bank);

    tax(bank, tax_value, sizeOfArray);
}
// ==============================================================================================
// ==============================================================================================
/**
 * @brief Tax subtractor
 * 
 * @param bank 
 * @param tax 
 * @param size 
 */
void tax(struct bank_custumers_details bank[], double tax, int size)
{
    FILE *fp;

    fp = (fopen("data2.csv", "w"));
    checkErr(fp);

    tax = (100 - tax) / 100;

    for (int i = 2; i < size; i++)
    {
        fprintf(fp, "%s,%s,%.2lf,%s,%ld,%s", bank[i].name,bank[i].IBAN, bank[i].balance * tax, bank[i].pData.address, bank[i].pData.phone, bank[i].pData.birthday);
    }
    fclose(fp);
}

/**
 * @brief Row counter
 * 
 * @return int 
 */
int countRows()
{

    char buf[1024];
    int row_count = 0;
    FILE *fp;

    fp = (fopen("data2.csv", "r"));

    checkErr(fp);

    while (fgets(buf, 1024, fp))
    {
        row_count++;

        if (row_count == 1)
        {
            continue;
        }
    }
    fclose(fp);
    return row_count;
}

/**
 * @brief Read file
 * 
 * @param bank 
 */
void readFile(struct bank_custumers_details bank[])
{

    char buf[1024];
    int row_count = 0;
    int field_count = 0;
    FILE *fp;

    fp = (fopen("data2.csv", "r"));
    checkErr(fp);

    while (fgets(buf, 1024, fp))
    {
        field_count = 0;
        row_count++;

        if (row_count == 1)
        {
            continue;
        }

        char *field = strtok(buf, ",");
        while (field)
        {
            switch (field_count)
            {
            case 0:
                strcpy(bank[row_count].name, field);
                break;
            case 1:
                strcpy(bank[row_count].IBAN, field);
                break;
            case 2:
                bank[row_count].balance = atof(field);
                break;
            case 3:
                strcpy(bank[row_count].pData.address, field);
                break;
            case 4:
                bank[row_count].pData.phone = atol(field);
                break;
            case 5:
                strcpy(bank[row_count].pData.birthday, field);
                break;
            }
            field = strtok(NULL, ",");

            field_count++;
        }
    }
    fclose(fp);
}

/**
 * @brief Error check
 * 
 * @param fp 
 */
void checkErr(FILE *fp)
{
    if (fp == NULL)
    {
        printf("Error!");
        exit(1);
    }
}