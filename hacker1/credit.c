/*
  Author: Zach Toolson
  Date: May, 2014

  credit.c gets a credit card number from the user in the form of a
  number, and then validates whether it is a valid American Express,
  Discover, or Visa card.
*/
#include <cs50.h>
#include <stdio.h>
#include <math.h>

/*
  Return the first N digits of the long long provided.

  Example: 
  GetFirstDigits(3, 458234569);
  >>> 458
*/
int GetFirstDigits(int n, long long num) {
  long long log10 = ( log(num)/log(10) ) + 1;
  long long divisor = pow(10, log10 - n);
  return num / divisor;
}

bool IsValidCreditCard(long long cc_number) {

  int total_sum, cc_num_digits, product_length, other_length, count, i, j, sum_of_products_digits, sum_other;
  long long temp_user_input;
  bool is_valid_card_number = false;

  // Determine the length of the credit card
  cc_num_digits = log10(cc_number) + 1;

  // Set up arrays to use for storing each digit
  product_length = cc_num_digits / 2;
  other_length = cc_num_digits % 2 == 0 ? product_length : product_length + 1;

  int product_of_digits[product_length]; 
  int other_digits[other_length];

  count = 0;
  temp_user_input = cc_number;

  /* Add each digit to proper array */
  do {
    int digit = temp_user_input % 10;

    if (count % 2 == 1) {
      product_of_digits[count / 2] = digit * 2; 
    }
    else {
      other_digits[count / 2] = digit;
    }

    ++count;
  }
  while (temp_user_input /= 10);
  
  // Add each digit of the products together
  sum_of_products_digits = 0;
  for(i = 0; i < product_length; ++i) {
    int n = product_of_digits[i];
    do {
      int digit = n % 10;
      sum_of_products_digits += digit;
    }
    while(n /= 10);
  }

  // Add the sum_of_product_digits to all the digits that weren't 
  // multiplied by 2
  sum_other = 0;
  for(j = 0; j < other_length; ++j) {
    sum_other += other_digits[j];
  }
  
  // Check if card has valid number
  total_sum = sum_other + sum_of_products_digits;
  is_valid_card_number = total_sum % 10 == 0 ? true : false;

  return is_valid_card_number;
}


/*
   Determine the validity of a credit card number and identify
   which major card company that card belongs to.
 */
int main(void) {
  // Set up variables
  string output = "INVALID";
  long long user_input;
  int cc_num_digits;
  bool is_valid_card_number;


  // Get the number as a float from user
  printf("Enter your credit card number:\n");
  user_input = GetLongLong();
  cc_num_digits = log10(user_input) + 1;

  // *** Determine if it is valid credit card
  is_valid_card_number =IsValidCreditCard(user_input);
  

  // *** If valid:  Check AMEX, DISCOVER, or VISA
  if(is_valid_card_number) {

    // AMEX has 15 digits and must start with 34 or 37
    int temp = GetFirstDigits(2, user_input);
    if( (34 == temp || 37 == temp) && (cc_num_digits == 15) ) {
      output = "AMEX";
    }

    // MASTERCARD uses 16 digits and must start with 51, 52, 53, 54, or 55
    if ( cc_num_digits == 16 && (51 == temp ||  52 == temp || 53 == temp || 54 == temp || 55 == temp) ) {
      output = "MASTERCARD";
    }

    // VISA uses 13 or 16 digits, and must start with a 4
    temp = GetFirstDigits(1, user_input);
    bool is_visa = (cc_num_digits == 13 || cc_num_digits == 16) && 4 == temp;
    if(is_visa) {
      output = "VISA";
    }
  }

  printf("%s\n", output);

  return 0;
}
