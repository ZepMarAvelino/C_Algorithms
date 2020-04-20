/*  Autor: Avelino Zepeda Martinez
	Date Created: April 3rd, 2020
	Last Modified: April 19th, 2020

	Description: Radix Sort
*/

#include "radixSort.h"

float* radixSortf(float* array, unsigned int arraySize, unsigned int base) {
	//Allocate memory for the long long array
	long long* sortArray = (long long*) malloc(sizeof(long long) * arraySize);
	if (sortArray == NULL) {
		return NULL;
	}

	//Convert to long long
	for (unsigned int i = 0; i < arraySize; ++i) {
		sortArray[i] = (long long)((double)array[i] * 100000);
	}

	//Sort
	if (radixSortLong(sortArray, arraySize, base) == NULL) {
		free(sortArray);
		return NULL;
	}

	//Convert back to float
	for (unsigned int i = 0; i < arraySize; ++i) {
		array[i] = (float)(sortArray[i] * 0.00001);
	}

	//Free memory
	free(sortArray);

	//Return pointer to the array
	return array;
}

/*
 * Internal function that performs the count sort section of radix sort.
 *
 * Called with every radix iteration.
 *
 * Takes in the array to sort, the size of the array, the range of the data (the base), and the current radix
 *
 * Returns NULL if it fails to sort the array, otherwise it returns the array
 */
static int* radix_countSort(int* array, unsigned int arraySize, unsigned int range, int radix) {
	//Allocate memory for the output array
	int* output = (int*) malloc(sizeof(int) * arraySize);
	if (output == NULL) {
		return NULL;
	}

	//Allocate memory for the "buckets" or possible counts
	unsigned int* count = (unsigned int*) malloc(sizeof(unsigned int) * (range));
	if (count == NULL) {
		return NULL;
	}

	//Initialize the buckets to 0
	for (unsigned int i = 0; i < range; ++i) {
		count[i] = 0;
	}

	//Count the number of elements in each bucket
	for (unsigned int i = 0; i < arraySize; ++i) {
		++count[(array[i] / radix) % range];
	}

	//Change the value of the counts to be the index in which each element will be organized in output\
	//If there are 24 0s, then 24 will be added to the 1s, and so on.
	for (unsigned int i = 1; i < range; ++i) {
		count[i] += count[i - 1];
	}

	//Move the elements to their sorted location
	for (int i = arraySize - 1; i >= 0; --i) {
		output[count[(array[i] / radix) % range] - 1] = array[i];
		--count[(array[i] / radix) % range];
	}
	for (unsigned int i = 0; i < arraySize; ++i) {
		array[i] = output[i];
	}

	free(output);
	free(count);
	return array;
}

int* radixSort(int* array, unsigned int arraySize, unsigned int base) {
	int radix = 1;
	int largest = array[0];
	for (unsigned int i = 1; i < arraySize; i++) {
		if (array[i] > largest) {
			largest = array[i];
		}
	}

	while (largest > radix) {
		if (radix_countSort(array, arraySize, base, radix) == NULL) {
			return NULL;
		}
		radix *= base;
	}
	return array;
}

/*
 * Internal function that performs the count sort section of radix sort for the long long version.
 *
 * Called with every radix iteration.
 *
 * Takes in the array to sort, the size of the array, the range of the data (the base), and the current radix

 * Returns NULL if it fails to sort the array, otherwise it returns the array
 */
static long long* radix_countSortLong(long long* array, unsigned int arraySize, unsigned int range, int radix) {
	//Allocate memory for the output array
	long long* output = (long long *)malloc(sizeof(long long) * arraySize);
	if (output == NULL) {
		return NULL;
	}

	//Allocate memory for the "buckets" or possible counts
	unsigned int* count = (unsigned int*) malloc(sizeof(unsigned int) * (range));
	if (count == NULL) {
		return NULL;
	}

	//Initialize the buckets to 0
	for (unsigned int i = 0; i < range; ++i) {
		count[i] = 0;
	}

	//Count the number of elements in each bucket
	for (unsigned int i = 0; i < arraySize; ++i) {
		++count[(array[i] / radix) % range];
	}

	//Change the value of the counts to be the index in which each element will be organized in output\
	//If there are 24 0s, then 24 will be added to the 1s, and so on.
	for (unsigned int i = 1; i < range; ++i){
		count[i] += count[i - 1];
	}

	//Move the elements to their sorted location
	for (int i = arraySize - 1; i >= 0; --i) {
		output[count[(array[i] / radix) % range]-1] = array[i];
		--count[(array[i] / radix) % range];
	}
	for (unsigned int i = 0; i < arraySize; ++i) {
		array[i] = output[i];
	}

	free(output);
	free(count);
	return array;
}

long long* radixSortLong(long long* array, unsigned int arraySize, unsigned int base) {
	unsigned int radix = 1;
	long long largest = array[0];
	for (unsigned int i = 1; i < arraySize; i++) {
		if (array[i] > largest) {
			largest = array[i];
		}
	}

	while (largest > radix) {
		if (radix_countSortLong(array, arraySize, base, radix) == NULL) {
			return NULL;
		}
		radix *= base;
	}
	return array;
}