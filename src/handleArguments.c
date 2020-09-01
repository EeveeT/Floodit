#include "floodit.h"

Result_t handleArguments(int argc, char* argv[], Board_t *board_ptr){

  switch (argc){
    case 1:
        return setUpDefaultBoard(board_ptr);
    case 2:
        return handleSingleArgument(board_ptr, argv[1]);
    case 3:
        return handleTwoArguments(board_ptr, argv[1], argv[2]);
    default:
      fprintf(stderr, "Invalid usage\n");
      return failed;
  }

}

Result_t setUpDefaultBoard(Board_t *board_ptr){
  board_ptr->length = DEFAULT_BOARD_SIZE;
  board_ptr->colourCount = DEFAULT_NUM_COLOURS;

  setUpBoardMem(board_ptr);
  fillBoard(board_ptr);

  return succeeded;
}

Result_t setUpBoardWithLength(Board_t *board_ptr, u_char inputBoardLength){
  board_ptr->length = inputBoardLength;
  board_ptr->colourCount = DEFAULT_NUM_COLOURS;

  assertBoardLenValid(board_ptr);
  setUpBoardMem(board_ptr);
  fillBoard(board_ptr);

  return succeeded;
}

Result_t setUpBoardWithLengthAndColours(Board_t *board_ptr,
  u_char inputBoardLength,
  Colour_t colourCount){

  board_ptr->length = inputBoardLength;
  board_ptr->colourCount = colourCount;

  assertBoardLenValid(board_ptr);
  assertColourCountValid(board_ptr);
  setUpBoardMem(board_ptr);
  fillBoard(board_ptr);

  return succeeded;
}

Result_t handleSingleArgument(Board_t *board_ptr, char *arg){

  u_char boardSize;
  FILE *file;
  Result_t handledFile;

  if(readInUCharFromString(arg, &boardSize) == succeeded){
    return setUpBoardWithLength(board_ptr, boardSize);
  }

  file = fopen(arg, "r");
  if(file == NULL){
    fprintf(stderr, "Error opening file %s. \n", arg);
    return failed;
  }
  handledFile = handleFile(board_ptr, file);
  fclose(file);
  return handledFile;

}

Result_t handleTwoArguments(Board_t *board_ptr,
  char *boardLenStr, char *colourCountStr){

  Colour_t colourCount;
  u_char boardSize;

  if(readInUCharFromString(boardLenStr, &boardSize) == failed){
    fprintf(stderr, "Please enter a number for board size\n");
    return failed;
  }

  if(readInUCharFromString(colourCountStr, &colourCount) == failed){
    fprintf(stderr, "Please enter a number of colours\n");
    return failed;
  }

  return setUpBoardWithLengthAndColours(board_ptr, boardSize, colourCount);

}

Result_t readInUCharFromString(char *inputStr, u_char *inputUChar_ptr){

  int inputCount = 0;
  u_int userInput = 0;

  inputCount = sscanf(inputStr, "%u", &userInput);

  if(userInput > MAX_U_CHAR){
    /* Way I deal with numbers over 256 is to saturate them as 255 so that
       in captureInputTurn(), I can give a more precise error statement to
       the user
    */
    userInput = MAX_U_CHAR;
  }

  if(inputCount == 1){
    *inputUChar_ptr = userInput;
    return succeeded;
  }
  else{
    return failed;
  }
}
