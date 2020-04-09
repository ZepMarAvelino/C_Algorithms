#include "bubbleSort.h"

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
	void* temp = (void*) malloc(dataSize);
	if (temp == NULL) {
		return -1;
	}

	//Swap elements
	copy(temp, elem1, dataSize);
	copy(elem1, elem2, dataSize);
	copy(elem2, temp, dataSize);

	//Free temp memory
	free (temp);

	return 0;
}

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