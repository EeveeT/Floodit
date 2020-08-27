#include "floodit.h"

/* COL ROW NEEDS TO BE REVERSED */

int main (int argc, char *argv[]){

/*  This is the real board we always want to use, hence why it is in main,
    and this is why we always have to send a pointer to other functions to
    THIS board here in main
*/
  Board_t board;
  int turnCounter = 0;
  Colour_t fillNumber = 0;
  //board.length = DEFAULT_BOARD_SIZE;
  handleArguements(argc, argv, &board);
  /*The & enables the function to access the address in memory
    to where board is stored */
  /*if(!setUpBoardMem(&board, board.length)){
    fprintf(stderr, "This should never have happened\n");
  }*/
  while(!checkIfWon(&board)){
    turnCounter += 1;
    fillNumber = captureInputTurn(&board, turnCounter);
    printf("User input is: %u \n", fillNumber);
    updateBoard(&board, fillNumber);
    printBoard(&board);
  }



/*
  - Populate from text FILE
  - Populate from rand() depending on user input
      - check user input strlen == 1, isdigit and is between 1-9
  - Need to go into an infinite loop (while(1))
    or while(gameNotFinished)
  - Print to user an instruction for each "go"
  - Need to scanf their input
  - Check inpute is valid
      depening on DEFAULT_NUM_COLOURS || what the user specified


  - ~actionTurn~ **IGNORE (for now)**
      - save current value of top left corner
        - convert top left corner to user's specified input for that "go"
        - check neighbour cells if the value in them is the same
        - check neighbour cells of the neighbour cells


  -
*/

  /*When user quits or wins, need to cleanUpBoard() */
  cleanUpBoard(&board);

  return 0;
}
/*
  Whenever we see Board_t *board_ptr, think of it like a "tunnel" to
  the orignal board up in main
*/
void handleArguements(int argc, char* argv[], Board_t *board_ptr){

  FILE *file;
  /* We set array to NULL to be certain the malloc operation was a success */
  board_ptr->array2d = NULL;

  switch (argc){
    case 1:
          handleFirstArgument(board_ptr);
      break;
    case 2:
      /* boardSize 1-9  incomplete*/
      printf("Trying to open file %s\n",argv[1]);
        file = fopen(argv[1], "r");
      //  printf("File = %p \n", file);
        /* To check if argc == 2 is either a file or an int, we try to
          open a file by default to check if there is a file or not*/
        if(file == NULL){
          /* If we get to here, we now need to check if argv[1] is a single int */
          handleSecondArgumentLength(argv, board_ptr);
          board_ptr->colourCount = DEFAULT_NUM_COLOURS;
          printf("board has been made\n");
          fillBoard(board_ptr);
          printf("filled board successfully \n");

        }
        else{
              handleFileArgument(board_ptr, file);
          /*  fillBoardFromTxtFile(board_ptr, file);*/
            /* Line below is now correct, just used to void a seg fault for now*/
            fclose(file);
        }

      break;
    case 3:
      /*board size and number of colours determiend by user*/
      /*
        - As with case two, get the user input for argv[1][0] and argv [2][0]
        - Check if the inputs from the user are valid and the set the board up!
       */
        handleThirdArgumentLength(argv, board_ptr);
        fillBoard(board_ptr);


      break;
    default:
      /* else error */
      fprintf(stderr, "something went wrong\n");
  }
  /* Final last resort error check that should not happen */
  if(board_ptr->array2d == NULL){
    fprintf(stderr, "Failed to setup the board\n");
    exit(-1);
  }
}
 /*If the board has not been malloced, will crash.
  - check if array == NULL
  - check len > 1
  */

void printBoard(Board_t *board_ptr){

  unsigned char c, r = 0;
  unsigned int index;
  unsigned char len = board_ptr->length;

  printf("Board length: %d\n", len);

  for(r = 0; r < len; r++){
    for(c = 0; c < len; c++){
      index = getIndexFromColRow(board_ptr, c, r);
      printf("%d", board_ptr->array2d[index]);
    }
    printf("\n");
  }
}

