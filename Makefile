all:
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 floodit.c -o floodit.o
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 board.c -o board.o
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 game.c -o game.o
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 readFile.c -o readFile.o
	gcc floodit.o board.o game.o readFile.o -o floodit

clean:
	rm *.o
	rm floodit
