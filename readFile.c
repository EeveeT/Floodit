#include "floodit.h"

void handleFileArgument(Board_t *board_ptr, FILE *file){

  char line[LARGE_LINE_NUMBER];
  unsigned char firstLineLen = 0;
  unsigned char colCount = 0;

  while(fgets(line, LARGE_LINE_NUMBER, file) != NULL){
    //printf("Line length is: %d\n",strlen(line));
    checkColourValid(line);
    checkLineLenValid(line, &firstLineLen);
    printf("%s",line);
    colCount += 1;
  }
/*Square check */
  checkSquareBoard(colCount, firstLineLen);
}
/*
void allocateMemoryBoardArray(){}
*/
/*
  Checks line is within parameter or min andmax board size and that
  all lines are the same length by comapring to the first line length
*/
void checkLineLenValid(char line[], unsigned char *firstLineLen_ptr ){

  unsigned char len = strlen(line) - NEW_LINE;

  if(len < MIN_BOARD_SIZE){
    fprintf(stderr, "Board size too small, must be between 2-20.\n");
    exit(-1);
  }
  if(len >  MAX_BOARD_SIZE){
    fprintf(stderr, "Board size too big, must be between 2-20\n");
    exit(-1);
  }
  /*To find the first line, check if current length is 0, if so, can then set the
    first lenth */
  if(*firstLineLen_ptr == 0){
    *firstLineLen_ptr = len;
  }
  else if(*firstLineLen_ptr != len){
    fprintf(stderr, "Varying line lengths, incorrect file format.\n");
    exit(-1);
  }
}

void checkSquareBoard(unsigned char col, unsigned char row){

  if(col != row){
    fprintf(stderr, "Rows and Columns must be the same lenths\n");
    exit(-1);
  }

}

void checkColourValid(char line[]){

  int i = 0;
  int len = strlen(line) - NEW_LINE;

  for(i; i < len; i++){
    if(!isdigit(line[i])){
      fprintf(stderr, "File must contain numbers 1-9 only\n");
      exit(-1);
    }
  }
}
Colour_t getColourRange(Board_t *board_ptr){
  /* need to get highest colour value to set as colourCount */
}
