/**
 * argv-4.c
 *
 * Rob Bowden
 * rob@cs.harvard.edu
 *
 * Prints command-line arguments, one character per line.
 *
 * Checks for '\0' instead of using strlen.
 */

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // print arguments
    for (int i = 0; i < argc; i++)
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            printf("%c\n", argv[i][j]);
        }
        printf("\n");
    }
}
