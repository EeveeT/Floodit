#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOARD_SIZE 20
#define MIN_BOARD_SIZE 2
#define DEFAULT_BOARD_SIZE 14
#define DEFAULT_NUM_COLOURS 6
#define MAX_NUM_COLOURS 9
#define MIN_NUM_COLOURS 1
/*Mac version of new line is '\lf' (line feed) and has an ASCII value of 10*/
#define LF_CHAR 10
/*
   MAX_BOARD_SIZE * MAX_BOARD_SIZE + 20 '\n' chars = 420
   To get the total length of the longest length that a FILE
   or board could be, we multiply the MAX_BOARD_SIZE and as
   there are MAX_BOARD_SIZE '\n' new line chars at the end
   of each new line, this needs to be accounted for.
 */
#define MAX_CHAR_LEN 420
/*
  As with max lenths, need a lower boundary of the size the board could be
  which is 2 x 2 + 2 '/n' new lines. You can't play on a board that is one
  square
*/
#define MIN_CHAR_LEN 6





/*To keep things clearer, we can use Colour instead of unsigned char
  even though they are the same, just so it's neater to use Colour*/
typedef unsigned char Colour_t;

/*As the max board size is 20, we can use and unsigned char because we don't
  want negative numbers which an unsigned numeric type ensures. We don't need
  more than 1 btye of memory for the board size, so char would be more efficient
  than an int */
typedef struct{
  unsigned char length;
  unsigned char maxColour;
  Colour_t *array2d;
} Board_t;


void makeBoard(Board_t *board_ptr);
void cleanUpBoard(Board_t *board_ptr);
void setColourAt(Board_t *board_ptr, unsigned char x, unsigned char y, Colour_t colour);
Colour_t getColourAt(Board_t *board_ptr, unsigned char x, unsigned char y);
Colour_t colourAt(Board_t *board_ptr, unsigned char x, unsigned char y);
unsigned int getIndexFromXY(Board_t *board_ptr, unsigned char x, unsigned char y);
void print2dArray(Board_t *board_ptr);
void handleArguements(int argc, char* argv[], Board_t *board_ptr);
void handleSecondArgumentLength(int argc, char* argv[], Board_t *board_ptr);
void fillBoardFromTxtFile(Board_t *board_ptr, FILE *file);
int readTxtFileToArray(Board_t*board_ptr, FILE *file);
/*void handleThirdArgumentColours(int argv, char* argv[], Board_t *board_ptr);*/
