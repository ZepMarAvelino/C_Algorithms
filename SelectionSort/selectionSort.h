/*  Autor: Avelino Zepeda Martinez
    Date Created: April 9th, 2020
    Last Modified: April 19th, 2020

    Description: Selection Sort
        Library contains functions to perform an in place Selection sort.
        Future modifications:
            - Research ways to optimize algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include "memUtils.h"

#ifndef __SELECTIONSORT_H__
#define __SELECTIONSORT_H__

/*
 *  Sorts an array in place.
 *
 *  Takes in :
 *      void* array - The array to be sorted
 *      unsigned int arrLength - Length of the array to be sorted
 *      size_t dataSize - Size in bytes of each element in the array
 *      func pointer compFunc - Pointer to the comparison function
 *
 *Returns:
 *      void* array - Pointer to the sorted array
 */
void* selectionSort(void*, unsigned int, size_t, int (*compFunc)(void*, void*));

#endif