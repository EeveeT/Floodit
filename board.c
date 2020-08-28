#include "floodit.h"

/* This funciton dynamically allocates the memory for the board */
void setUpBoardMem(Board_t *board_ptr){
  /* We create the len variable to avoid long lines of code*/
  u_char len;
  len = board_ptr->length;
  if(len == 0 || len > MAX_BOARD_SIZE){
    /*If length is invalid, we haven't used malloc, so to be safe,
      we set the array to NULL so we know what it is and this will be caught
      later as an error
    */
    board_ptr->array2d = NULL;
    return;
  }

  /* malloc can only give us a strip in memory, we need length*length for the
    total number of cells (the complete table as one long strip), and we also
    need to calculate how much memory each "Colour_t" will take up

    As malloc doesn't know what type to return, represented as void*, we
    instruct (type caste) it to return our Colour_t instead
  */
  board_ptr->array2d = (Colour_t*)malloc(len * len * sizeof(Colour_t));

  if(board_ptr->array2d == NULL){
    fprintf(stderr, "Error, could not allocate memory for the board.\n");
    exit(-1);
  }
}

/* Once we no longer need the board, we need to ensure we free the memory
   allocated for it
*/
void cleanUpBoard(Board_t *board_ptr){

  free(board_ptr->array2d);

}
/* To fill in a single square with a colour */
void setColourAt(Board_t *board_ptr, u_char col, u_char row, Colour_t colour){

  u_int index = getIndexFromColRow(board_ptr, col, row);
  board_ptr->array2d[index] = colour;


}

Colour_t getColourAt(Board_t *board_ptr, u_char col, u_char row){


    u_int index = getIndexFromColRow(board_ptr, col, row);

    return board_ptr->array2d[index];

}

/* As malloc only provides a strip of memory, we need to be consistent in
   indexing through a '1D' table. */
u_int getIndexFromColRow(Board_t *board_ptr, u_char col, u_char row){

  /* The part in () 'hops' along the 1D array in rows of the length of our
     board. For example, if r = 0, then this indicates the first 'chunk'.
     If r = 2, then we would be in the second row of the length of the board.
     This always gets us the beginning of the row, and c traverses
     through each cell in that row
  */
  u_int index = col + (board_ptr->length * row);

  return index;

}

void checkBoardLenValid(Board_t *board_ptr){

  if(board_ptr->length < MIN_BOARD_SIZE){
    fprintf(stderr, "Board size too small, must be between 2-20.\n");
    exit(-1);
  }
  if(board_ptr->length >  MAX_BOARD_SIZE){
    fprintf(stderr, "Board size too big, must be between 2-20\n");
    exit(-1);
  }
}

void printBoard(Board_t *board_ptr){

  u_char col;
  u_char row;
  u_char len = board_ptr->length;
  Colour_t colour;

  for(row = 0; row < len; row++){
    for(col = 0; col < len; col++){
      colour = getColourAt(board_ptr, col, row);
      printf("%d", colour);
    }
    printf("\n");
  }
}

Colour_t generateRandomColour(Board_t *board_ptr){

  u_char numColours = board_ptr->colourCount;
  /*Using modulo here to constrain upper limit of number of colours
    We have to specify numColours + 1 otherwise the rand() function would
    begin from 0 instead of 1 (which is the minumum number of colours)
  */
  Colour_t randColour = rand() % numColours + MIN_NUM_COLOURS;

  return randColour;
}

void fillBoard(Board_t *board_ptr){

  u_char len = board_ptr->length;
  int col;
  int row;
  Colour_t colour;

  for(col = 0; col < len ; col++){
    for(row = 0; row < len ; row++){
      colour = generateRandomColour(board_ptr);
      setColourAt(board_ptr, col, row, colour);
    }
  }
}

bool isValidColour(Board_t *board_ptr, Colour_t colour){
  return MIN_NUM_COLOURS <= colour && colour <= board_ptr->colourCount;
}
