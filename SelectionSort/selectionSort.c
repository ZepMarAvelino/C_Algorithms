/*  Autor: Avelino Zepeda Martinez
	Date Created: April 9th, 2020
	Last Modified: April 19th, 2020

	Description: Selection Sort
*/

#include "selectionSort.h"

/*
 * Compare function
 *
 * If 1, argument 1 is considered to meet the comparison requirements
 * If 0, argument 2 is considered to meet the comparison requirements
 *
 */
static int (*compareFunction)(void*, void*);

void* selectionSort(void* array, unsigned int arrLength, size_t dataSize, int (*compFunc)(void*, void*)) {
	//Check if Array is at least of size 2
	//If not, assume array sorted (size 1)
	if (arrLength < 2) {
		return array;
	}
	//Validate that the function fed is not empty
	if (compFunc == NULL) {
		return NULL;
	}
	compareFunction = compFunc;

	//Set cursors
	// Beginning of unsorted section
	void* unsortedCursor = array;
	// Current minimum element in the unsorted section
	void* minCursor = array;
	// Current element being compared
	void* iterCursor = array;

	//Iterate at least N times
	for (unsigned int i = 0; i < arrLength; i++) {
		iterCursor = unsortedCursor;
		minCursor = unsortedCursor;
		for (unsigned int j = i; j < arrLength; j++) {
			if (compareFunction(iterCursor, minCursor)) {
				minCursor = iterCursor;
			}
			iterCursor = (char*)iterCursor + dataSize;
		}
		if (minCursor != unsortedCursor) {
			swap(minCursor, unsortedCursor, dataSize);
		}
		unsortedCursor = (char*)unsortedCursor + dataSize;
	}

	return array;
}