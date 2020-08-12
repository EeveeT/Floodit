#include "board.h"

void makeBoard(Board_t *board_ptr, unsigned char len){

  /* We create the len variable to avoid long lines of code*/
  len = board_ptr->length;
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


/* https://www.geeksforgeeks.org/lvalue-and-rvalue-in-c-language/ */
