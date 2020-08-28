#include "floodit.h"

void handleArguments(int argc, char* argv[], Board_t *board_ptr){

  FILE *file;
  /* We set array to NULL to be certain the malloc operation was a success */
  board_ptr->array2d = NULL;

  switch (argc){
    case 1:
        setUpDefaultBoard(board_ptr);
      break;
    case 2:
      /* boardSize 1-9  incomplete*/
      printf("Trying to open file %s\n",argv[1]);
        file = fopen(argv[1], "r");
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
              handleFile(board_ptr, file);
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

void setUpDefaultBoard(Board_t *board_ptr){
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
    if((isdigit(argv[1][0]) && strlen(argv[1]) == 1)
    || (isdigit(argv[1][0]) && isdigit(argv[1][1]))){
      printf("Argument given is: %c%c\n", argv[1][0], argv[1][1]);
      /*
        - We first convert the string passed down from argv[1]
          to an interger using atoi(), see here for more details:
          https://www.educative.io/edpresso/how-to-convert-a-string-to-an-integer-in-c
          Then we type caste it to an u_char because length in Board_t
          is an u_char type.
      */
      length = atoi(argv[1]);
      board_ptr->length = (u_char)length;
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

  u_char numColours;

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
