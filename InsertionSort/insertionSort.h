/*  Autor: Avelino Zepeda Martinez
    Date Created: April 8th, 2020
    Last Modified: April 19th, 2020

    Description: Insertion Sort
        Library contains functions to perform an in place insertion sort.
        Future modifications:
            - Research ways to optimize algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include "memUtils.h"

#ifndef __INSERTIONSORT_H__
#define __INSERTIONSORT_H__

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
void* insertionSort(void*, unsigned int, size_t, int (*compFun)(void*, void*));

#endif