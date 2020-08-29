warnings = -pedantic -ansi  -Wall -Wextra -Wfloat-equal
inc = -Iinc
flags = -O2

all: floodit.o board.o game.o handleArguments.o handleFile.o test.o
	gcc $^ -o floodit

%.o: src/%.c
	gcc -c $(warnings) $(inc) $(flags) $^ -o $*.o

clean:
	rm -f *.o
	rm -f floodit

test: flags += -DTEST
test: | clean all
	./floodit
