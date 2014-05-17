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
int binary_search_r(int value, int values[], int min_index,  int max_index)
{
    // Invalid index values, return -1 stating item isn't in the array
    if (min_index > max_index)
    {
        return -1;
    }

    // Calculate the mid index
    int mid = (min_index + (max_index - min_index)) / 2; // Limited number calculation to prevent overflow
    
    // Is the index at the middle of the remaining the value? if so
    // return the index
    if (value == values[mid])
    {
        return mid;
    }
    else if (value < values[mid])
    // value is lower than subset, check lower half of remaining array
    {
        return binary_search_r(value, values, min_index, mid-1);
    }
    else if (value > values[mid])
    // value is higher that subset, check hight half of remaining array
    {
        return binary_search_r(value, values, mid+1, max_index); 
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
        int mid = (min_index + (max_index - min_index)) / 2; // Limited number calculation to prevent overflow
        
        // found the item, return the index
        if (values[mid] == value)
        {
            return mid;
        }
        // Determine which subarray to search
        else if (values[mid] < value)
        {
            min_index = mid + 1;
        }
        else
        {
            max_index = mid -1;
        }

    }

    // Value was not found
    return -1;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //bubble_sort(values, n);
    //selection_sort(values, n);
    insertion_sort(values, n);
    return;
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
void merge_sort(int values[], int n)
{
    // TODO: implement an O(n * log n) sorting algorithm
    return;
}
