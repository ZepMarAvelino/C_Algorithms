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
		return NULL;
	}

	//Convert back to float
	for (unsigned int i = 0; i < arraySize; ++i) {
		array[i] = (sortArray[i] * 0.00001);
	}

	//Free memory
	free(sortArray);

	//Return pointer to the array
	return array;
}

static int radix_countSort(int* array, unsigned int arraySize, unsigned int range, unsigned int radix) {
	//Allocate memory for the output array
	int* output = malloc(sizeof(int) * arraySize);
	if (output == NULL) {
		return -1;
	}

	//Allocate memory for the "buckets" or possible counts
	unsigned int* count = malloc(sizeof(unsigned int) * (range));
	if (count == NULL) {
		return -1;
	}

	//Initialize the buckets to 0
	for (unsigned int i = 0; i < range; ++i) {
		count[i] = 0;
	}

	//Count the number of elements in each bucket
	for (unsigned int i = 0; i < arraySize; ++i) {
		++count[(array[i] / radix) % range];
	}

	//If all the elements are in the bottom range, then we have reached the end
	if (count[0] == arraySize) {
		return 1;
	}
	//Change the value of the counts to be the index in which each element will be organized in output\
	//If there are 24 0s, then 24 will be added to the 1s, and so on.
	for (unsigned int i = 1; i < range; ++i) {
		//If any of the counts contains all the elements in the array, then we have reached the end
		if (count[i] == arraySize) {
			return 1;
		}
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
	return 0;
}

int* radixSort(int* array, unsigned int arraySize, unsigned int base) {
	unsigned int radix = 1;
	while (!radix_countSort(array, arraySize, base, radix)) {
		radix *= base;
	}
	return array;
}

static int radix_countSortLong(long long* array, unsigned int arraySize, unsigned int range, unsigned int radix) {
	//Allocate memory for the output array
	long long* output = malloc(sizeof(long long) * arraySize);
	if (output == NULL) {
		return -1;
	}

	//Allocate memory for the "buckets" or possible counts
	unsigned int* count = malloc(sizeof(unsigned int) * (range));
	if (count == NULL) {
		return -1;
	}

	//Initialize the buckets to 0
	for (unsigned int i = 0; i < range; ++i) {
		count[i] = 0;
	}

	//Count the number of elements in each bucket
	for (unsigned int i = 0; i < arraySize; ++i) {
		++count[(array[i] / radix) % range];
	}

	//If all the elements are in the bottom range, then we have reached the end
	if (count[0] == arraySize) {
		return 1;
	}
	//Change the value of the counts to be the index in which each element will be organized in output\
	//If there are 24 0s, then 24 will be added to the 1s, and so on.
	for (unsigned int i = 1; i < range; ++i){
		//If any of the counts contains all the elements in the array, then we have reached the end
		if (count[i] == arraySize) {
			return 1;
		}
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
	return 0;
}

long long* radixSortLong(long long* array, unsigned int arraySize, unsigned int base) {
	unsigned int radix = 1;
	while (!radix_countSortLong(array, arraySize, base, radix)) {
		radix *= base;
	}
	return array;
}