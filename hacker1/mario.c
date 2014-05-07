#include <cs50.h>
#include <stdio.h>

int main(void) {
  // Ask user the height of the half pyramids
  int height;
  int i;
  int j;
  int index_range;

  do
  {
    printf("Enter a height between 0 and 23: ");
    height = GetInt(); // GetInt ensures that an int was entered
  }
  while( height < 0 || height > 23);

  index_range  = height * 2 + 2;

  char pyramid[index_range];
  for(i = 0; i < index_range; ++i) {
    pyramid[i] = ' ';
  }

  
  for(j = 0; j < height; j++) {
    pyramid[height - 1 - j] = '#';
    pyramid[index_range - height + j] = '#';

    for(i = 0; i < index_range - height + j + 1; ++i) {
      printf("%c", pyramid[i]);
    }

    printf("\n");
  }

  return 0;
}

