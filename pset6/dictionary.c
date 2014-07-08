/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 * 
 * This dictionary implementation uses an array
 ***************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

char** dict_array;
long num_words;


/**
 * Returns true if word is in dictionary else false.
 * Implement binary search algorithm here
 */
bool check(const char* word)
{
    long min_index = 0;
    long max_index = num_words -1;
    long mid;
    bool found = false;
    int compare_value;

    // lowercase input word
    char ch;
    char* target = malloc(sizeof(word));
    int i = 0;
    do
    {
        ch = word[i];
        target[i] = tolower(word[i]);
        i++;
    } while (ch != '\0');
    

    // Search for word
    while (min_index <= max_index && !found)
    {
        mid = min_index + ((max_index - min_index) / 2);
        
        // Check for string
        compare_value = strcmp(target, dict_array[mid]);
        if (compare_value == 0)
        {
            found = true;
        }
        // word is less than dict_array[mid]
        else if (compare_value < 0)
        {
            max_index = mid - 1;
        }
        // word is greater than dict_array[mid]
        else
        {
            min_index = mid + 1;
        }

    }

    return found; 
}

/**
 * Loads dictionary into memory(data structure).  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    const char* default_dict = "/home/cs50/pset6/dictionaries/large";
    
    // We can not read in the file if it is the default_dict
    if (strcmp(dictionary, default_dict) == 0)
    {
        num_words = 143091;
    }
    else
    {
        num_words = file_size(dictionary);
    }

    // allocate string array
    dict_array = (char**) malloc(num_words * sizeof(char*)); 
    if (dict_array == NULL)
    {
        return false;
    }

    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Error loading file");
    }

    // allocate each string in the array and read in the file
    for (int i = 0; i < num_words; i++)
    {
        // allocate max size of string
        dict_array[i] = malloc(LENGTH * sizeof(char));
        
        // check if we have memory
        if (dict_array[i] == NULL)
        {
            return false;
        }

        // read line in from file into string
        fscanf(fp, "%s", dict_array[i]);
    }
    
    fclose(fp);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return num_words;
}

/**
 * Returns number of words in file
 */
unsigned int file_size(const char* dictionary)
{
    // TODO
    int count = 0;
    int ch;
    FILE *fp = fopen(dictionary, "r");

    do
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            count++;
        }
    } while (ch != EOF );

    free(fp);
    return count;
}

/**
 * Unloads dictionary from memory(data structure).  Returns true if successful else false.
 */
bool unload(void)
{
    // Free each string in the array    
    for (int i = 0; i < num_words; ++i)
    {
        if (dict_array[i] != NULL)
        {
            free(dict_array[i]);
        }
    }

    // free array containter
    if (dict_array != NULL)
    {
        free(dict_array);
    }

    return true;
}
