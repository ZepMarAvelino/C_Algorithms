/*  Autor: Avelino Zepeda Martinez
    Date Created: April 7th, 2020
    Last Modified: April 7th, 2020

    Description: Merge Sort
        Library contains functions to perform an in place merge sort.
        Future modifications:
            - Research ways to optimize algorithm
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef __MERGESORT_H__
#define __MERGESORT_H__


/*
 * Compare function
 *
 * If 1, argument 1 is considered to meet the comparison requirements
 * If 0, argument 2 is considered to meet the comparison requirements
 *
 */
static int (*compareFunction)(void*, void*);

/*
 * Internal function used to copy a block of data of size_t onto memory location
 * (Same as memcpy?)
 */
static void copy(void*, void*, size_t);

/*
 * Receives pointers to the beginning of the two split arrays. It then merges them in a sorted fashion.
 * Sorts in a stable fashion as long as the comparison function is done properly
 *
 * Takes in:
 *      void* arr1 - Pointer to the first array to be merged
 *      unsigned int arrLength1 - Length of the first section of the array
 *      void* arr2 - Pointer to the second array to be merged
 *      unsigned int arrLength2 - Length of the second section of the array
 *      size_t dataSize - Size in bytes of each element in the array
 *
 * Returns:
 *      void* array - Pointer to the merged array
 */
static void* merge(void*, unsigned int, void*, unsigned int, size_t);

/*
 * Recursive function, used to split the array to single blocks.
 * After splitting its array, it merges the pieces returned by the recursed function calls
 * It does not allocate more memory for the splitted sections
 * Only allocated memory is done while merging, as we need a temporary array to hold the sorted data
 *
 * Takes in:
 *      void* arr - The array to be sorted
 *      unsigned int arrLength - Length of the array to be sorted
 *      size_t dataSize - Size in bytes of each element in the array
 *
 * Returns:
 *      void* array - Pointer to the sorted array
 *          - If at any point the memory allocation failed, it returns null and stops the sorting
 */
static void* split(void*, unsigned int, size_t);

/*
 * Wrapper function. Only function accessible by the user
 * Sorts an array in place.
 *
 * Takes in:
 *      void* array - The array to be sorted
 *      unsigned int arrLength - Length of the array to be sorted
 *      size_t dataSize - Size in bytes of each element in the array
 *      func pointer compFunc - Pointer to the comparison function
 *
 * Returns:
 *      void* array - Pointer to the sorted array
 */
void* mergeSort(void*, unsigned int, size_t, int (*compFunc)(void*, void*));

#endif