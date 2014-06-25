/**
 * argv-3.c
 *
 * Rob Bowden
 * rob@cs.harvard.edu
 *
 * Prints command-line arguments, one character per line.
 *
 * Uses own version of strlen function.
 */

#include <cs50.h>
#include <stdio.h>

int my_strlen(string s)
{
    int length = 0;
    while(s[length] != '\0')
    {
        length++;
    }
    return length;
}

int main(int argc, string argv[])
{
    // print arguments
    for (int i = 0; i < argc; i++)
    {
        for (int j = 0, n = my_strlen(s); j < n; j++)
        {
            printf("%c\n", argv[i][j]);
        }
        printf("\n");
    }
}
