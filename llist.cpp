/*****************************************************************
//
// NAME:        Caliana Fortin
//
// HOMEWORK:    Project
//
// CLASS:	ICS 212
//
// INSTRUCTOR:  Ravi Narayan
//
// DATE:        September 29, 2019
//
// FILE:        database.c
//
// DESCRIPTION: This file contains the definitions for the 6 functions used
//              in user_interface
//
******************************************************************/

#include "database.h"

void getAddress(char[] , int );

int debug = 0;

/*****************************************************************
//
// Function name:   addRecord
//
// DESCRIPTION:     Stub to add a new record to the bank database
//
// Parameters:      start (struct record **): this starts the function
//                  account (int): account number
//                  name (char []): name of account holder
//                  address (char []): address of account holder
//
// Return values:   0: Done or success
//
*****************************************************************/

int addRecord(struct record ** start, int accountno, char name[], char address[])
{
    struct record * prev;
    struct record * immediate;
    struct record * release;
    int valueForReturn;

    release = (struct record *)malloc(sizeof(struct record));
    valueForReturn = 1;
    release->accountno = accountno;

    /****************************************************************
    * Note: We need to get down the information inputted by the user
    * to the new record we created, which is create. We use strcpy
    * since we want to copy all the contents that have been recorded
    * to release.
    ****************************************************************/

    strcpy(release->name, name);
    strcpy(release->address, address);
    immediate = *start;
    prev = NULL;

    /****************************************************************
    * Note: If the record we are trying add is in empty list, then
    * we check for this in an if statement, and we set the next value of
    * the record to NULL, and the valueForReturn, becomes 0, indicating
    * it has been added.
    ******************************************************************/

    if(*start == NULL)
    {
     	release->next = NULL;
        *start = release;
        valueForReturn = 0;
    }
    else
    {
    /*********************************************************************
    * Note: If it does not pass the above case, that means that the record
    * we are trying to add in a list that contains at least 1 record. So
    * while the list we are looking into is not NULL and the valueForReturn
    * is 1 (indicating a fail), we need to correctly place the record we are
    * trying to add in the correct location. If the record we are trying to
    * add is greater than the record that is in the list, then we add it after.
    * If the record we are trying to add is less than record in the list, then
    * add it before it.
    **********************************************************************/
        while(immediate != NULL && valueForReturn == 1)
        {
            if(release->accountno <= immediate->accountno)
            {
             	release->next = immediate;

                if(prev == NULL)
                {
                    *start = release;
                    valueForReturn = 0;
                }
                else
                {
                    prev->next = release;
                    valueForReturn = 0;
                }
            }
            else if(immediate->next == NULL)
            {
             	release->next = immediate->next;
                immediate->next = release;
                valueForReturn = 0;
            }
            else
            {
             	prev = immediate;
                immediate = prev->next;
            }
        }
      }

    return valueForReturn;

}

/*****************************************************************
//
// Function name:   printRecord
//
// DESCRIPTION:     Stub to print information about a record in the
//                  bank database
//                  
// Parameters:      start (struct record *): starts the stub function
//                  account (int): account number used as the key
// 
// Return values:   0: Done or Success
//
*****************************************************************/

int printRecord(struct record * toBePrint, int accountno)
{
    int valueForReturn;
    struct record * previous;

    previous = NULL;
    valueForReturn = 1;

    if(debug != 0)
    {
     	printf("**********************************************************\n");
        printf("Hey there! You called the printRecord function \n");
        printf("Here is the accountno = %d", accountno);
        printf("\n**********************************************************\n");
    }

     	while(toBePrint != NULL)
        {
            if(accountno == toBePrint->accountno)
            {
             	printf("\n===================================================================\n");
                printf("Account Number: %d \n", toBePrint->accountno);
                printf("UserName: %s \n", toBePrint->name);
                printf("Address: \n %s \n", toBePrint->address);
                printf("===================================================================\n");
                previous = toBePrint;
                toBePrint = previous->next;
                valueForReturn = 0;
            }
            else
            {
             	previous = toBePrint;
                toBePrint = previous->next;
            }
	}

    return valueForReturn;
}

/*****************************************************************
//
// Function name:   modifyRecord
// 
// DESCRIPTION:     Stub to modify a record in the bank database
// 
// Parameters:      start (struct record *): starts function
//                  uaccount (int): account number used as the key
//                  address (char []): address of account holder
//
// Return values:   0: done or Success
//
*****************************************************************/

int modifyRecord(struct record * start, int uaccountno, char uaddress[])
{   
    struct record * current;
    int returnvalue;

    if(debug != 0)
    {
     	printf("**********************************************************\n");
        printf("Hey there! You called the printRecord function \n");
        printf("Here is the accountno = %d", uaccountno);
        printf("\n**********************************************************\n");
    }
    current = start;
    returnvalue = 2;

    if (start != NULL)
    {
        while (current != NULL)
        {
            if (current->accountno == uaccountno)
            {
                strcpy(current->address, uaddress);
                returnvalue = 0;
            }
            else if (current->accountno > uaccountno)
            {
                break;
            }
            current = current->next;
        }
    }
    else
    {
        returnvalue = 1;
    }

    return returnvalue;

}

/*****************************************************************
//
// Function name:   printAllRecords
// 
// DESCRIPTION:     Stub to print all information in the bank database
// 
// Parameters:      start (struct record *): starts the stub function
//                  
*****************************************************************/

