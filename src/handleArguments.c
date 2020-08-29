#include "floodit.h"

void handleArguments(int argc, char* argv[], Board_t *board_ptr){

  switch (argc){
    case 1:
        setUpDefaultBoard(board_ptr);
      break;
    case 2:
        handleSingleArgument(board_ptr, argv[1]);
      break;
    case 3:
        handleTwoArguments(board_ptr, argv[1], argv[2]);
      break;
    default:
      fprintf(stderr, "Invalid usage\n");
      exit(-1);
  }

}

void setUpDefaultBoard(Board_t *board_ptr){
  board_ptr->length = DEFAULT_BOARD_SIZE;
  board_ptr->colourCount = DEFAULT_NUM_COLOURS;

  setUpBoardMem(board_ptr);
  fillBoard(board_ptr);
}

void setUpBoardWithLength(Board_t *board_ptr, u_char inputBoardLength){
  board_ptr->length = inputBoardLength;
  board_ptr->colourCount = DEFAULT_NUM_COLOURS;

  assertBoardLenValid(board_ptr);
  setUpBoardMem(board_ptr);
  fillBoard(board_ptr);
}

void setUpBoardWithLengthAndColours(Board_t *board_ptr,
  u_char inputBoardLength,
  Colour_t colourCount){

  board_ptr->length = inputBoardLength;
  board_ptr->colourCount = colourCount;

  assertBoardLenValid(board_ptr);
  assertColourCountValid(board_ptr);
  setUpBoardMem(board_ptr);
  fillBoard(board_ptr);
}

void handleSingleArgument(Board_t *board_ptr, char *arg){

  u_char boardSize;
  int inputCount;
  FILE *file;

  inputCount = sscanf(arg, "%hhu", &boardSize);
  if(inputCount == INPUT_COUNT){
    setUpBoardWithLength(board_ptr, boardSize);
  }
  else{
    file = fopen(arg, "r");
    if(file == NULL){
      fprintf(stderr, "Error opening file %s. \n", arg);
      exit(-1);
    }
    handleFile(board_ptr, file);
    fclose(file);
  }
}

void handleTwoArguments(Board_t *board_ptr, char *boardLenStr, char *maxColourStr){

  int inputCount;
  Colour_t maxColour;
  u_char boardSize;

  inputCount = sscanf(boardLenStr, "%hhu", &boardSize);
  if(inputCount != INPUT_COUNT){
    fprintf(stderr, "Please enter a number for board size.\n");
    exit(-1);
  }
  inputCount = sscanf(maxColourStr, "%hhu", &maxColour);
  if(inputCount != INPUT_COUNT){
    fprintf(stderr, "Please enter a number of colours.\n");
    exit(-1);
  }

  setUpBoardWithLengthAndColours(board_ptr, boardSize, maxColour);

}
