project: database.o menu.o
	gcc -o project database.c menu.o

menu.o: menu.c record.h database.h
	gcc -ansi -pedantic-errors -Wall -c menu.c

database.o: database.c record.h
	gcc -ansi -pedantic-errors -Wall -c database.c
