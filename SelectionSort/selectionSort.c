#include "selectionSort.h"

static void copy(void* dest, void* src, size_t dataSize) {
	//Used temporary char* (1 byte each), so we can copy the 
	// bytes and perform pointer arithmetic
	char* temp_dest = dest;
	char* temp_src = src;
	for (size_t i = 0; i < dataSize; i++) {
		temp_dest[i] = temp_src[i];
	}
}

static int swap(void* elem1, void* elem2, size_t dataSize) {
	//Allocate temp memory
	void* temp = (void*)malloc(dataSize);
	if (temp == NULL) {
		return -1;
	}

	//Swap elements
	copy(temp, elem1, dataSize);
	copy(elem1, elem2, dataSize);
	copy(elem2, temp, dataSize);

	//Free temp memory
	free(temp);

	return 0;
}

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