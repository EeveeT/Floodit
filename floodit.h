#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BOARD_SIZE 20
#define MIN_BOARD_SIZE 2
#define DEFAULT_BOARD_SIZE 14
#define DEFAULT_NUM_COLOURS 6
#define MAX_NUM_COLOURS 9
#define MIN_NUM_COLOURS 1
#define NEXT_CELL 1
#define START_CELL 0

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
/*Like MAX_CHAR_LEN, largest line length in file is MAX_BOARD_SIZE + 1 for
 the '\n' character */
#define MAX_LINE_LEN 21
/* No file.txt being fed into this program, but incase it is, we need to catch it */
#define LARGE_LINE_NUMBER 1000
/* For purposes of calcuating line length we want to ignore '\n'*/
#define NEW_LINE 1
/*
  As with max lenths, need a lower boundary of the size the board could be
  which is 2 x 2 + 2 '/n' new lines. You can't play on a board that is one
  square
*/
#define MIN_CHAR_LEN 6





/*To keep things clearer, we can use Colour instead of unsigned char
  even though they are the same, just so it's neater to use Colour*/
typedef unsigned char Colour_t;
//typedef size_t Line_t;

/*As the max board size is 20, we can use and unsigned char because we don't
  want negative numbers which an unsigned numeric type ensures. We don't need
  more than 1 btye of memory for the board size, so char would be more efficient
  than an int */
typedef struct{
  unsigned char length;
  unsigned char colourCount;
  /* N.B., think about renaming array2d as it's not 2d */
  Colour_t *array2d;
} Board_t;


void setUpBoardMem(Board_t *board_ptr);
void cleanUpBoard(Board_t *board_ptr);
void setColourAt(Board_t *board_ptr, unsigned char col, unsigned char row, Colour_t colour);
Colour_t getColourAt(Board_t *board_ptr, unsigned char col, unsigned char row);
Colour_t colourAt(Board_t *board_ptr, unsigned char col, unsigned char row);
unsigned int getIndexFromColRow(Board_t *board_ptr, unsigned char col, unsigned char row);
void printBoard(Board_t *board_ptr);
void handleArguements(int argc, char* argv[], Board_t *board_ptr);
void handleFirstArgument(Board_t *board_ptr);
void handleFileArgument(Board_t *board_ptr, FILE *file);
void handleSecondArgumentLength(char* argv[], Board_t *board_ptr);
void handleThirdArgumentLength(char* argv[], Board_t *board_ptr);
void checkBoardLenValid(Board_t *board_ptr);
void checkLineLenValid(char line[], unsigned char *firstLineLen_ptr);
void checkSquareBoard(unsigned char col, unsigned char row);
void checkColourValid(char line[]);
void fillBoardFromTxtFile(Board_t *board_ptr, FILE *file);
int readTxtFileToArray(Board_t*board_ptr, FILE *file);
bool checkIfWon(Board_t *board_ptr);
Colour_t captureInputTurn(Board_t *board_ptr, int turnCounter);
unsigned int generateRand(Board_t *board_ptr);
void fillBoard(Board_t *board_ptr);
void updateBoard(Board_t *board_ptr, Colour_t fillColour);
void updateBoardRecursive(
  Board_t *board_ptr,
  unsigned char col, unsigned char row,
  Colour_t fillColour, Colour_t targetColour
);
bool isValidCoord(Board_t *board_ptr, unsigned char col, unsigned char row);
/*void handleThirdArgumentColours(int argv, char* argv[], Board_t *board_ptr);*/
