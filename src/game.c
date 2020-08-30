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
/*
  Starting at the top left cell, we fill in all adjacantly connected cells
  of the same colour with `floodColour`.
*/
void updateBoard(Board_t *board_ptr, Colour_t floodColour){

  Colour_t targetColour = getColourAt(board_ptr, START_CELL, START_CELL);

  /*If target and flood colour are the same, we don't bother updating the board
    as it is already in the state it should be in. It is not an invalid move.*/
  if(targetColour != floodColour){
    updateBoardRecursive(
      board_ptr,
      START_CELL, START_CELL,
      floodColour, targetColour
    );
  }
}
/*
  The target `colour` is the colour we're replacing if it is the colour in the
  top left hand corner. We replace this with the user inputed floodColour.
*/
void updateBoardRecursive(
  Board_t *board_ptr,
  u_char row, u_char col,
  Colour_t floodColour, Colour_t targetColour
){
  u_char nextRow;
  u_char nextCol;
  u_char prevRow;
  u_char prevCol;
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
  setColourAt(board_ptr, row, col, floodColour);

  nextRow = row;
  nextCol = col + NEXT_CELL;

  updateBoardRecursive(board_ptr, nextRow, nextCol, floodColour, targetColour);

  prevRow = row;
  prevCol = col + PREV_CELL;

  updateBoardRecursive(board_ptr, prevRow, prevCol, floodColour, targetColour);

  nextRow = row + NEXT_CELL;
  nextCol = col;

  updateBoardRecursive(board_ptr, nextRow, nextCol, floodColour, targetColour);

  prevRow = row + PREV_CELL;
  prevCol = col;

  updateBoardRecursive(board_ptr, prevRow, prevCol, floodColour, targetColour);

}

Colour_t captureInputTurn(Board_t *board_ptr, int turnCounter){

    Colour_t turnColour;
    bool askingForInput = true;
    int inputCount;

    while (askingForInput) {
      fflush(stdin);
      printf("Turn %d: What number? ", turnCounter);
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
        printf("Please input a colour between %d and %u\n",
                MIN_NUM_COLOURS, board_ptr->colourCount);
      }
      else{
        /* Get to here if user entered nothing or a non-numeric*/
        printf("Please input a number\n");
      }
    }
    return turnColour;
}
