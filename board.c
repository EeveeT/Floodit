#include "board.h"

/* This funciton dynamically allocates the memory for the board */
void setUpBoardMem(Board_t *board_ptr){
  /* We create the len variable to avoid long lines of code*/
  unsigned char len;
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

   This function receives a pointer to the board, because the free() function
   needs to opertate on the real variable, the real board.
*/
void cleanUpBoard(Board_t *board_ptr){

  free(board_ptr->array2d);

}
/* To fill in a single square with a colour */
void setColourAt(Board_t *board_ptr, unsigned char x, unsigned char y, Colour_t colour){
  /*L value type  */
  unsigned int index = getIndexFromXY(board_ptr, x, y);
  board_ptr->array2d[index] = colour;
  return;

}

Colour_t getColourAt(Board_t *board_ptr, unsigned char x, unsigned char y){

  return colourAt(board_ptr, x, y);

}
/*
  - Getting a value:
  > *colourAt(board, x, y);

  - Setting a value:
  > *colourAt(board, x, y) = colour;

  - In both cases need to dereference
 */
Colour_t colourAt(Board_t *board_ptr, unsigned char x, unsigned char y) {
  /*
    - Unsigned int because negative memory locations don't exist
    - We turn a 2D coordinate to a 1D index we can use
  */

  unsigned int index = getIndexFromXY(board_ptr, x, y);

  return board_ptr->array2d[index];
}

/* As malloc only provides a strip of memory, we need to be consistent in
   indexing through a '1D' table. */
unsigned int getIndexFromXY(Board_t *board_ptr, unsigned char x, unsigned char y){

  /* The part in () 'hops' along the 1D array in chunks of the length of our
     board. For example, if y = 0, then this indicates the first 'chunk'.
     If y = 2, then we would be in the second chunk of the length of the board.
     This always gets us the beginning of the chunk (row), and x traverses
     through each cell in that row
  */
  unsigned int index = x + (board_ptr->length * y);

  return index;

}

unsigned int generateRand(Board_t *board_ptr){

  unsigned char numColours = board_ptr->maxColour;
  //printf("num of colours is: %u \n", numColours );
  unsigned int randColour;
  /*Using modulo here to constrain upper limit of number of colours
    We have to specify numColours + 1 otherwise the rand() function would
    begin from 0 instead of 1 (which is the minumum number of colours)
  */
  randColour = rand() % numColours + MIN_NUM_COLOURS;

  return randColour;
}

void fillBoard(Board_t *board_ptr){

  unsigned char len = board_ptr->length;
  unsigned char *array = board_ptr->array2d;
  int c;
  int r;
  unsigned int index;

//  printf("entering fill board loop\n");

  for(c = 0; c < len ; c++){
  //  printf("looping through columns\n");
    for(r = 0; r < len ; r++){
    //  printf("looping through rows\n" );
      index = getIndexFromXY(board_ptr, c, r);
    //  printf("index is: %u\n", index);
      array[index] = generateRand(board_ptr);
      printf("%u", array[index]);
    }
    printf("\n");
  }
}

/* https://www.geeksforgeeks.org/lvalue-and-rvalue-in-c-language/ */
