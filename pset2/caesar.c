/*
  Author: Zach Toolson
  Date: 5/12/2014
*/
#include <stdio.h>
#include <cs50.h>

int main(int argc, char * argv[]) {
  // Program accepts one command-line argument which is a non-negative number.
  // Will return 1 if this is not the case

  if (argc != 2) {
    return 1;
  }

  int input = atoi(argv[1]); // convert command line to int
  if (input <= 0) {
    return 1;
  }
  
  for (int i = 0; i < argc; ++i) {
    printf("Argument %i is %s\n", i, argv[i]);
  }

  printf("\nThe converted argv[1] is: %i\n", input);
}
