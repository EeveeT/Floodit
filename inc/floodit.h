#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_BOARD_SIZE 20
#define MIN_BOARD_SIZE 2
#define DEFAULT_BOARD_SIZE 14
#define DEFAULT_NUM_COLOURS 6
#define MAX_NUM_COLOURS 9
#define MIN_NUM_COLOURS 1
#define NEXT_CELL 1
#define START_CELL 0
#define INPUT_COUNT 1
#define NO_ERROR 0
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
#define MAX_LINE_LEN (MAX_BOARD_SIZE + 1)
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
typedef unsigned int u_int;
typedef unsigned char u_char;

/*As the max board size is 20, we can use and u_char because we don't
  want negative numbers which an unsigned numeric type ensures. We don't need
  more than 1 btye of memory for the board size, so char would be more efficient
  than an int */
typedef struct{
  u_char length;
  Colour_t colourCount;
  /* N.B., think about renaming array2d as it's not 2d */
  Colour_t *array2d;
} Board_t;


void setUpBoardMem(Board_t *board_ptr);
void cleanUpBoard(Board_t *board_ptr);
void setColourAt(Board_t *board_ptr, u_char col, u_char row, Colour_t colour);
Colour_t getColourAt(Board_t *board_ptr, u_char col, u_char row);
Colour_t colourAt(Board_t *board_ptr, u_char col, u_char row);
u_int getIndexFromColRow(Board_t *board_ptr, u_char col, u_char row);
void printBoard(Board_t *board_ptr);
void handleArguments(int argc, char* argv[], Board_t *board_ptr);
void setUpDefaultBoard(Board_t *board_ptr);
void handleFileArgument(Board_t *board_ptr, FILE *file);
void handleSecondArgumentLength(char* argv[], Board_t *board_ptr);
void handleThirdArgumentLength(char* argv[], Board_t *board_ptr);
void checkBoardLenValid(Board_t *board_ptr);
void checkLineLenValid(char line[], u_char *firstLineLen_ptr);
void checkSquareBoard(u_char col, u_char row);
void handleBoardColours(char line[], Colour_t *maxColour_ptr);
void handleFile(Board_t *board_ptr, FILE *file);
u_int getLineLength(char line[]);
void assertAllDigits(char line[], u_int lineLength);
void handleLineLength(Board_t *board_ptr, u_char *boardSize_ptr, u_int lineLength);
void fillRow(Board_t *board_ptr, char line[], u_int lineLength, u_char row);
Colour_t digitToColour(char digit);
void findMaxColour(char line[], u_int lineLength, Colour_t *maxColour);
bool stringIsEmpty(char string[]);
bool checkIfWon(Board_t *board_ptr);
Colour_t captureInputTurn(Board_t *board_ptr, int turnCounter);
u_int generateRand(Board_t *board_ptr);
void fillBoard(Board_t *board_ptr);
void updateBoard(Board_t *board_ptr, Colour_t fillColour);
void updateBoardRecursive(
  Board_t *board_ptr,
  u_char col, u_char row,
  Colour_t fillColour, Colour_t targetColour
);
bool isValidCoord(Board_t *board_ptr, u_char col, u_char row);
bool isValidColour(Board_t *board_ptr, Colour_t colour);
/*void handleThirdArgumentColours(int argv, char* argv[], Board_t *board_ptr);*/
