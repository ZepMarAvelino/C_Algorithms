/*  Autor: Avelino Zepeda Martinez
	Date Created: April 9th, 2020
	Last Modified: April 19th, 2020

	Description: BubbleSort
*/

#include "bubbleSort.h"

/*
 * Compare function
 *
 * If 1, argument 1 is considered to meet the comparison requirements
 * If 0, argument 2 is considered to meet the comparison requirements
 *
 */
static int (*compareFunction)(void*, void*);

void* bubbleSort(void* array, unsigned int arrLength, size_t dataSize, int (*compFunc)(void*, void*)) {
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

	//Set sortedIdx to the end of the array (this assumes no element is considered sorted
	unsigned int sortedIdx = arrLength - 1;
	//Iterate through the whole array n times
	for (unsigned int count = 0; count < arrLength; count++, sortedIdx--) {
		//Flag to check if there were swaps through the whole array iteration
		int swapped = 0;
		//Set the elements to be compared to be at the beginning of the array
		void* cursor = array;
		void* nextElem = (char*)array + dataSize;
		//Compare each element to their next element until reaching the sorted element section
		for (unsigned int travIdx = 0; travIdx < sortedIdx; travIdx++) {
			//If the elem at cursor and nextElem should be swapped
			if (!compareFunction(cursor, nextElem)) {
				//Swap
				swap(cursor, nextElem, dataSize);
				//Set swapped flag
				swapped = 1;
			}
			//Increment the pointers of cursor and nextElem
			cursor = nextElem;
			nextElem = (char*)nextElem + dataSize;
		}
		if (swapped == 0) {
			//Array fully sorted
			break;
		}
	}
	return array;
}