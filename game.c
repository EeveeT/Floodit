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
      index = getIndexFromXY(board_ptr, c, r);
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

void updateBoard(Board_t *board_ptr, unsigned int userInput){

  unsigned char c = 0;
  unsigned char r = 0;
  unsigned int index;

  index = getIndexFromXY(board_ptr, c, r);
  checkNeighbourCell(board_ptr, 0, 0, userInput);
  board_ptr->array2d[index] = userInput;

}

void checkNeighbourCell(Board_t *board_ptr, unsigned char c, unsigned char r, unsigned int userInput){

  unsigned char cMod;
  unsigned char targC;
  unsigned char targR;
  unsigned char currColour;
  unsigned int index;
  unsigned char startColour;

  index = getIndexFromXY(board_ptr, START_CELL, START_CELL);

  /*The start "colour" at cell 0,0 which is the beginning of the game */
  startColour = board_ptr->array2d[index];

  /*We need to check square"behind" which is -1 to where we currently are
   This loop checks cell behind, current cell, then next cell*/
  for(cMod = NEIGHBOUR_NEG; cMod <= NEIGHBOUR_POS; cMod++){
    targC = c + cMod;
  }
 /* If we receive an invalid coordinate to check, will quit the function
    c and r cannot be equal to board length because index starts at 0, so
    board length is +1*/
  if(c < 0 || c >= board_ptr->length){
    return;
  }
  if(r < 0 || r >= board_ptr->length){
    return;
  }

  index = getIndexFromXY(board_ptr, c, r);
  /*To get the colour at the current cell */
  currColour = board_ptr->array2d[index];
  /* */
  if(startColour != currColour){
    return;
  }

  printf("I am checking c: %u and r: %u\n",c, r);
  /*Checks cell "behind" */
  //targR = r;
  //targC = c + NEIGHBOUR_NEG;

  //checkNeighbourCell(board_ptr, targC, targR);

  //targR = r + NEIGHBOUR_NEG;
  //targC = c;

  //checkNeighbourCell(board_ptr, targC, targR);



  targR = r;
  targC = c + NEIGHBOUR_POS;

  checkNeighbourCell(board_ptr, targC, targR, userInput);

  targR = r + NEIGHBOUR_POS;
  targC = c;

  checkNeighbourCell(board_ptr, targC, targR, userInput);

  board_ptr->array2d[index] = userInput;


}
