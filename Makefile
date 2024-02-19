wish: main.o modes.o echo.o
	gcc -o wish main.o modes.o echo.o

main: main.c
	gcc -c main.c

modes: modes.c
	gcc -c modes.c

echo: echo.c
	gcc -c echo.c

