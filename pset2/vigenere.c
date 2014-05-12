/*
  Author: Zach Toolson
  Date: 5/12/2014

  Applies vigenere cipher to the input with the key as a command line argument,
  and then prints out the ciphered text.

  Vignere cipher uses a keyword to encrpt the original text.
  Valid keys must only contain characters A-Z or a-z. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char * argv[]) {
  
  // Program accepts one command-line argument which is a string.
  // Will return 1 if this is not the case
  if (argc != 2) {
    printf("Check command line arguements and try again\n");
    printf("Expecting './caesar <key>' where key is a positive integer");
    return 1;
  }
  
  // Get the key string from the command line input
  string key = argv[1];

  // Check if it is a valid key and convert each letter to lowercase
  bool is_valid = true;
  for (int i = 0, n = strlen(key); i < n; ++i) {
    // Check if char is valid ascii char [A-Za-z]
    if (! ((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122))) {
      is_valid = false;
      break;
    }
    // Assuming valid string, convert to all lowercase
    key[i] = tolower(key[i]);
  }
  
  // Return if not a valid keyword
  if (!is_valid) {
    printf("Not a valid command line arguement. Must be only A-Z or a-z");
    return 1;
  }

  // Prompt user for a string of plain text
  string user_text;
  do {
//    printf("Enter what you would like to be ciphered:\n");
    user_text = GetString();
  }
  while( strcmp("", user_text) == 0 );

  // Calculate vigenere cipher of that string using the key from command line
  int count = 0; // count number of letters converted
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
    
    // If the character needs to be converted, perform cipher translation
    if (conver_char){
      // Calculate k number based on key
      char temp_char = key[count % strlen(key)];
      int key_num = temp_char - 'a';

      int text_num = user_text[i] - sub_char; // Get number representation of phrase char
      text_num = (text_num + key_num) % 26; // Apply cipher
      user_text[i] = text_num + sub_char; // convert back to ascii
      count++;
    }
  }

  // Output cipher text to user
  printf("%s\n", user_text);
  
  return 0;
}
