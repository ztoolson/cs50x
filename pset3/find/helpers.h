/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Different search algorithms for an array
 */
int linear_search(int value, int values[], int n);
int binary_search_r(int value, int values[], int min_index, int max_index);
int binary_search_it(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

/**
 * Implements bubble sort algorithm
 */
void bubble_sort(int values[], int n);

/**
 * Implements selection sort algorithm
 */
void selection_sort(int values[], int n);

/**
 * Implements insertion sort algorithm
 */
void insertion_sort(int values[], int n);

/**
 * Implements merge sort algorithm
 */
void merge(int values[], int min, int mid, int max);
void merge_sort(int values[], int min_index, int max_index);
