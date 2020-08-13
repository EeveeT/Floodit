#include "board.h"

int main (int argc, char *argv[]){

/*  This is the real board we always want to use, hence why it is in main,
    and this is why we always have to send a pointer to other functions to
    THIS board here in main
*/
  Board_t board;
  board.length = DEFAULT_BOARD_SIZE;
  handleArguements(argc, argv, &board);
  /*The & enables the function to access the address in memory
    to where board is stored */
  /*if(!makeBoard(&board, board.length)){
    fprintf(stderr, "This should never have happened\n");
  }*/
  print2dArray(&board);

  /*When user quits or wins, need to cleanUpBoard() */
  cleanUpBoard(&board);

  return 0;
}
/*
  Whenever we see Board_t *board_ptr, think of it like a "tunnel" to
  the orignal board up in main
*/
void handleArguements(int argc, char* argv[], Board_t *board_ptr){

  switch (argc){
    case 1:
      if(argc == 1){
        board_ptr->length = DEFAULT_BOARD_SIZE;
        /*Need to check for a NULL pointer later on*/
        makeBoard(board_ptr);
      }
      break;
    case 2:
      /* boardSize 1-9  incomplete*/
      break;
    case 3:
      /*board size and number of colours determiend by user*/
      break;
    default:
      /* else error */
      fprintf(stderr, "something went wrong\n");

  }
}

 /*If the board has not been malloced, will crash.
  - check if array == NULL
  - check len > 1
  */

void print2dArray(Board_t *board_ptr){

  unsigned char c, r = 0;
  unsigned int index;
  unsigned char len = board_ptr->length;

  printf("Printing board...\n");

  for(r = 0; r < len; r++){
    for(c = 0; c < len; c++){

      index = getIndexFromXY(board_ptr, c, r);
      printf("%u", board_ptr->array2d[index]);

    }
    printf("\n");
  }
}
/*
void fillBoard(Board_t *board_ptr, unsigned char length){



}*/




/*https://www.programiz.com/c-programming/library-function/string.h/strlen */


/* todo:
- pass arguemnts from command line
- load in text file, save to array
- write a function to check if all array cells have the same value and if so,
  they win
*/
