/*
  Author: Zach Toolson
  Date: May, 2014

  mario.c will prompt the user to enter a non negative number and then
  it will output a representation of the end blocks found in mario game.

  Example:
  User input: 4
  Output:
     ##
    ###
   ####
  #####
*/
#include <cs50.h>
#include <stdio.h>

int main(void)
{
  // Get User Input

  // Declare the Height input 
  int height;

  // Check to make sure int is valid. The height is not valid
  // if it is negative or is greater than 23
  //
  // Will keep prompting user for a valid integer until one is valid
  do
  {
    printf("Enter a height between 0 and 23: ");
    height = GetInt(); // GetInt ensures that an int was entered
  }
  while( height < 0 || height > 23);

  int length_of_row = height + 1;

  // Start printing out the right aligned pyramid
  // Print the total number of rows
  for (int col_num = 0; col_num < height; ++col_num)
  {
    // Print out each char in the row
    for(int row_char = 0; row_char < length_of_row; ++row_char)
    {
      if(row_char >= (length_of_row - 2 - col_num))
      {
        printf("#");
      }
      else
      {
        printf(" ");
      }

    }
    printf("\n");
  }
}
