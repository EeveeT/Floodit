all:
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 test.c -o test.o
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 board.c -o board.o
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 game.c -o game.o
	gcc test.o board.o game.o -o floodit

clean:
	rm *.o
	rm floodit
