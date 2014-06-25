/**
 * debug.c
 *
 * Rob Bowden
 * rob@cs.harvard.edu
 *
 * Intentionally buggy program that (in theory) never terminates.
 *
 * Meant to be debugged with GDB!
 */


#include <stdio.h>
#include <cs50.h>

void foo(int i)
{
    while (i != 0)
    {
        i = i - 3;
    }
    printf("%i\n", i);
}

int main(void)
{
    printf("Enter an integer: ");
    int i = GetInt();

    while (i > 10)
    {
        i--;
    }

    foo(i);
}
