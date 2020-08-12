#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOARD_SIZE 20
#define DEFAULT_BOARD_SIZE 14

/*To keep things clearer, we can use Colour instead of unsigned char
  even though they are the same, just so it's neater to use Colour*/
typedef unsigned char Colour_t;

/*As the max board size is 20, we can use and unsigned char because we don't
  want negative numbers which an unsigned numeric type ensures. We don't need
  more than 1 btye of memory for the board size, so char would be more efficient
  than an int */
typedef struct{
  unsigned char length;
  Colour_t *array2d;
} Board_t;

int makeBoard(unsigned char len);
void cleanUpBoard(Board_t *board_ptr);
void setColourAt(Board_t *board_ptr, unsigned char x, unsigned char y, Colour_t colour);
Colour_t getColourAt(Board_t *board_ptr, unsigned char x, unsigned char y);
Colour_t colourAt(Board_t *board_ptr, unsigned char x, unsigned char y);
unsigned int getIndexFromXY(Board_t *board_ptr, unsigned char x, unsigned char y);
void print2dArray(Board_t *board_ptr);