void printAllRecords(struct record * all)
{
    struct record * immediate;

    if(debug != 0)
    {
        printf("**********************************************************\n");
        printf("Hey there! You called the printAllRecords function \n");
        printf("**********************************************************\n");
    }

    immediate = all;

    if(all != NULL)
    {
        printf("\n===================================================================\n");
        printf("\t \t \t YOUR RECORDS");
        printf("\n===================================================================\n");

        while(immediate != NULL)
        {
            printf("\n===================================================================\n");
            printf("Account Number: %d \n", immediate->accountno);
            printf("UserName: %s \n", immediate->name);
            printf("Address: \n %s \n", immediate->address);
            printf("===================================================================\n");
            immediate = immediate->next;
        }
    }
    else
    {
     	printf("Hmm... There's nothing here. The database is empty.");
    }
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:    A function to obtain information that the user
//                  inputs. This will record the record and the account
//                  number to delete a record.
//
//  Parameters:    struct record ** toBeDelete, int accountno
//
//  Return values: 0, 1
//
****************************************************************/

int deleteRecord(struct record ** toBeDelete, int accountno)
{
    int valueForReturn;
    struct record * release = *toBeDelete, *previous;

    if(debug != 0)
    {
     	printf("**********************************************************\n");
        printf("Hey there! You called the deleteRecord function \n");
        printf("Here is the accountno = %d", accountno);
        printf("**********************************************************\n");
    }
    valueForReturn = 1;

    while(release!= NULL && release->accountno == accountno)
    {
     	*toBeDelete = release->next;
        free(release);
        release = *toBeDelete;
        valueForReturn = 0;
    }

    while(release != NULL)
    {
     	while(release != NULL && release->accountno != accountno)
        {
            previous = release;
            release = release->next;
        }
	if (release == NULL)
        {
            valueForReturn = 1;
            break;
        }

	previous->next = release->next;
        free(release);
        release = previous->next;
        valueForReturn = 0;
    }

    return valueForReturn;

}

/**************************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:
//                 This function is used to read the record from the text
//                 file and store it in an array.
//
//  Parameters:    struct record ** start, char filename[]
//
//  Return values: 0 if successful 1 if failure
//
**************************************************************************/

int readfile( struct record ** start, char filename[ ] )
{

    FILE *inputFile;
    char accountNumber[100];
    char address[80];
    int accountNum;
    int index;
    int index2;
    int valueForReturn;
    char name[25];

    valueForReturn = 1;
    inputFile = fopen(filename, "r");

    if(debug != 0)
    {
     	printf("**********************************************************\n");
        printf("Hey there! You called the printAllRecords function \n");
        printf("**********************************************************\n");
    }

    if(inputFile != NULL)
    {
     	valueForReturn = 0;

        while(!feof(inputFile))
        {

            if(inputFile == NULL || feof(inputFile))
            {
             	break;
            }
            /* Retrieve the lines of account numbers in the file */

            fgets(accountNumber, 100, inputFile);

            /***********************************************************************
            *Note: Since we donâ€™t have a parameter knowing the amount of
            *records, thereâ€™ll be since the user can create as many as they would
            *like, we have to find a way to know the amount. A function I saw I can
            *use is a atoi, which is on page 42-43. It converts a string of digits into
            *its numeric equivalent. So I can use atoi with the account number as
            *the parameter, within a while loop to retrieve all the account numbers
            *that were made.
            ************************************************************************/

            accountNum = atoi(accountNumber);

            index = strlen(name)-1;

            fgets(address, 80, inputFile);

            index2 = strlen(address)-1;

            if(name[index] == '\n')
            {
             	name[index] = '\0';
            }

            if(address[index2] == '\n')
            {
             	address[index] = '\0';
            }

            addRecord(start, accountNum, name, address);
        }

	fclose(inputFile);
        return valueForReturn;
    }

    return valueForReturn;
}

/*************************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:
//                 This function is used to write data from the records
//                 to a file specified by accarray into a text file.
//                 file and store it in an array.
//
//  Parameters:    struct record * start,  char filename[]
//
//  Return values: 0 if successful 1 if failure
//
*************************************************************************/

int writefile( struct record * start, char filename[ ] )
{

    FILE *outputFile;
    struct record * immediate;

    outputFile = fopen(filename, "w");
    immediate = start;
    if(debug != 0)

    {
        printf("**********************************************************\n");
        printf("Hey there! You called the writefile function \n");
        printf("**********************************************************\n");
    }



   if(outputFile != NULL)
    {
     	while(immediate != NULL)
        {
            fprintf(outputFile, "%d \n ", immediate->accountno);
            fprintf(outputFile, "%s \n",  immediate->name);
            fprintf(outputFile, "%s \n", immediate->address);
            fprintf(outputFile, "\n");

            immediate = immediate->next;
        }

	fclose(outputFile);
        return 0;
    }

    return 1;
}

/**************************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   This function is delete all files.
//                 
//        
//
//  Parameters:    struct record ** pstart
//
//  Return values: none
//
**************************************************************************/

void cleanup(struct record ** pstart){

struct record * current;

    if (debug == 1)
    {
        printf("\nDEBUG: cleanup function called\n\n");
    }

    current = *pstart;

    if (pstart != NULL)
    {
        *pstart = NULL;
        while (current != NULL)
        {
            free(current);
            current = current->next;
        }
    }
}

