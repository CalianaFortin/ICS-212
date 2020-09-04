/************************************************************************
*
*  Name:        Caliana  Fortin
*
*  Homework:    Project
*
*  Class:	ICS 212
*
*  Instructor:  Ravi Narayan
*
*  Date:        November 6, 2019
*
*
*  File         database.h
*
*  Description:
*    This file contains the function prototypes for addRecord, printRecord,
*    printAllRecords, deleteRecords, readfile, and writefile.
*
************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

int addRecord (struct record **, int, char[], char[]);

int printRecord (struct record *, int);

void printAllRecords (struct record *);

int deleteRecord (struct record **, int);

int readfile (struct record **, char[]);

int writefile (struct record *, char[]);

void cleanup(struct record **);

int modifyRecord (struct record *, int, char [ ]);