void handleFirstArgument(Board_t *board_ptr){
  board_ptr->length = DEFAULT_BOARD_SIZE;
  board_ptr->colourCount = DEFAULT_NUM_COLOURS;

  setUpBoardMem(board_ptr);
  fillBoard(board_ptr);
}

void handleSecondArgumentLength(char* argv[], Board_t *board_ptr){

  int length;

  /*Checks that the input paramater is valid by seeing if it is a single
    character or number*/
  printf("%s\n", argv[1] );
  /*If the string length of argv[1] is more than 2 characters, we have a number
    above 100 or something of three or more charaters*/
  if(strlen(argv[1]) > 2){
    fprintf(stderr, "Incorrect argument, try to use a number between 2-20.\n");
    exit(-1);
  }
  else{
    /*Checks to see if both argv[1][0] and argv[1][1] are numberic types
      (Both indecies 0 and 1 for the first argument, i.e.,
    ./floodit 14) Both the 1 and 4 at position argv[1] are checked.
     */
     /* - The first check is to check the first digit is one character long and
          that that character is a digit.
        - The second check is if argv[1] is more than one character, and therefore
          is two (we have already checked it is not more than two), both the
          characters are digits so '3a' is not valid but '39' is at this point.
          We will then go on to check the number is between 2 and 20
      */
    if(isdigit(argv[1][0]) && strlen(argv[1]) == 1
    || isdigit(argv[1][0]) && isdigit(argv[1][1])){
      printf("Argument given is: %c%c\n", argv[1][0], argv[1][1]);
      /*
        - We first convert the string passed down from argv[1]
          to an interger using atoi(), see here for more details:
          https://www.educative.io/edpresso/how-to-convert-a-string-to-an-integer-in-c
          Then we type caste it to an unsigned char because length in Board_t
          is an unsigned char type.
      */
      length = atoi(argv[1]);
      board_ptr->length = (unsigned char)length;
      printf("length is: %d\n", length);

      checkBoardLenValid(board_ptr);

      printf("converted to an int %c\n",board_ptr->length);
    }
    else{
      fprintf(stderr, "Failed: You passed in a large number or\n"
      "letter which is an invalid text file, please try a number\n"
      "between 2-20 \n");
      exit(-1);
    }
  }
  /*If we get to here, all errors have passed so we can safely create the board*/
  setUpBoardMem(board_ptr);
}
/* this function is a mess, it has mixture or argv[2] and numColours but for
   some reason I must have both for the programme to work so something is wrong
   here
*/
void handleThirdArgumentLength(char* argv[], Board_t *board_ptr){

  unsigned char numColours;

  handleSecondArgumentLength(argv, board_ptr);
  numColours = atoi(argv[2]);
  printf("Argv[2] is: %s\n", argv[2]);
  printf("numColours is: %u\n", numColours);

  if(strlen(argv[2]) > 1){
    fprintf(stderr, "Input too long, must be a number between 1-9\n");
    exit(-1);
  }

  else{
        printf("checked argv[2] is a single character\n");
        /*THE LINE BELOW IS HORRIBLE,THIS NEEDS LOOKING AT BUT IT CURRENTLY WORKS
        statement below checks argv[2] is a digit that is not 0 */
      if(!isdigit(argv[2][0])){
        fprintf(stderr, "%s is not valid input\n",argv[2]);
        exit(-1);
      }
      if(numColours == 0){
        fprintf(stderr, "%d is an invalid input, numbers must be between 1-9\n",numColours);
        exit(-1);
      }
      /*By this point, argv[2] (now numColours) must be a number betwwen 1-9 */
      board_ptr->colourCount = numColours;
    }
}

