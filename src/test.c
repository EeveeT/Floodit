#include "floodit.h"
#include <assert.h>


void test(void){
  Board_t testBoard;
  u_char column;
  u_char row;
  Colour_t testColour;
  int i;
  /*----------------------------- Board Functions---------------------------- */
  /* Test for valid board length values*/
  for(testBoard.length = MIN_BOARD_SIZE; testBoard.length <= MAX_BOARD_SIZE; testBoard.length++){
    assertBoardLenValid(&testBoard);
  }
  /* Test all colours up to maximum colour of 9 are valid. If this test fails
     the program will quit, thus test fail.*/
  for(testBoard.colourCount = MIN_NUM_COLOURS; testBoard.colourCount <= MAX_NUM_COLOURS; testBoard.colourCount ++){
    assertColourCountValid(&testBoard);
  }
  /*Set variables to values that we can test */
  testBoard.length = DEFAULT_BOARD_SIZE;
  testBoard.colourCount = MAX_NUM_COLOURS;
  testBoard.array2d = NULL;

  setUpBoardMem(&testBoard);
  /* Now that memory for the board array has been set up, it should not be NULL*/
  assert(testBoard.array2d != NULL);

  for(testColour = MIN_NUM_COLOURS; testColour <= MAX_NUM_COLOURS; testColour++){
    /*Each of these colours up to and including the max colour should be valid*/
    assert(isValidColour(&testBoard, testColour));
  }
  /*Anything less than the minimum number of colours is not a valid colour*/
  for(testColour = 0; testColour < MIN_NUM_COLOURS; testColour++){
    assert(!isValidColour(&testBoard, testColour));
  }
  for(testColour = MAX_NUM_COLOURS + 1; testColour < MAX_U_CHAR; testColour++){
    assert(!isValidColour(&testBoard, testColour));
  }

  /* 100 is just an arbitury large number. We do 100 tests on generating random
     colours and each one should be valid */
  for(i = 0; i < 100; i++){
    testColour = generateRandomColour(&testBoard);
    assert(isValidColour(&testBoard, testColour));
  }

  /* We test setting and getting a colour for each cell in the board*/
  for(row = 0; row < testBoard.length; row++){
    for(column = 0; column < testBoard.length; column++){
      testColour = generateRandomColour(&testBoard);
      setColourAt(&testBoard, column, row, testColour);
      assert(getColourAt(&testBoard, column, row) == testColour);
    }
  }





















  /* Difficult to test that the pointer has been freed */
  cleanUpBoard(&testBoard);

  printf("Tests successfully passed\n");
}
