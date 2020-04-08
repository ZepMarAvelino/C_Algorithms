/*  Autor: Avelino Zepeda Martinez
    Date Created: April 8th, 2020
    Last Modified: April 8th, 2020

    Description: Insertion Sort
        Library contains functions to perform an in place insertion sort.
        Future modifications:
            - Research ways to optimize algorithm
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef __INSERTIONSORT_H__
#define __INSERTIONSORT_H__


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


void* insertionSort(void*, unsigned int, size_t, int (*compFun)(void*, void*));

#endif