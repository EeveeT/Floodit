#include "floodit.h"

void handleFile(Board_t *board_ptr, FILE *file){
  /* We add one to the line length to account for null byte at the end*/
  char line[MAX_LINE_LEN + 1];
  u_char boardSize = 0;
  u_int lineLength;
  u_char rowCount = 0;
  Colour_t maxColour = 0;

  while(fgets(line, MAX_LINE_LEN + 1, file) != NULL && !stringIsEmpty(line)){
    lineLength = getLineLength(line);
    handleLineLength(board_ptr, &boardSize, lineLength);
    assertAllDigits(line, lineLength);
    fillRow(board_ptr, line, lineLength, rowCount);
    findMaxColour(line, lineLength, &maxColour);
    rowCount += 1;
  }
  if(rowCount != boardSize){
    fprintf(stderr, "Board must be a square\n");
    exit(-1);
  }
  board_ptr->colourCount = maxColour;
  printBoard(board_ptr);
}

u_int getLineLength(char line[]){

  u_int i;

  for(i = 0; line[i] != '\n' && i < MAX_BOARD_SIZE && line[i] != '\0'; i++) {}

  return i;

}

void assertAllDigits(char line[], u_int lineLength){
  u_int i;
  for(i = 0; i < lineLength; i++){
    if(!isdigit(line[i])){
      fprintf(stderr, "Board can only contain numbers 1-9\n");
      exit(-1);
    }
  }
}

void handleLineLength(Board_t *board_ptr, u_char *boardSize_ptr, u_int lineLength){
  if(*boardSize_ptr == 0){
    printf("---------------\n");
    *boardSize_ptr = lineLength;
    /*Set up board in the first line*/
    board_ptr->length = *boardSize_ptr;
    setUpBoardMem(board_ptr);
  }
  else if(*boardSize_ptr != lineLength){
    fprintf(stderr, "Incorrect line length\n");
    exit(-1);
  }
}

void fillRow(Board_t *board_ptr, char line[], u_int lineLength, u_char row){

  u_char col;
  Colour_t colour = 0;

  for(col = 0; col < lineLength; col++){
    colour = digitToColour(line[col]);
    setColourAt(board_ptr, col, row, colour);
  }
}

Colour_t digitToColour(char digit){

  return (Colour_t)(digit - '0');
}

void findMaxColour(char line[], u_int lineLength, Colour_t *maxColour){

  u_int i;
  Colour_t colour;

  for(i = 0; i < lineLength; i++){
    colour = digitToColour(line[i]);
    if(colour > *maxColour){
      *maxColour = colour;
    }
  }
}

bool stringIsEmpty(char string[]){
  return string[0] == '\0';
}
