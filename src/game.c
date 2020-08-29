#include "floodit.h"


bool checkIfWon(Board_t *board_ptr){

  u_char len = board_ptr->length;
  Colour_t colour;
  Colour_t startColour = getColourAt(board_ptr, START_CELL, START_CELL);
  u_char row;
  u_char col;

  for(row = 0 ; row < len ; row++){
    for(col = 0; col < len ; col++){
      colour = getColourAt(board_ptr, row, col);
      if(startColour != colour){
        return false;
      }
    }
  }
  /*If we get to here, then everything in the board must be the same*/
  return true;
}
/*
  Starting at the top left cell, we fill in all adjacantly connected cells
  of the same colour with `fillColour`.
*/
void updateBoard(Board_t *board_ptr, Colour_t fillColour){

  Colour_t targetColour = getColourAt(board_ptr, START_CELL, START_CELL);

  updateBoardRecursive(
    board_ptr,
    START_CELL, START_CELL,
    fillColour, targetColour
  );
}

void updateBoardRecursive(
  Board_t *board_ptr,
  u_char row, u_char col,
  Colour_t fillColour, Colour_t targetColour
){
  u_char nextRow;
  u_char nextCol;
  Colour_t currColour;

  /*If the coordinate is invalid, we quit the recursion but not the game */
  if(!isValidCoord(board_ptr, row, col)){
    return;
  }

  currColour = getColourAt(board_ptr, row, col);
  /*Checks that target colour is not currrent colour because we don't change the
    colour of any cells that are not the target colour/number*/
  if(targetColour != currColour){
    return;
  }
  setColourAt(board_ptr, row, col, fillColour);

  nextRow = row;
  nextCol = col + NEXT_CELL;

  updateBoardRecursive(board_ptr, nextRow, nextCol, fillColour, targetColour);

  nextRow = row + NEXT_CELL;
  nextCol = col;

  updateBoardRecursive(board_ptr, nextRow, nextCol, fillColour, targetColour);

}

bool isValidCoord(Board_t *board_ptr, u_char row, u_char col){
  /*
    Col and Row are always greater than 0 because they are unsigned.
    To ensure that col and row are within the board, we compare them
    against the length of the board.
  */
  return (col < board_ptr->length) && (row < board_ptr->length);
}

void runGame(Board_t *board_ptr){
  u_int turnCounter = 0;
  Colour_t floodColour = 0;

  while(!checkIfWon(board_ptr)){
    turnCounter += 1;
    printBoard(board_ptr);
    floodColour = captureInputTurn(board_ptr, turnCounter);
    updateBoard(board_ptr, floodColour);
  }

  printBoard(board_ptr);

}
/*MAJOR BUG IN HERE - TAKING IN NON DIGITS AND INFINITELY RUNNING AND ALSO MORE THAN ONE NUMBER */
Colour_t captureInputTurn(Board_t *board_ptr, int turnCounter){

    Colour_t turnColour;
    bool askingForInput = true;
    int inputCount;

    while (askingForInput) {
      printf("Turn %d: What number? ", turnCounter);
      /*
        Error number (errno) is where most functions report errors.
        This clears out all errors so we know any errors that do occur are
        related to scanf
        Ref: https://linux.die.net/man/3/errno
      */
      errno =  NO_ERROR;
      /*
        u  = unsigned decimal number (default u_int)
        hh = use a char/u_char
        We can read in a u_char and convert it into a Colout_t
      */
      inputCount = scanf("%hhu", &turnColour);
      /*We only want to read in one thing from scanf, so inputCount must be 1 */
      if(inputCount == INPUT_COUNT && isValidColour(board_ptr, turnColour)){
        /* Input has been found and is valid so we leave the while loop*/
        askingForInput = false;
      }
      else if(inputCount == INPUT_COUNT){
        printf("Please input a valid colour\n");
      }
      else if(errno != NO_ERROR){
        exit(-1);
      }

      else{
        /* Get to here if user entered nothing or invalid input*/
        printf("Please input a number\n");

      }
    }
    return turnColour;
}
bool isValidColour(Board_t *board_ptr, Colour_t colour){
  return MIN_NUM_COLOURS <= colour && colour <= board_ptr->colourCount;
}
