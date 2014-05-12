/*
  Author: Zach Toolson
  Date: 5/12/2014
*/
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char * argv[]) {
  // Program accepts one command-line argument which is a non-negative number.
  // Will return 1 if this is not the case

  if (argc != 2) {
    printf("Check command line arguements and try again\n");
    printf("Expecting './caesar <key>' where key is a positive integer");
    return 1;
  }

  // convert command line to int, this is the offset for caesar cipher
  int k = atoi(argv[1]);
  if (k <= 0) {
    return 1;
  }

  // Prompt user for a string of plain text
  string user_text;
  do {
//    printf("Enter what you would like to be ciphered:\n");
    user_text = GetString();
  }
  while( strcmp("", user_text) == 0 );

  // Calculate caesar cipher of that string using k from command line
  for (int i = 0, n = strlen(user_text); i < n; ++i) {
    char sub_char;
    bool conver_char = false; // do not convert punctuation
    if (user_text[i] >= 97 && user_text[i] <= 122) {
      conver_char = true;
      sub_char = 'a';
    }
    else if ( user_text[i] >= 65 && user_text[i] <= 90) {
      conver_char = true;
      sub_char = 'A';
    }

    if (conver_char){
      int temp = user_text[i] - sub_char; // Get number representation
      temp = (temp + k) % 26; // Apply cipher
      user_text[i] = temp + sub_char; // convert back to ascii
    }
  }

  // Output cipher text to user
  printf("%s\n", user_text);
  
  return 0;
}
