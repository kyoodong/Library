compile: main.o file.o list.o
		gcc main.o file.o list.o
main.o: main.c
		gcc -c main.c
file.o: file.c
		gcc -c file.c
list.o: list.c
		gcc -c list.c
