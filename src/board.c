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
    board_ptr->colourArray = NULL;
    return;
  }
  /* malloc can only give us a strip in memory, we need length*length for the
    total number of cells (the complete table as one long strip), and we also
    need to calculate how much memory each "Colour_t" will take up

    As malloc doesn't know what type to return, represented as void*, we
    instruct (type caste) it to return our Colour_t instead
  */
  board_ptr->colourArray = (Colour_t*)malloc(len * len * sizeof(Colour_t));

  if(board_ptr->colourArray == NULL){
    fprintf(stderr, "Error, could not allocate memory for the board.\n");
    exit(-1);
  }
}

/* Once we no longer need the board, we need to ensure we free the memory
   allocated for it
*/
void cleanUpBoard(Board_t *board_ptr){

  free(board_ptr->colourArray);

}
/* To fill in a single square with a colour */
void setColourAt(Board_t *board_ptr, u_char row, u_char col, Colour_t colour){

  u_int index = getIndexFromRowCol(board_ptr, row, col);
  board_ptr->colourArray[index] = colour;

}

Colour_t getColourAt(Board_t *board_ptr, u_char row, u_char col){

    u_int index = getIndexFromRowCol(board_ptr, row, col);

    return board_ptr->colourArray[index];

}
/* As malloc only provides a strip of memory, we need to be consistent in
   indexing through a '1D' table. */
u_int getIndexFromRowCol(Board_t *board_ptr, u_char row, u_char col){

  /* The part in () 'hops' along the array in rows of the length of our
     board. For example, if r = 0, then this indicates the first 'chunk'.
     If r = 2, then we would be in the second row of the length of the board.
     This always gets us the beginning of the row, and c traverses
     through each cell in that row
  */
  u_int index = (board_ptr->length * row) + col;

  return index;

}

void assertBoardLenValid(Board_t *board_ptr){

  if(board_ptr->length < MIN_BOARD_SIZE){
    fprintf(stderr, "Board size too small, must be between 2-20.\n");
    exit(-1);
    /* return 0;*/
  }
  if(board_ptr->length >  MAX_BOARD_SIZE){
    fprintf(stderr, "Board size too big, must be between 2-20\n");
    exit(-1);
    /*return 0 */
  }
  /*else{
    return 1;
  }*/
}

void assertColourCountValid(Board_t *board_ptr){
  if(board_ptr->colourCount < MIN_NUM_COLOURS){
    fprintf(stderr, "Colour is too small\n");
    exit(-1);
  }
  if(board_ptr->colourCount > MAX_NUM_COLOURS){
    fprintf(stderr, "Colour is too large\n");
    exit(-1);
  }
}

void printBoard(Board_t *board_ptr){

  u_char row;
  u_char col;
  u_char len = board_ptr->length;
  Colour_t colour;

  for(row = 0; row < len; row++){
    for(col = 0; col < len; col++){
      colour = getColourAt(board_ptr, row, col);
      printf("%u", colour);
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

bool isValidCoord(Board_t *board_ptr, u_char row, u_char col){
  /*
    Col and Row are always greater than 0 because they are unsigned.
    To ensure that col and row are within the board, we compare them
    against the length of the board.
  */
  return (col < board_ptr->length) && (row < board_ptr->length);
}

bool isValidColour(Board_t *board_ptr, Colour_t colour){
  return MIN_NUM_COLOURS <= colour && colour <= board_ptr->colourCount;
}

void fillBoard(Board_t *board_ptr){

  u_char len = board_ptr->length;
  int row;
  int col;
  Colour_t colour;

  for(row = 0; row < len ; row++){
    for(col = 0; col < len ; col++){
      colour = generateRandomColour(board_ptr);
      setColourAt(board_ptr, row, col, colour);
    }
  }
}
