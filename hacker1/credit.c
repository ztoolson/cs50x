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
  int res = num / divisor;
  return res;
}

bool IsValidCreditCard(long long cc_number) {

  bool is_valid_card_number = false;

  // Determine the length of the credit card
  int cc_num_digits = log10(cc_number) + 1;

  // Set up arrays to use for storing each digit
  int product_length = cc_num_digits / 2;
  int other_length = cc_num_digits % 2 == 0 ? product_length : product_length + 1;

  int product_of_digits[product_length]; 
  int other_digits[other_length];

  int count = 0;
  long long temp_user_input = cc_number;
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
  int i;
  int sum_of_products_digits = 0;
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
  int sum_other = 0;
  int j;
  for(j = 0; j < other_length; ++j) {
    sum_other += other_digits[j];
  }
  
  // Check if card has valid number
  int total_sum = sum_other + sum_of_products_digits;
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


  // Get the number as a float from user
  printf("Enter your credit card number:\n");
  user_input = GetLongLong();
  int cc_num_digits = log10(user_input) + 1;

  // *** Determine if it is valid credit card
  bool is_valid_card_number =IsValidCreditCard(user_input);
  
  // Multiply every other digit by 2, starting with the number's second-to-last digit
  // And store result in a list of integers
  

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
