/**
 * scanf-2.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Reads a string from the user into an array (dangerously).
 *
 * Demonstrates potential buffer overflow!
 */
       
#include <stdio.h>

int main(void)
{
    char buffer[16]; // Allocated 16 char array
    printf("String please: ");
    // If string.length > 15 then buffer overflow!
    scanf("%s", buffer);
    printf("Thanks for the %s!\n", buffer);
}
