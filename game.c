#include "board.h"


bool checkIfWon(Board_t *board_ptr){

  Colour_t *array = board_ptr->array2d;
  unsigned char len = board_ptr->length;
  unsigned char ch = array[0];
  int c;
  int r;
  unsigned int index;

printf("entering for loop to check if won\n");
  for(c = 0; c < len ; c++){
    printf("going through columns\n");
    for(r = 0 ; r < len ; r++){
      index = getIndexFromXY(board_ptr, c, r);
      printf("Going through rows\n");
      printf("ch is: %u\n", ch );
      printf("array[index] is: %u\n", array[index]);
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
  board_ptr->array2d[index] = userInput;

}
