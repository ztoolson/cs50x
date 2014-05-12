/*
  Author: Zach Toolson
  Date: May, 2014

  Gets user input for height of the mario like structure and prints it out.
  This version outputs two half pyramids.

  For example
  User Input: 4
  Output:
     #  #
    ##  ##
   ###  ###
  ####  ####

*/
#include <cs50.h>
#include <stdio.h>

int main(void) {
  int height, i, j, index_range;
  
  /* Get user input */
  do
  {
    printf("Enter a height between 0 and 23: ");
    height = GetInt(); // GetInt ensures that an int was entered
  }
  while( height < 0 || height > 23);
  
  /* Calculate how large of an array is needed to store the pyramid */
  index_range  = height * 2 + 2;

  /* Initialize and set all char to ' ' in the pyramid "string" */
  char pyramid[index_range];
  for(i = 0; i < index_range; ++i) {
    pyramid[i] = ' ';
  }

  /* Calculate which indices need to have a '#' in the */  
  for(j = 0; j < height; j++) {
    pyramid[height - 1 - j] = '#'; /* Set first half pyramid '#' location */
    pyramid[index_range - height + j] = '#'; /* Set second pyramid '#' location */
    
    /* Print out the level of the pyramid most recently updated */
    for(i = 0; i < index_range - height + j + 1; ++i) {
      printf("%c", pyramid[i]);
    }
  
    printf("\n");
  }

  return 0;
}

