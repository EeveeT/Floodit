/* Each 'colour' is represented by a number 1-9. The maximum number of 'colours'
   is 9. I will refer to these numbers 1-9 as 'colours'.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/* If argc == 1, then we set the board to it the default size of 14 x 14 with
   6'colours' as per the handout specification. If argc == 1, then the count of
   arguments submitted by the user is just the program and in this instance the
   user has not specified board size or number of different 'colours'
*/
#define DEFAULT_BOARD_SIZE 14
#define DEFAULT_NUM_COLOURS 6
#define MAX_BOARD_SIZE 20

int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

void print2dArray(int maxRow, int maxCol);
void ZeroArray(int maxRow, int maxCol);
/* argc -> count, argv[] -> vector */
int main(int argc, char **argv){

ZeroArray(MAX_BOARD_SIZE, MAX_BOARD_SIZE);


/* check argument recievedand print back

check valid input */
  FILE *file;
  char colour;


  file = fopen("board.txt", "r");
  if(file){

    int c = 0;
    int r = 0;

    while((colour = fgetc(file)) != EOF){
      if(isdigit(colour)){
        if(c < MAX_BOARD_SIZE){
          if(r < MAX_BOARD_SIZE){
            board[r][c] = colour - '0';
            c++;
          }
          else{
            printf("Warning, too many rows\n");
          }
        }

        else{
          printf("Warning, board exceeded border\n");
        }
    }
      else if(colour == '\n' || colour =='\r'){
        c = 0;
        r++;
      }
    /*  printf("%c", colour);*/
    }
    printf("\n");
  }
  fclose(file);

  print2dArray(3, 3);

  /*int board[][];


  if(argc == 1){
    board [DEFAULT_BOARD_SIZE][DEFAULT_BOARD_SIZE];
    fillBoard(); will create a function to fill the board

  }
*/
  return 0;

}

void print2dArray(int maxRow, int maxCol){

  int c, r = 0;

  printf("Printing board...\n");

  for(r = 0; r < maxRow; r++){
    for(c = 0; c < maxCol; c++){
      printf("%d", board[r][c]);
    }
    printf("\n");
  }
}

void ZeroArray(int maxRow, int maxCol){

  int c, r = 0;

  for(r = 0; r < maxRow; r++){
    for(c = 0; c < maxCol; c++){
      board[r][c] = 0;
    }
  }
}

/*int fillBoard(int)*/
