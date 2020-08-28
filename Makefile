warnings = -pedantic -ansi  -Wall -Wextra -Wfloat-equal
inc = -Iinc

all: floodit.o board.o game.o handleArguments.o readFile.o
	gcc $^ -o floodit

%.o:
	gcc -c $(warnings) $(inc) -O2 src/$*.c -o $*.o

clean:
	rm *.o
	rm floodit
