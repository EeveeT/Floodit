#include "floodit.h"
#include <assert.h>


void test(void){
  Board_t testBoard;
  u_char row;
  u_char column;
  Colour_t testColour;
  Colour_t expectedSolutionColour;
  u_int i;
  u_int index;
  char testDigit;
  char testLine[5] = {'1', '2', '3', '4', '\n'};
  char testLineEmpty[1] = {'\0'};
  u_int testLineLen;
  u_char boardSize_testPtr = 0;
  Colour_t testArray[9] = {1,2,3,2,3,1,3,1,2};
  Colour_t expectedSolutionArray[9] = {'2','2','3','2','3','1','3','1','2'};

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
  testBoard.colourArray = NULL;

  setUpBoardMem(&testBoard);
  /* Now that memory for the board array has been set up, it should not be NULL*/
  assert(testBoard.colourArray != NULL);

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

  /* Test we are getting the correct index from each coordinate in the board */
  index = 0;
  for(row = 0; row < testBoard.length; row++){
    for(column = 0; column < testBoard.length; column++){
      assert(getIndexFromRowCol(&testBoard, row, column) == index);
      index += 1;
    }
  }
  /* We test setting and getting a colour for each cell in the board*/
  for(row = 0; row < testBoard.length; row++){
    for(column = 0; column < testBoard.length; column++){
      testColour = generateRandomColour(&testBoard);
      setColourAt(&testBoard, column, row, testColour);
      assert(getColourAt(&testBoard, column, row) == testColour);
    }
  }
  /* Use memset to set fillBoard function fills only valid colours
    we put in a value we know are or should be invalid, such as MAX_U_CHAR(255)
    into each cell in the board*/
  memset(testBoard.colourArray, MAX_U_CHAR, (testBoard.length * testBoard.length));
  fillBoard(&testBoard);
  for(row = 0; row < testBoard.length; row++){
    for(column = 0; column < testBoard.length; column++){
      testColour = getColourAt(&testBoard, row, column);
      assert(isValidColour(&testBoard, testColour));
    }
  }

  /*------------------------ Handle Arguments Functions--------------------- */

  /*Test that if the defult board is run, we get the default length and colours*/
  setUpDefaultBoard(&testBoard);
  assert(testBoard.length == DEFAULT_BOARD_SIZE);
  assert(testBoard.colourCount == DEFAULT_NUM_COLOURS);

  /*5 is just an arbitury number for a valid board length */
  setUpBoardWithLength(&testBoard, 5);
  assert(testBoard.length == 5);
  assert(testBoard.colourCount == DEFAULT_NUM_COLOURS);

  /* Here again, testing with a random arbitury valid number for length and colourCount*/
  setUpBoardWithLengthAndColours(&testBoard, 10, 7);
  assert(testBoard.length == 10);
  assert(testBoard.colourCount == 7);

  /*find a way of testing invalid (large) numbers. what happens if I set up 0?*/

  /*------------------------- Handle File Functions------------------------- */
  /* Declare an array but place nothing in it*/
  assert(stringIsEmpty(testLineEmpty) == true);
  assert(stringIsEmpty(testLine) == false);

  testLineLen = getLineLength(testLine);
  /* As we want to 'ignore' '\n', we expect 4*/
  assert(testLineLen == 4);

  testDigit = '5';
  testColour = digitToColour(testDigit);
  assert(testColour == 5);
  assert(isAllDigits(testLine, testLineLen));

 /*Handle Line Length sets the first line length and then ensures all lines after
  the first line in a board are the same length. 10 is an arbitury random number
  that we set as the length of the first line*/
  handleLineLength(&testBoard, &boardSize_testPtr, (u_int)10);
  assert(testBoard.length == 10);


  /* Reset row so ensure we know that it is. 1 is just an arbitury valid number*/
  row = 1;
  fillRow(&testBoard, testLine, testLineLen, row);
  for(column = 0; column < testLineLen; column++){
      testColour = digitToColour(testLine[column]);
      assert(getColourAt(&testBoard, row, column) == testColour);
  }

  /* Reset test colour to 0 so we know what it is*/
  testColour = 0;
  findColourCount(testLine, testLineLen, &testColour);
  /* The highest in our testline is a 4, so we expect colour count to be 4*/
  assert(testColour == 4);

  /*---------------------------- Game Functions--------------------------- */

  testBoard.length = DEFAULT_BOARD_SIZE;
  /* We reset board length and fill the board with one number, such as 5 and
     assert all numbers in the board are the same to check if we have won */
  memset(testBoard.colourArray, 5, (testBoard.length * testBoard.length));
  assert(checkIfWon(&testBoard) == true);


  testBoard.length = 3;
  testBoard.colourCount = 3;

  memcpy(testBoard.colourArray, testArray, (testBoard.length * testBoard.length * sizeof(Colour_t)));

  testColour = 2;
  index = 0;
  updateBoard(&testBoard, testColour);

  for(row = 0; row < testBoard.length; row++){
    for(column = 0; column < testBoard.length; column++){
      /* Extract colour from expected solution */
      index = getIndexFromRowCol(&testBoard, row, column);
      expectedSolutionColour = digitToColour(expectedSolutionArray[index]);
      /* Extract colour from actual output */
      testColour = getColourAt(&testBoard, row, column);
      assert(expectedSolutionColour == testColour);
    }
  }

/*------------------------------- End of Tests------------------------------- */

  /* Difficult to test that the pointer has been freed. We need to cleanUpBoard
     now we have finished with it though */
  cleanUpBoard(&testBoard);

  printf("Tests successfully passed\n");
}
