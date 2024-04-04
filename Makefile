wish: main.o shell.o commands.o redirection.o parallel.o shared.o error.o
	gcc -o wish main.o shell.o commands.o redirection.o parallel.o shared.o error.o -Wall # wish

clean: 
	rm -r *.o
	rm wish

main.o: main.c
	gcc -c main.c -Wall # main

shell.o: shell.c
	gcc -c shell.c -Wall # shell

commands.o: commands.c
	gcc -c commands.c -Wall # commands

redirection.o: redirection.c
	gcc -c redirection.c -Wall # redirection

parallel.o: parallel.c
	gcc -c parallel.c -Wall # parallel

shared.o: shared.c
	gcc -c shared.c -Wall # shared

error.o: error.c
	gcc -c error.c -Wall # error
