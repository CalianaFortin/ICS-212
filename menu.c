#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"
#include "database.h"
int debug;

void getaddress(char[], int);

int main(int argc, char * argv[])
{
   int quit = 0;
   int menu;
   int accountNumber;
   int length;
   int compare;
   int size = 80;
   int errorCode = 0;
   char nameOf[25];
   char addressOf[80];
   char input[100];
   struct record * start = NULL;

   if(argc==1)
  {
      debug = 0;
   }
   else if(argc==2)
   {
      compare = strcmp(argv[1], "debug");
      if(compare==0)
      {
       	 debug = 1;
      }
      else
      {
         printf("Invalid arguments: (2)\nProper Usage: ./Project1 \nProper Usage: ./Project1 debug\n");
         exit(0);     
      }
   }
   else if(argc>=2)
   {
      printf("Too many arguments: (2)\nProper Usage: ./Project1 \nProper Usage:./Project1 debug\n");
      exit(0);
   }

   readfile(&start, "savefile.txt");

   while(quit==0)
   {
      menu = 0;
     
      printf("Welcome Please choose one of the following options\n");
      printf("****************************************************"); 
      printf("\n1. Add a new record in the database.\n");
      printf("2. Modify a record in the database\n");
      printf("3. Print infromation about a record\n");
      printf("4. Print all information in database\n");
      printf("5. Delete an existing record from the database.\n");
      printf("6. Quit the program \n");
      printf("****************************************************\n");
      scanf("%d", &menu);
      printf("You selected %d", menu);
      fgets(input, 100, stdin);
      printf("\n");

      if(menu==1) /* Add record */
      {
       	 printf("------------------------You've chosen to add a record. Please input the required information------------------------\n");

         printf("Account Number: \n");
         scanf("%d", &accountNumber);
         fgets(input, 100, stdin);

         printf("Name: \n");
         fgets(nameOf, 25, stdin);
         length = strlen(nameOf);
         nameOf[length]='\0';

         printf("Address(Press Enter Twice To Signify End of Address): \n");
         getaddress(addressOf, size);

         addRecord(&start, accountNumber, nameOf, addressOf);
      }

      else if(menu==2) /* Modify record - accountno as key */
      {
         printf("------------------------You've chosen to modify a record's address. Please enter the Account Number------------------------\n ");
         scanf("%d", &accountNumber);
         fgets(input,100,stdin);
         printf("Modifying Account Number: %d\n", accountNumber);
         printf("Enter new address(Press Enter Twice To Signify End of Address): \n");

         getaddress(addressOf, size);

         errorCode = modifyRecord(start, accountNumber, addressOf);
         if (errorCode == 1)
         {
            printf("The List is Empty\n");
         }
         else if(errorCode == 2)
         {
            printf("The Record wasn't found\n");
         }
      }

      else if(menu==3) /* Print information - accountno as key */
      {
       	 printf("------------------------You've chosen to print the information of an account, Please enter the Account number:------------------------\n");
         scanf("%d", &accountNumber);
         fgets(input, 100, stdin);

         errorCode = printRecord(start, accountNumber);
         if (errorCode == 1)
         {
            printf("-----------The List is Empty----------\n");
         }
        else if(errorCode == 2)
         {
            printf("The record was NOT found\n");
         }

      }

      else if(menu==4) /* Print all */
      { 
         if (start == NULL)
         {
             printf("there is nothing to print\n");
         }
         else  
         {
       	 printf("------------------------You've chosen to print all------------------------ \n\n");
         printAllRecords(start);
         }
      }

      else if(menu==5) /* Delete an existing record */
      {
       	 printf("------------------------You've chosen to delete an existing record, Please enter the Account Number------------------------ ");
         scanf("%d", &accountNumber);
         fgets(input, 100, stdin);

         errorCode = deleteRecord(&start, accountNumber);
         if (errorCode == 1)
         {
            printf("The List is empty\n");
         }
         else if(errorCode == 2)
         {
            printf("Record not found...\n");
         }
      }
      else if(menu==6)
      {
       	 printf("You have chosen to quit the program. Have a nice day.\n");
         writefile(start, "BeforeCleanup.txt");
         cleanup(&start);
         writefile(start, "savefile.txt");
         quit = 1;
      }
      else
      {
       	 printf("That is not a valid menu choice\n");
      }
   }
return 0;
}

void getaddress(char address[], int size)
{
   int i;
   int j = 0;

   if (debug==1)
   {
      printf("\n--\nThis is debug for getaddress: \n");
      printf("Address: %s\nSize: %d \n--\n",address,size);
   }

   for(i = 0; i<80; i++)
   {
      address[i]=fgetc(stdin);

      if (address[i]=='\n')
      {
          j++;
      }
      else
      {
          j=0;
      }

      if(j==2)
      {
       	 address[i-1]='\0';
         i=80;
      }
   }
}


