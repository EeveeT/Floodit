#include "floodit.h"


bool checkIfWon(Board_t *board_ptr){

  Colour_t *array = board_ptr->array2d;
  unsigned char len = board_ptr->length;
  unsigned char ch = array[0];
  int c;
  int r;
  unsigned int index;

//printf("entering for loop to check if won\n");
  for(c = 0; c < len ; c++){
  //  printf("going through columns\n");
    for(r = 0 ; r < len ; r++){
      index = getIndexFromColRow(board_ptr, c, r);
  //    printf("Going through rows\n");
    //  printf("ch is: %u\n", ch );
      //printf("array[index] is: %u\n", array[index]);
      if(array[index] != ch){
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
/*

 */
void updateBoardRecursive(
  Board_t *board_ptr,
  unsigned char col, unsigned char row,
  Colour_t fillColour, Colour_t targetColour
){
  unsigned char nextCol;
  unsigned char nextRow;
  Colour_t currColour;

  /*If the coordinate is invalid, we quit the recursion but not the game */
  if(!isValidCoord(board_ptr, col, row)){
    return;
  }

  currColour = getColourAt(board_ptr, col, row);
  /*Checks that target colour is not currrent colour because we don't change the
    colour of any cells that are not the target colour/number*/
  if(targetColour != currColour){
    return;
  }
  setColourAt(board_ptr, col, row, fillColour);

  nextRow = row;
  nextCol = col + NEXT_CELL;

  updateBoardRecursive(board_ptr, nextCol, nextRow, fillColour, targetColour);

  nextRow = row + NEXT_CELL;
  nextCol = col;

  updateBoardRecursive(board_ptr, nextCol, nextRow, fillColour, targetColour);

}
bool isValidCoord(Board_t *board_ptr, unsigned char col, unsigned char row){

  /*
    Col and Row are always greater than 0 because they are unsigned.
    To ensure that col and row are within the board, we compare them
    against the length of the board.
  */
  return (col < board_ptr->length) && (row < board_ptr->length);
}
