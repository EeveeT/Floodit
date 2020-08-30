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
#define PREV_CELL (-1)
#define START_CELL 0
#define INPUT_COUNT 1
/*Largest line length in file is MAX_BOARD_SIZE + 1 for the '\n' character */
#define MAX_LINE_LEN (MAX_BOARD_SIZE + 1)
/* Used for testing  */
#define MAX_U_CHAR 255

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
  Colour_t *colourArray;
} Board_t;

/* Board Functions */
void setUpBoardMem(Board_t *board_ptr);
void cleanUpBoard(Board_t *board_ptr);
void setColourAt(Board_t *board_ptr, u_char row, u_char col, Colour_t colour);
Colour_t getColourAt(Board_t *board_ptr, u_char row, u_char col);
u_int getIndexFromRowCol(Board_t *board_ptr, u_char row, u_char col);
void assertBoardLenValid(Board_t *board_ptr);
void assertColourCountValid(Board_t *board_ptr);
void printBoard(Board_t *board_ptr);
Colour_t generateRandomColour(Board_t *board_ptr);
void fillBoard(Board_t *board_ptr);
bool isValidCoord(Board_t *board_ptr, u_char row, u_char col);
bool isValidColour(Board_t *board_ptr, Colour_t colour);

/* Handle Arguments Functions (exl. handle file)*/
void handleArguments(int argc, char* argv[], Board_t *board_ptr);
void setUpDefaultBoard(Board_t *board_ptr);
void setUpBoardWithLength(Board_t *board_ptr, u_char inputBoardLength);
void setUpBoardWithLengthAndColours(Board_t *board_ptr,
  u_char inputBoardLength,
  Colour_t colourCount);
void handleSingleArgument(Board_t *board_ptr, char *arg);
void handleTwoArguments(Board_t *board_ptr,
  char *boardLenStr,
  char *colourCountStr);

/* Handle File Functions */
void handleFile(Board_t *board_ptr, FILE *file);
u_int getLineLength(char line[]);
void assertAllDigits(char line[], u_int lineLength);
void handleLineLength(Board_t *board_ptr,
  u_char *boardSize_ptr,
  u_int lineLength);
void fillRow(Board_t *board_ptr, char line[], u_int lineLength, u_char row);
Colour_t digitToColour(char digit);
void findColourCount(char line[], u_int lineLength, Colour_t *colourCount);
bool stringIsEmpty(char string[]);

/* Game Functions */
bool checkIfWon(Board_t *board_ptr);
void updateBoard(Board_t *board_ptr, Colour_t floodColour);
void updateBoardRecursive(
  Board_t *board_ptr,
  u_char row, u_char col,
  Colour_t floodColour, Colour_t targetColour
);
void runGame(Board_t *board_ptr);
Colour_t captureInputTurn(Board_t *board_ptr, int turnCounter);


/* Test Function */
void test(void);
