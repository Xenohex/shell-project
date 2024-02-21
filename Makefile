wish: main.o modes.o commands.o error.o
	gcc -o wish main.o modes.o commands.o error.o

main: main.c
	gcc -c main.c

modes: modes.c
	gcc -c modes.c

commands: commands.c
	gcc -c commands.c

error: error.c
	gcc -c error.c
