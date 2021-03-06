/**
 * list-0.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates a linked list for numbers.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list-0.h"

// linked list
node* first = NULL;

// prototypes
void delete(void);
void insert(void);
void search(void);
void traverse(void);

int main(void)
{
    int c;
    do
    {
        // print instructions
        printf("\nMENU\n\n"
            "1 - delete\n"
            "2 - insert\n"
            "3 - search \n"
            "4 - traverse\n"
            "0 - quit\n\n");

        // get command
        printf("Command: ");
        c = GetInt();

        // try to execute command
        switch (c)
        {
            case 1: delete(); break;
            case 2: insert(); break;
            case 3: search(); break;
            case 4: traverse(); break;
        }
    }
    while (c != 0);

    // free list before quitting
    node* ptr = first;
    while (ptr != NULL)
    {
        node* predptr = ptr; // get current item to free
        ptr = ptr->next; // point to next item in the list
        free(predptr); // free current item
    }
}

/**
 * Tries to delete a number.
 */
void delete(void)
{
    // prompt user for number
    printf("Number to delete: ");
    int n = GetInt();

    // get list's first node
    node* ptr = first;

    // try to delete number from list
    node* predptr = NULL;
    while (ptr != NULL)
    {
        // check for number
        if (ptr->n == n)
        {
            // delete from head
            if (ptr == first)
            {
                first = ptr->next;
                free(ptr);
            }

            // delete from middle or tail
            else
            {
                predptr->next = ptr->next;
                free(ptr);
            }

            // all done
            break;
        }
        else
        {
            predptr = ptr;
            ptr = ptr->next;
        }
    }

    // traverse list
    traverse();
}

/**
 * Tries to insert a number into list.
 */
void insert(void)
{
    // try to instantiate node for number
    node* newptr = malloc(sizeof(node));
    if (newptr == NULL)
    {
        return;
    }

    // initialize node
    printf("Number to insert: ");
    newptr->n = GetInt();
    newptr->next = NULL;

    // check for empty list
    if (first == NULL)
    {
        first = newptr;
    }

    // else check if number belongs at list's head (IE new number is the lowest one being inserted)
    else if (newptr->n < first->n)
    {
        newptr->next = first; // new item will now point to original first
        first = newptr; // update first to the newptr
    }

    // else try to insert number in middle or tail
    else
    {
        node* predptr = first;
        while (true)
        {
            // avoid duplicates
            if (predptr->n == newptr->n)
            {
                free(newptr);
                break;
            }

            // check for insertion at tail (IE newptr is the largest number in the list)
            else if (predptr->next == NULL)
            {
                predptr->next = newptr;
                break;
            }

            // check for insertion in middle (IE insert between predptr and predptr->next)
            else if (predptr->next->n > newptr->n)
            {
                // (predptr->n) < (newptr->n) < (predptr->next->n)
                newptr->next = predptr->next; // newptr points to larger item in list
                predptr->next = newptr; // predptr now points to newptr since
                break;
            }

            // update pointer to examine next element
            predptr = predptr->next;
        }
    }

    // traverse list
    traverse();
}

/**
 * Searches for a number in list.
 */
void search(void)
{
    // prompt user for number
    printf("Number to search for: ");
    int n = GetInt();

    // get list's first node
    node* ptr = first;

    // search for number
    while (ptr != NULL)
    {
        if (ptr->n == n)
        {
            printf("\nFound %i!\n", n);
            sleep(1);
            break;
        }
        ptr = ptr->next;
    }
}

/**
 * Traverses list, printing its numbers.
 */
void traverse(void)
{
    // traverse list
    printf("\nLIST IS NOW: ");
    node* ptr = first;
    while (ptr != NULL)
    {
        printf("%i-> ", ptr->n);
        ptr = ptr->next;
    }

    // flush standard output since we haven't outputted any newlines yet
    fflush(stdout);

    // pause before continuing
    sleep(1);
    printf("\n\n");
}
