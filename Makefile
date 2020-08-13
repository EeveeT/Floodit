all:
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 test.c -o test.o
	gcc -c -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 board.c -o board.o
	gcc test.o board.o -o floodit

clean:
	rm *.o
	rm floodit
