/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
//    int index = linear_search(value, values, n);
//    int index = binary_search_r(value, values, 0, n-1);
    int index = binary_search_it(value, values, n-1);

    return index == -1 ? false : true; 
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //bubble_sort(values, n);
    //selection_sort(values, n);
    //insertion_sort(values, n);
    merge_sort(values, 0, n-1);

    return;
}

/**
 * Linear search algorithm.
 * Iterate over every item in the array, and check if it is the value.
 */
int linear_search(int value, int values[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        // If we find the value return true
        if (values[i] == value)
        {
            return i;
        }
    }
    
    // No value found after iterating over the whole array.
    return -1;
}

/**
 * Binary search algorithm using recursion. Pre-condition: values[] must be sorted.
 * 
 */
int binary_search_r(int value, int values[], int min_index, int max_index)
{
    int mid = min_index + ((max_index - min_index) / 2);

    // Base Case, item has not been found
    if (min_index == max_index && value != values[mid])
    {
        return -1; 
    }
    else
    // Keep searching for item in subarray
    {   
        // Base case Item has been found
        if (value == values[mid])
        { 
            return mid; // value found
        }
        // Determine which subdirectory to continue searching
        else if (value < values[mid])
        {
            // search lower subset
            return binary_search_r(value, values, min_index, mid-1);
        }
        else if (value > values[mid])
        {
            // search upper subset
            return binary_search_r(value, values, mid+1, max_index);
        }
    }

    return -1;
}

/**
 * Binary search algorithm iteratively implemented. Pre-condition: values[] must be sorted.
 */
int binary_search_it(int value, int values[], int max_index)
{
    int min_index = 0;
    
    while (max_index >= min_index)
    {
        int mid = min_index + ((max_index - min_index) / 2); // Limited number calculation to prevent overflow
        
        // Determine which subarray to search
        if (value < values[mid])
        {
            max_index = mid - 1;
        }
        else if (value > values[mid])
        {
            min_index = mid + 1;
        }
        else
        // found the item, return the index
        {
            return mid;
        }
    }

    // Value was not found
    return -1;
}


void bubble_sort(int values[], int n)
{
    //  implement an O(n^2) sorting algorithm
    // Keep swapping values until the array is sorted
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n-1; ++i)
        {
            // if values[i] is larger than values[i+1], then swap the values
            if (values[i] > values[i+1])
            {
                int temp = values[i+1];
                values[i+1] = values[i];
                values[i] = temp; 
            }
        }
    }
    
    return;
}

/**
 * Selection sort works by selecting the smallest elemnt of the array,
 * and placing it as the head of the array. The process is repeated for
 * the remainder of the array; the next largest element is selected and 
 * put into the next slot.
 */
void selection_sort(int values[], int n)
{
    for (int j = 0; j < n; ++j)
    {
        // Start with the value of the index
        int index_of_min = j;
        
        // Iterate through the array and determine the smallest index
        for (int i = j; i < n; ++i)
        {
            if (values[index_of_min] > values[i])
            {
                index_of_min = i;
            }
        }

        // Switch the smallest number into the head position
        int temp = values[j];
        values[j] =values[index_of_min];
        values[index_of_min] = temp;
    }

    return;
}

/**
 * Insertion sort inserts each element of the array into the proper
 * position.
 *
 * Example [5, 2, 3, 1, 4]:
 *                                                  => 5, 2, 3, 1, 4
 * Start with 2, and two belongs before 5           => 2, 5, 3, 1, 4
 * Move into 3, and 3 is greater than 2 less than 5 => 2, 3, 5, 1, 4
 * One is the lowest                                => 1, 2, 3, 5, 4
 * 4 is lower than 5 greater than 3                 => 1, 2, 3, 4, 5
 */
void insertion_sort(int values[], int n)
{
    //  implement an O(n^2) sorting algorithm
    for (int j = 1; j < n; ++j)
    {
        int i = j;
        int value = values[j];
        
        // Shift values in the array 
        while (i > 0 && (values[i-1] > value))
        {
            values[i] = values[i-1]; // shift values to the right
            i--;
        }

        values[i] = value;
    }

    return;
}

/**
 *
 */
void merge(int values[], int min, int mid, int max)
{
    int temp_length = max-min + 1;
    int temp_array[temp_length]; // temp array for sorting

    int pos = 0;
    int left_pos = min;
    int right_pos = mid + 1;
    
    // Sort the values
    while (left_pos <= mid && right_pos <= max)
    {
        if (values[left_pos] < values[right_pos])
        {
            // Copy value into temp array and move up the left pos and position
            temp_array[pos++] = values[left_pos++];
        }
        else
        {
            temp_array[pos++] = values[right_pos++];
        }
    }
    // Copy remaining values into the array
    while (left_pos <= mid)
        temp_array[pos++] = values[left_pos++];
    while (right_pos <= max)
        temp_array[pos++] = values[right_pos++];
    
    /* Copy temp values back into the original array */
    for (int i = 0; i < temp_length; ++i)
    {
        values[i + min] = temp_array[i];
    }

    return;
}

/**
 *
 */
void merge_sort(int values[], int min, int max)
{
    int mid = (min + max) / 2;

    if (min < max)
    {
        // Sort the left half values
        merge_sort(values, min, mid);
        // Sort the right half values
        merge_sort(values, mid+1, max);

        merge(values, min, mid, max);
    }

    return;
}

