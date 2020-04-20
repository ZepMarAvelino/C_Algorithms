/*  Autor: Avelino Zepeda Martinez
    Date Created: April 19th, 2020
    Last Modified: April 19th, 2020

    Description: Memory Utilities for the C_Algorithms Library
    Library contains functions to perform some memory management (copy, swap, or compare memory blocks)
        Future modifications:
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef __MEMUTILS_H__
#define __MEMUTILS_H__

/*
 * Function used to copy a block of data of size_t onto memory location
 * (Same as memcpy?)
 */
void copy(void*, void*, size_t);


/*
 * Function used to swap to blocks of memory. Requires additional memory the size of the third argument
 */
int swap(void*, void*, size_t);


/*
 * Function used to compare if two blocks of memory are the same
 */
int equal(void* elem1, void* elem2, size_t dataSize);

#endif