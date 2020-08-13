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

  FILE *file;

  switch (argc){
    case 1:
        board_ptr->length = DEFAULT_BOARD_SIZE;
        /*Need to check for a NULL pointer later on*/
        makeBoard(board_ptr);
      break;
    case 2:
      /* boardSize 1-9  incomplete*/
      printf("Trying to open file %s\n",argv[1]);
        file = fopen(argv[1], "r");
        printf("File = %p \n", file);
        /* To check if argc == 2 is either a file or an int, we try to
          open a file by default to check if there is a file or not*/
        if(file == NULL){
          /* If we get to here, we now need to check if argv[1] is a single int */
          if(strlen(argv[1]) != 1){
            fprintf(stderr, "Incorrect argument, try to use a number between 2-9");
            fprintf(stderr, "Or you attempted to use a .txt file that does not exist");
            exit(-1);
          }
          else{
            /*Checking the first char of argv[1] by indexing [0] */
            if(isdigit(argv[1][0])){
              /* initialise board with number stored in argv[1]
                 and to convert that number from a char to an actual
                 numeric value, we take away the ASCII character '0'
              */
              printf("Argument given is: %c\n",argv[1][0]);
              board_ptr->length = argv[1][0] - '0';
              if(board_ptr->length < 2){
                fprintf(stderr, "0-1 is an invalid input");
                exit(-1);
              }
              printf("Converted to an int %c\n",board_ptr->length);
              makeBoard(board_ptr);
              printf("valid number input found\n");
            }
            else{
              fprintf(stderr, "Failed: You passed in a letter which is an \
              invalid text file, please try a number");
              exit(-1);
            }

      break;
    case 3:
      /*board size and number of colours determiend by user*/
      /*
        - As with case two, get the user input for argv[1][0] and argv [2][0]
        - Check if the inputs from the user are valid and the set the board up!
       */
       if(isdigit(argv[1][0])){
         printf("argument given is: %c \n", argv[1][0]);
         board_ptr->length = argv[1][0] - '0';
         if(board_ptr->length < 2){
           fprintf(stderr, "Board size too small, must be between 2-9\n");
           exit(-1);
         }
         printf("converted to an int %c\n",board_ptr->length);
         makeBoard(board_ptr);
       }
      break;
    default:
      /* else error */
      fprintf(stderr, "something went wrong\n");

      }
    }
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
