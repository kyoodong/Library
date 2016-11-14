compile: main.o file.o list.o member.o admin.o
		gcc main.o file.o list.o member.o admin.o
main.o: main.c
		gcc -c main.c
file.o: file.c
		gcc -c file.c
list.o: list.c
		gcc -c list.c

member.o: member.c
		gcc -c member.c

admin.o: admin.c
		gcc -c admin.c
