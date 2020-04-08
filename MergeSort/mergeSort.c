/*  Autor: Avelino Zepeda Martinez
	Date Created: April 7th, 2020
	Last Modified: April 7th, 2020

	Description: Merge Sort
*/

#include "mergeSort.h"

static void copy(void* dest, void* src, size_t dataSize) {
	//Used temporary char* (1 byte each), so we can copy the 
	// bytes and perform pointer arithmetic
	char* temp_dest = dest;
	char* temp_src = src;
	for (size_t i = 0; i < dataSize; i++) {
		temp_dest[i] = temp_src[i];
	}
}

static void* merge(void* arr1, unsigned int arrLength1, void* arr2, unsigned int arrLength2, size_t dataSize) {
	//Get the resulting arrays length
	unsigned int totalLength = arrLength1 + arrLength2;

	//Allocate memory for temporary array
	void* temp = (void*)malloc(dataSize * (totalLength));
	if (temp == NULL) {
		return NULL;
	}

	//Iterate through the whole array
	void* cursor1 = arr1;
	void* cursor2 = arr2;
	void* tempCursor = temp;
	//Used to make sure we don't go out of boundaries of the subarrays
	unsigned int idx1 = 0;
	unsigned int idx2 = 0;
	while(idx1 < arrLength1 || idx2 < arrLength2) {
		//If we have copied all the elements of arr1, then copy all the elements of arr2
		//This should guarantee that (totalLength - i) == (arrLength2 - idx2)
		if (idx1 >= arrLength1) {
			while (idx2 < arrLength2) {
				copy(tempCursor, cursor2, dataSize);
				cursor2 = ((char*)cursor2 + dataSize);
				idx2++;
				tempCursor = ((char*)tempCursor + dataSize);
			}
		}
		//If we have copied all the elements of arr2, then copy all the elements of arr1
		//This should guarantee that (totalLength - i) == (arrLength1 - idx1)
		else if (idx2 >= arrLength2) {
			while (idx1 < arrLength1) {
				copy(tempCursor, cursor1, dataSize);
				cursor1 = ((char*)cursor1 + dataSize);
				idx1++;
				tempCursor = ((char*)tempCursor + dataSize);
			}
		}
		else {
			//If the element at the front of arr1 meets the comparison requirements,
			//copy it to the temp array
			//After move the cursor on arr1 to the next element
			if (compareFunction(cursor1, cursor2)) {
				copy(tempCursor, cursor1, dataSize);
				cursor1 = ((char*)cursor1 + dataSize);
				idx1++;
			}
			//Else if the element at the front of arr2 meets the requirements, copy it instead
			//After move the cursor on arr2 to the next element
			else {
				copy(tempCursor, cursor2, dataSize);
				cursor2 = ((char*)cursor2 + dataSize);
				idx2++;
			}
			//Move the cursor on the temp array to the next element
			tempCursor = ((char*)tempCursor + dataSize);
		}
	}



	//Once all the elements have been sorted into the temp array,
	//copy them back onto arr1, then free the memory used in temp
	cursor1 = arr1;
	tempCursor = temp;
	for (unsigned int i = 0; i < totalLength; i++) {
		copy(cursor1, tempCursor, dataSize);
		cursor1 = ((char*)cursor1 + dataSize);
		tempCursor = ((char*)tempCursor + dataSize);
	}
	free(temp);

	return arr1;
}

static void* split(void* arr, unsigned int arrLength, size_t dataSize) {
	//If the array is of size one or empty (it should be 1 at minimum)
	//return the array so it can be merged
	if (arrLength <= 1) {
		return arr;
	}
	else {
		unsigned int arrLength1, arrLength2;
		void* arr1;
		void* arr2;
		//If the array is of an odd length
		if (arrLength % 2) {
			arrLength1 = arrLength / 2;
			arrLength2 = (arrLength / 2) + 1;
		}
		//If the array is of an even length
		else {
			arrLength1 = arrLength / 2;
			arrLength2 = arrLength / 2;
		}

		arr1 = arr;
		//Casting to char* to perform pointer arithmetic (as we know the data size)
		//Casting back to void* just to guarantee there won't be any issues.
		//The second array is just a pointer to the middle of the original array.
		//Ideally this will save memory usage, so we will only need additional memory when merging
		arr2 = ((char*)arr + (dataSize * arrLength1));


		//Split and sort each subarray
		arr1 = split(arr1, arrLength1, dataSize);
		arr2 = split(arr2, arrLength2, dataSize);
		//If there was an issue in one of the underlying splits and merges, return null. 
		if ((arr1 == NULL) || (arr2 == NULL)) {
			return NULL;
		}
		//Merge the split array. The split parts are first sorted.
		//Return the merged and sorted array
		return merge(arr1, arrLength1, arr2, arrLength2, dataSize);
	}
}

void* mergeSort(void* array, unsigned int arrayLength, size_t dataSize, int (*compFunc)(void*, void*)) {
	//If no function is fed into the algorithm, return NULL (Otherwise it will fail)
	if (compFunc == NULL) {
		return NULL;
	}
	//Set the compareFunction of the algorithm to be the argumented function
	compareFunction = compFunc;

	//Sort the array and return it
	return split(array, arrayLength, dataSize);
}