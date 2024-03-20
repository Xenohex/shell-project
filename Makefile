wish: main.o shell.o commands.o redirection.o shared.o error.o
	gcc -o wish main.o shell.o commands.o redirection.o shared.o error.o -Wall

main: main.c
	gcc -c main.c -Wall

shell: shell.c
	gcc -c shell.c -Wall

commands: commands.c
	gcc -c commands.c -Wall

redirection: redirection.c
	gcc -c redirection.o -Wall

shared: shared.c
	gcc -c shared.c -Wall

error: error.c
	gcc -c error.c -Wall
