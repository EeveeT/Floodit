if(argc > 3){
  printf("You have entered too many arguments\n");
}

else if(argc == 1){
  print2dArray(DEFAULT_BOARD_SIZE,DEFAULT_BOARD_SIZE);
  /* fill defaul board */
}
else if(argc == 2){
  file = fopen(argv[1], "r");
  /* To check if argc == 2 is either a file or an int, we try to
    open a file by default to check if there is a file or not*/
  if(file == NULL){
    /* If we get to here, we now need to check if argv[1] is a single int */
    if(strlen(argv[1]) != 1){
      printf("Input number too long, not a valid .txt file \n \
              or not a number, please check again\n");
    }
    else{
      /*Checking the first char of argv[1] by indexing [0] */
      if(isdigit(argv[1][0])){
        /* initialise board with number stored in argv[1]*/
        printf("valid number input found\n");
      }
      else{
        /*If we get to here, not a number so an invalid argument */
      }
    }
  }
    else{
      /*Try to initialise the board from a text file */
    }
  }

  /*  else if {
      /*check if boardSize betwwen 1-9
      printf("%s\n", argv[1]);
      argv[1] = boardSize;
    }
    else if(argv[2])
       read in file
    */
