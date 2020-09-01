#include "floodit.h"

Result_t handleFile(Board_t *board_ptr, FILE *file){
  /* We add one to the line length to account for null byte at the end*/
  char line[MAX_LINE_LEN + 1];
  u_char boardSize = 0;
  u_int lineLength;
  u_char rowCount = 0;
  Colour_t colourCount = 0;

  /*fgets gets one line from the file (up to '\n' or '\0') so we loop through
    the file to get each line. We do not want to read in an empty line*/
  while(fgets(line, MAX_LINE_LEN + 1, file) != NULL && !stringIsEmpty(line)){
    lineLength = getLineLength(line);
    handleLineLength(board_ptr, &boardSize, lineLength);
    if(isAllDigits(line, lineLength) == false){
      logError("Board can only contain numbers 1-9\n");
      return failed;
    }
    fillRow(board_ptr, line, lineLength, rowCount);
    findColourCount(line, lineLength, &colourCount);
    rowCount += 1;
  }
  if(rowCount != boardSize){
    logError("Board must be a square\n");
    return failed;
  }
  board_ptr->colourCount = colourCount;

  return succeeded;
}

u_int getLineLength(char line[]){

  u_int i;

  /*Either the end of a line is a new line OR we don't want to read in anymore
    elements in a line beyond the maximum length of the board*/
  for(i = 0; line[i] != '\n' && i < MAX_BOARD_SIZE && line[i] != '\0'; i++) {}
  /*We don't need to do anything in the loop other than go through it to get i*/
  return i;
}

bool isAllDigits(char line[], u_int lineLength){
  u_int i;
  for(i = 0; i < lineLength; i++){
    if(!isdigit(line[i])){
      return false;
    }
  }
  return true;
}

void handleLineLength(Board_t *board_ptr,
  u_char *boardSize_ptr,
  u_int lineLength){
  /*boardSize_ptr is the first line. When it is 0, we know it has not been set yet*/
  if(*boardSize_ptr == 0){
    *boardSize_ptr = lineLength;
    /*Set up board in the first line*/
    board_ptr->length = *boardSize_ptr;
    setUpBoardMem(board_ptr);
  }
  /*For all other lines after the first line in the board, we check that the
    current length is the same as the first line*/
  else if(*boardSize_ptr != lineLength){
    logError("Incorrect line length\n");
    exit(-1);
  }
}

void fillRow(Board_t *board_ptr, char line[], u_int lineLength, u_char row){

  u_char col;
  Colour_t colour = 0;

  for(col = 0; col < lineLength; col++){
    colour = digitToColour(line[col]);
    setColourAt(board_ptr, row, col, colour);
  }
}

Colour_t digitToColour(char digit){

    return (Colour_t)digit - '0';

}

void findColourCount(char line[], u_int lineLength, Colour_t *colourCount){

  u_int i;
  Colour_t colour;

  for(i = 0; i < lineLength; i++){
    colour = digitToColour(line[i]);
    if(colour > *colourCount){
      *colourCount = colour;
    }
  }
}

bool stringIsEmpty(char string[]){
  /* If it first item in a string is '\0', then it is empty*/
  return string[0] == '\0';
}
