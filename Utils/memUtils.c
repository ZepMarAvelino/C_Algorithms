#include "memUtils.h"

void copy(void* dest, void* src, size_t dataSize) {
	//Used temporary char* (1 byte each), so we can copy the 
	// bytes and perform pointer arithmetic
	char* temp_dest = dest;
	char* temp_src = src;
	for (size_t i = 0; i < dataSize; i++) {
		temp_dest[i] = temp_src[i];
	}
}

int swap(void* elem1, void* elem2, size_t dataSize) {
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

int equal(void* elem1, void* elem2, size_t dataSize) {
	char* temp1 = elem1;
	char* temp2 = elem2;
	for (size_t i = 0; i < dataSize; i++) {
		if (temp1[i] != temp2[i]) {
			return 0;
		}
	}
	return 1;
}