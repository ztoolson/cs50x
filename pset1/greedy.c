/*
  Author: Zach Toolson
  Date: May, 2014

  This program gets a float from the user asking for an amount of money.
  greedy.c will calculate the minumum number of coins needed to achieve that
  amount entered using quarters, dimes, nickels, and pennies.
*/
#include <cs50.h>
#include <stdio.h>

int main()
{
  int num_quarters = 0;
  int num_dimes = 0;
  int num_nickels = 0;
  int num_pennies = 0;
  int total_coins = 0;

  // Promt the user for an amount of change
  float change_amount_requested;
  int change_amount;

  do
  {
    printf("O hai! How much change is owed? ");
    change_amount_requested = GetFloat(); // GetInt ensures that an int was entered
  }
  while( change_amount_requested < 0 );


  // Round number to 2 decimal places
  change_amount =  (int)(change_amount_requested * 100 ) ;

  // Always use the largest coin possible when calculating change owed
  num_quarters = change_amount / 25;
  change_amount = change_amount % 25;
  
  num_dimes = change_amount / 10;
  change_amount = change_amount % 10;

  num_nickels = change_amount / 5;
  change_amount = change_amount % 5;

  num_pennies = change_amount;
  
  total_coins = num_quarters + num_dimes + num_nickels + num_pennies;
  printf("%d\n", total_coins);

  return 0;
}
