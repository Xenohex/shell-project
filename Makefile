wish: main.o shell.o commands.o error.o
	gcc -o wish main.o shell.o commands.o error.o

main: main.c
	gcc -c main.c

shell: shell.c
	gcc -c shell.c

commands: commands.c
	gcc -c commands.c

error: error.c
	gcc -c error.c
