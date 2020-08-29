#include "floodit.h"

/* COL ROW NEEDS TO BE REVERSED */

int main (int argc, char *argv[]){

  #ifdef TEST
    test();
  #else
    /*  This is the real board we always want to use, hence why it is in main,
        and this is why we always have to send a pointer to other functions to
        THIS board here in main
    */
    Board_t board;
    handleArguments(argc, argv, &board);
    /*The & enables the function to access the address in memory
      to where board is stored */
    /*if(!setUpBoardMem(&board, board.length)){
      fprintf(stderr, "This should never have happened\n");
    }*/
    runGame(&board);
    /*When user quits or wins, need to cleanUpBoard() */
    cleanUpBoard(&board);
  #endif

  return 0;
}