void checkBoardLenValid(Board_t *board_ptr){

  if(board_ptr->length < MIN_BOARD_SIZE){
    fprintf(stderr, "Board size too small, must be between 2-20.\n");
    exit(-1);
  }
  if(board_ptr->length >  MAX_BOARD_SIZE){
    fprintf(stderr, "Board size too big, must be between 2-20\n");
    exit(-1);
  }

}
/*
void handleThirdArgumentColours(int argv, char* argv[], Board_t *board_ptr){
  if(strlen(argv[2] != 1)){
    fprintf(stderr, "Incorrect input, try a number between 1-6");
  }
}
*/
/* (as of Friday 14th August):
  - Firstly we get the total number of characters in the board by looking
    ahead to the end of the board the calculating the difference between
    position 0 and the end of the file.
  - Then, we rewind back to the beginning of the file in order to be able to
    read from it from the beginnig
  - Next, we check that the number of characters in the board is between the
    maximum and minimum allowed.
  - After this, we dynamically allocate the memory for the characters in the
    board
  - Then, we read the entire board as it is easier to work with an array
    than a whole text file.

*/

int readTxtFileToArray(Board_t *board_ptr, FILE *file){

  long int num_char_length;
  unsigned char *charArray;
  int bytesRead = 0;
  int i = 0;
  int c;
  int r;
  int columnLen = 0;
  int rowLen = 0;
  unsigned char value;
  int j;
  unsigned int index;
  Colour_t maxNumColour = 0;
/*
  Working form this website:
  https://www.tutorialspoint.com/c_standard_library/c_function_ftell.htm

  /* We retrieve the length of the file by returning where the file pointer is
    beginning from positon 0 to the EOF using fseek()
    Working form this website:
    https://www.tutorialspoint.com/c_standard_library/c_function_ftell.htm*/
  fseek(file, 0, SEEK_END);
  num_char_length = ftell(file);

  /*
    Rewind takes us back to position 0 of the file (see website)
    http://www.cplusplus.com/reference/cstdio/rewind/
    We only peeked ahead to the end of the file to get the length
    but need to rewind to the beginning so that when we read the file,
    we are reading from the beginning as expected.
   */
  rewind(file);

  printf("Length of text file is: %ld\n", num_char_length);
  if(num_char_length > MAX_CHAR_LEN){
    fprintf(stderr, "Board in the text file too large\n");
    fprintf(stderr, "Max board size is 20 x 20 characters + 20 new lines\n");
    fclose(file);
    exit(-1);
  }
  if(num_char_length < MIN_CHAR_LEN){
    fprintf(stderr, "Board size in text file too small\n");
    fprintf(stderr, "Minumum board size is 2 x 2 + 2 new lines\n");
    fclose(file);
    exit(-1);
  }
  /*Reserve enough memory to hold the text file */
  charArray = (unsigned char*) malloc(sizeof(unsigned char)*num_char_length);

  /*
    As opposed to char by char, fread() reads through the entire board in
    one go, which we do to check that we have a valid sized board contents.
    https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
    It is easier to do this working from memory than directly from the file.
  */
  bytesRead = fread(charArray, sizeof(unsigned char), num_char_length, file);
  /*The below lets us know if the file has been read properly */
  if(bytesRead != num_char_length){
    fprintf(stderr, "Failed to read text file\n");
    fclose(file);
    exit(-1);
  }
  /*These loops are to check that the contents of the text file are 'valid' which
  in our case means they are numbers or '\n' or '\0' and that the numbers are
  between 1-9. */
  c = 0;
  r = 0;
  for(i = 0; i < num_char_length; i++){
    if(!isdigit(charArray[i]) && charArray[i] != '\n' && charArray[i] != '\0'){
      fprintf(stderr, "File must contain numbers 1-9 only\n");
      exit(-1);
    }
    if(charArray[i] != '\n' && charArray[i]!= '\0' && charArray[i] != LF_CHAR && charArray[i] != '\r'){
      /*Value will now be the actual value of the number character and not the
        ASCII value of that character */
      value = charArray[i] - '0';
      c++;

      if(value < 1 || value > 9){
        fprintf(stderr, "Numbers in file must be between 1-9\n");
        exit(-1);
      }
    }
    /*
     Once we get to here, we have found a '\n' character so need to go down
     to next row and set the column back to the start.
      - If we read through our array in the file, we can find the length
      of the board by counting the characters up to the first '\n' we find.
    */


    else{
      if(c > columnLen){
        columnLen = c;
      }
      c = 0;
      r++;
    }

  //  printf("Column is: %d \nRow is: %d\n", c, r );
  }
  /*To create the 2D Array from the Board_t structure
    Need to check length is valid before making the board.
   */

   /*count how many '\n' there are and compare to length we found */
   if(columnLen != r){
     fprintf(stderr, " Board is not a square, rows and columns must be the \n"
                     "same length. There must be a newline on last row of numbers\n");
    exit(-1);
    }
    else{
      columnLen;
      rowLen = r;
      /*Pointers are permanent so length is saved. It also doesn't matter now
        if we set to row or coulumn length as we know they are the same*/
      board_ptr->length = rowLen;
    }

    setUpBoardMem(board_ptr);

    c = 0;
    r = 0;
    //printf("Entering j for loop...\n" );
    for(j = 0; j < num_char_length; j++){
      if(!isdigit(charArray[j]) && charArray[j] != '\n' && charArray[j] != '\0'){
        fprintf(stderr, "File must contain numbers 1-9 only\n");
        exit(-1);
      }
    //  printf("checking text input is valid...\n");
      if(charArray[j] != '\n' && charArray[j]!= '\0' && charArray[j] != LF_CHAR && charArray[j] != '\r'){
        /*Value will now be the actual value of the number character and not the
          ASCII value of that character */
        value = charArray[j] - '0';
      //  printf("value is: %d\n", value);
        /*
          To find the highest colour/number value, and therefore how
          many different 'colours' there are, we can use the conditional
          operator to get the highest number in the array.
          https://www.geeksforgeeks.org/conditional-or-ternary-operator-in-c-c/
        */
        maxNumColour = maxNumColour > value ? maxNumColour : value;
        printf("max number of colours is: %u\n", maxNumColour );

        if(value < 1 || value > 9){
          fprintf(stderr, "Numbers in file must be between 1-9\n");
          exit(-1);
        }
        else{
          index = getIndexFromColRow(board_ptr, (unsigned char)c, (unsigned char) r);
          printf("Saving value(%d) into array..\n", value);
          /*Puts all the values into the board from the file */
          board_ptr->array2d[index] = value;
          c++;

        }
      }
      else{
        if(c > columnLen){
          columnLen = c;
        }
        c = 0;
        r++;
      }
    }
    board_ptr->colourCount = maxNumColour;
    /*Text file has been transferred into a chunk of memory and now we
      are done with the charArray we used (as its easier to work with an array
      that directly with a text file), we need to free the memory we were using*/
    free(charArray);
    return 0;
  }

Colour_t captureInputTurn(Board_t *board_ptr, int turnCounter){

    Colour_t turnColour;

    printf("Turn %d : What number ? ", turnCounter);
    scanf("%u", &turnColour);
    printf("turn input is: %u\n", turnColour );
    printf("board max colour is: %u\n", board_ptr->colourCount);
    if(turnColour < MIN_NUM_COLOURS || turnColour > board_ptr->colourCount){
      fprintf(stderr, "Invalid number: must be between 1-%u\n", board_ptr->colourCount);
      /* Instead of exiting the game and ending it for the user, we simply return
          so they can keep playing*/

    }
    return turnColour;
}


  /* once checked length, then go through loop again but instead of
     setting board length, we need to store each char into the board.
     when storing chars into the board, need to check they are digitss between
     1-9.
  */

/* todo:
- load in text file, save to array
- find highest number in array
- allocate memeory for board contents
*/
