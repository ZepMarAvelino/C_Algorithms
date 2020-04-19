/*  Autor: Avelino Zepeda Martinez
    Date Created: April 3rd, 2020
    Last Modified: April 6th, 2020

    Description: Radix Sort LSD
        Library contains functions to perform an in place radix sort on arrays of floats, ints, and long long.
        Future modifications:
            - Research ways to optimize algorithm (memory usage can be quite high as it requires enough space to generate an array of equal size)
            - Create an MSD version of the algorithm
            - Implement integer overflow safeguards
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __RADIXSORT_H__
#define __RADIXSORT_H__

/*
 * Wrapper function for radix sort using floats
 *
 * Converts the floats into long long ints (multiplies by 10^5) and performs radixSortLong
 *
 * Takes in an array of floats, the size of the array, the base of the numbers
 *
 * Returns the array of floats sorted
 */
float* radixSortf(float*, unsigned int, unsigned int);

/*
 * Internal function that performs the count sort section of radix sort.
 *
 * Called with every radix iteration.
 *
 * Takes in the array to sort, the size of the array, the range of the data (the base), and the current radix
 *
 * Returns NULL if it fails to sort the array, otherwise it returns the array
 */
static int* radix_countSort(int*, unsigned int, unsigned int, unsigned int);

/*
 * Radix sort function
 *
 * Takes in an array of int, the size of the array, the base of the numbers
 *
 * Returns the array sorted
 */
int* radixSort(int*, unsigned int, unsigned int);

/*
 * Internal function that performs the count sort section of radix sort for the long long version.
 *
 * Called with every radix iteration.
 *
 * Takes in the array to sort, the size of the array, the range of the data (the base), and the current radix

 * Returns NULL if it fails to sort the array, otherwise it returns the array
 */
static long long* radix_countSortLong(long long* array, unsigned int arraySize, unsigned int range, unsigned int radix);

/*
 * Radix sort function
 *
 * Takes in an array of long longs, the size of the array, the base of the numbers
 * 
 * Returns the array sorted
 */
long long* radixSortLong(long long*, unsigned int, unsigned int);

#endif
