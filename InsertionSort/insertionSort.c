/*  Autor: Avelino Zepeda Martinez
	Date Created: April 8th, 2020
	Last Modified: April 19th, 2020

	Description: Insertion Sort
*/

#include "insertionSort.h"

/*
 * Compare function
 *
 * If 1, argument 1 is considered to meet the comparison requirements
 * If 0, argument 2 is considered to meet the comparison requirements
 *
 */
static int (*compareFunction)(void*, void*);

void* insertionSort(void* array, unsigned int arrLength, size_t dataSize, int (*compFunc)(void*, void*)) {
	//Check if a function was fed
	if (compFunc == NULL) {
		return NULL;
	}

	//Assign the function to be used
	compareFunction = compFunc;

	//Declare a temporary pointer to hold the data
	void* temp = (void*)malloc(dataSize);
	if (temp == NULL) {
		return NULL;
	}

	//Iterate through the array
	//Set the sorted cursor to the beginning of the array
	//Set the unsorted cursor to be at idx = 1
	void* sortedCursor = array;
	void* unsortedCursor = (char*)array + dataSize;
	int sortedIdx = 0;
	int unsortedIdx = 1;

	//While there are unsorted elements in the array
	while (unsortedIdx < arrLength) {
		//Reset the sorted cursor to be at the start of the array
		sortedCursor = array;
		sortedIdx = 0;
		//Check through every element in the sorted section
		//If we reach a point where sortedIdx == unsortedIdx then the element is considered sorted
		while (sortedIdx < unsortedIdx) {

			//If the unsorted cursor should be at this position
			if (!compareFunction(sortedCursor, unsortedCursor)) {
				//copy the element at unsorted cursor to the temp pointer
				copy(temp, unsortedCursor, dataSize);

				//Shift all the elements to the right by 1 idx
				//We do this starting closest to the unsorted cursor, to avoid unnecessary copies
				void* dest = unsortedCursor;
				void* src = (char*)dest - dataSize;
				for (int srcIdx = unsortedIdx - 1; srcIdx >= sortedIdx; srcIdx--) {
					copy(dest, src, dataSize);
					dest = (char*)dest - dataSize;
					src = (char*)src - dataSize;
				}

				//Once all the elements have been shifted, then insert the element to sortedCursor
				copy(sortedCursor, temp, dataSize);
				//Stop the while loop to move onto the next unsorted element
				break;
			}
			//Increment the sorted cursor
			else {
				sortedCursor = (char*)sortedCursor + dataSize;
				sortedIdx++;
			}
		}
		//Increment the unsorted cursor and idx
		unsortedCursor = (char*)unsortedCursor + dataSize;
		unsortedIdx++;
	}
	return array;
}