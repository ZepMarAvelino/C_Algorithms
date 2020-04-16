/*  Autor: Avelino Zepeda Martinez
    Date Created: April 10th, 2020
    Last Modified: April 10th, 2020

    Description: Quicksort
        Library contains functions to perform an in place Quicksort.
        Future modifications:
            - Research ways to optimize algorithm
            - Implement ternary quicksort

        Known Issues:
            - Arrays that have high value repetition can lead to a stack overflow.
                - Implementing ternary quicksort may fix this, and even significantly improve the performance in such cases
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef __QUICKSORT_H__
#define __QUICKSORT_H__

/*
 * Determines if the pivot should be:
 *  - Single .- Chooses the middle idx value as the pivot
 *  - Random .- Chooses a random idx as the pivot
 *  - Median .- Chooses the median value between the first, middle, and last idx as the pivot
 *  - Median of Five .- Chooses the median value between the first, middle, last, (last - first)/4 and (3*(last - first)/4)
 *  - Ninther Median .- Chooses the pivot using the ninther median, which is dictated by:
 *              ninther(a) = median(Mo3(first 1/3 of a), Mo3(middle 1/3 of a), Mo3(final 1/3 of a))
 */
typedef enum PivotSelect{SINGLE, RANDOM, MEDIAN, MEDIANFIVE, NINTHER} PivotSelect;

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
 * Internal function used to swap to blocks of memory. Requires additional memory the size of the third argument
 */
static int swap(void*, void*, size_t);

/*
 *  Gets the pivot of the array. Depending on the enum PivotSelect.
 *  If an invalid PivotSelect is fed, then it will default to Median Pivot
 *
 *  The types are:
 *      Single: Returns the middle of the array
 *      Random: Returns a random index of the array
 *      Median: Returns the median of 3. First element, last element, and middle element
 *      Median of Five: Returns the median of 5. First element, first quarter, middle, third quarter, last element
 *      Ninther: Returns the ninther median. This is the median of three of the first third of the array, middle third, and last third.
 *          It then obtains the median of these three medians.
 *
 *  Takes in :
 *      void* array - The array to be sorted
 *      unsigned int arrLength - Length of the array to be sorted
 *      PivotSelect - Enum of the pivot type
 *
 *Returns:
 *      void* array - Pointer to the sorted array
 */
static unsigned int getPivot(void*, unsigned int, size_t, PivotSelect);

/*
 *  Recursive portion of the quicksort algorithm
 *  Gets the pivot of the array, and sorts the array according to the pivot
 *  It then partitions the array in two and repeats. This is done until the partition is of size 1.
 *
 *  Takes in :
 *      void* array - The array to be sorted
 *      unsigned int arrLength - Length of the array to be sorted
 *      size_t dataSize - Size in bytes of each element in the array
 *      func pointer compFunc - Pointer to the comparison function
 *      PivotSelect - Enum of the pivot type
 *
 *Returns:
 *      void* array - Pointer to the sorted array
 */
void* partition(void* array, unsigned int length, size_t dataSize, PivotSelect pivotMethod);

/*
 *  Sorts an array in place.
 *
 *  Takes in :
 *      void* array - The array to be sorted
 *      unsigned int arrLength - Length of the array to be sorted
 *      size_t dataSize - Size in bytes of each element in the array
 *      func pointer compFunc - Pointer to the comparison function
 *      PivotSelect - Enum of the pivot type
 *
 *Returns:
 *      void* array - Pointer to the sorted array
 */
void* quicksort(void*, unsigned int, size_t, int (*compFun)(void*, void*), PivotSelect);

#endif