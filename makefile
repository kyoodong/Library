compile: main.o clients.o books.o borrows.o member.o admin.o
		gcc main.o clients.o books.o borrows.o member.o admin.o
main.o: main.c
		gcc -c main.c
clients.o: clients.c
		gcc -c clients.c
books.o: books.c
		gcc -c books.c
borrows.o: borrows.c
		gcc -c borrows.c

member.o: member.c
		gcc -c member.c

admin.o: admin.c
		gcc -c admin.c
