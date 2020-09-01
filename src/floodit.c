#include "floodit.h"

#ifndef TEST
  #define TEST 0
#endif

int main (int argc, char *argv[]){
  if(TEST){
    test();
  }
else{
    /*  This is the real board we always want to use, hence why it is in main,
        and this is why we always have to send a pointer to other functions to
        THIS board here in main
    */
    Board_t board;
    if(handleArguments(argc, argv, &board) == failed){
      return -1;
    }
    /*The & enables the function to access the address in memory
      to where board is stored */
    /*if(!setUpBoardMem(&board, board.length)){
      fprintf(stderr, "This should never have happened\n");
    }*/
    runGame(&board);
    /*When user quits or wins, need to cleanUpBoard() */
    cleanUpBoard(&board);
  }
  return 0;
}
/* So that we don't get hundreds of print statements when testing that invalid
   arguments passed into functions when testing, we only print error messages
   when playing the game to help a user*/
void logError(char* errorMessage){
  if(!TEST){
    fprintf(stderr, "%s", errorMessage);
  }
}
