/*  Autor: Avelino Zepeda Martinez
    Date Created: April 10th, 2020
    Last Modified: April 19th, 2020

    Description: Quicksort
        Library contains functions to perform an in place Quicksort.
        Future modifications:
            - Research ways to optimize algorithm

*/

#include <stdio.h>
#include <stdlib.h>
#include "memUtils.h"

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