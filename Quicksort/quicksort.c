#include "quicksort.h"

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

static unsigned int getPivot(void* array, unsigned int length, size_t dataSize, PivotSelect pivotMethod) {
    //Hold Pivot
    unsigned int pivot;
    //Holds the idx of the 5 points (start, middle, end, first quarter, third quarter)
    unsigned int start, middle, end, q1, q3;
    //Pointer to the values at the 5 indices above
    void* startPtr, * endPtr, * middlePtr, * q1Ptr, * q3Ptr;

    //Initializes middle idx
    middle = length >> 1;

    //Used for the ninther median:
    //ninther(a) = median(Mo3(first 1/3 of a), Mo3(middle 1/3 of a), Mo3(final 1/3 of a))
    void* nintherSubArray;
    unsigned int* nintherSubIdx;
    unsigned int nintherSubLength;

    int startq1, startMiddle, startq3, startEnd, middleq1, middleEnd, 
        middleq3, endq1, endq3, q1q3;

    switch (pivotMethod) {
        case SINGLE:
            pivot = middle;
            break;
        case RANDOM:
            pivot = rand() % length;
            break;
        default:
        case MEDIAN:
            if (length < 3) {
                pivot = middle;
                break;
            }

            startPtr = array;
            endPtr = (char*)array + (dataSize * (length - 1));
            middlePtr = (char*)array + (dataSize * (middle));

            startMiddle = compareFunction(startPtr, middlePtr);
            startEnd = compareFunction(startPtr, endPtr);
            middleEnd = compareFunction(middlePtr, endPtr);

            if (startMiddle + startEnd == 1) {
                pivot = 0;
            }
            else if (!startMiddle + middleEnd == 1) {
                pivot = middle;
            }
            else {
                pivot = length - 1;
            }

            break;
        case MEDIANFIVE:
            if (length < 5) {
                pivot = middle;
                break;
            }

            q1 = middle >> 1;
            q3 = middle + q1;
            startPtr = array;
            endPtr = (char*)array + (dataSize * (length - 1));
            middlePtr = (char*)array + (dataSize * (middle));
            q1Ptr = (char*)array + (dataSize * (q1));
            q3Ptr = (char*)array + (dataSize * (q3));


            startq1 = compareFunction(startPtr, q1Ptr);
            startMiddle = compareFunction(startPtr, middlePtr);
            startq3 = compareFunction(startPtr, q3Ptr);
            startEnd = compareFunction(startPtr, endPtr);
            middleq1 = compareFunction(middlePtr, q1Ptr);
            middleEnd = compareFunction(middlePtr, endPtr);
            middleq3 = compareFunction(middlePtr, q3Ptr);
            endq1 = compareFunction(endPtr, q1Ptr);
            endq3 = compareFunction(endPtr, q3Ptr);
            q1q3 = compareFunction(q1Ptr, q3Ptr);

            if ((startq1 + startMiddle + startq3 + startEnd) == 2) {
                pivot = 0;
            }
            else if ((!startq1 + !middleq1 + q1q3 + endq1) == 2) {
                pivot = q1;
            }
            else if ((!startMiddle + middleq1 + middleq3 + middleEnd) == 2) {
                pivot = middle;
            }
            else if ((!startq3 + !q1q3 + !middleq3 + endq3) == 2) {
                pivot = q3;
            }
            else {
                pivot = length - 1;
            }

            break;
        case NINTHER:
            if (length < 3) {
                pivot = middle;
                break;
            }
            
            //Used for the ninther calculation:
            //ninther(a) = median(Mo3(first 1/3 of a), Mo3(middle 1/3 of a), Mo3(final 1/3 of a))
            nintherSubArray = (void*)malloc(dataSize * 3);
            nintherSubIdx = (unsigned int*)malloc(sizeof(unsigned int) * 3);

            //If the memory failed to allocate, then return the median of the whole array as the pivot
            if ((nintherSubArray == NULL) || (nintherSubIdx == NULL)) {
                pivot = getPivot(array, length, dataSize, MEDIAN);
                break;
            }

            //Get the length of a third of the array
            nintherSubLength = length / 3;
            
            //Get the 3 medians
            for (int i = 0; i < 3; i++) {
                //If the last median, include the truncated part of the division by three
                if (i == 2) {
                    nintherSubIdx[i] = (nintherSubLength * i) + getPivot((char*)array + (dataSize * (nintherSubLength * i)), nintherSubLength + (length % 3), dataSize, MEDIAN);
                }
                else {
                    nintherSubIdx[i] = (nintherSubLength * i) + getPivot((char*)array + (dataSize * (nintherSubLength * i)), nintherSubLength, dataSize, MEDIAN);
                }
                //Copy the value of the medians to the nintherSubArray
                copy((char*)nintherSubArray + (dataSize * i), (char*)array + (dataSize * nintherSubIdx[i]), dataSize);
            }
            //Get the median of the 3 medians and return the idx of the resulting median
            pivot = nintherSubIdx[getPivot(nintherSubArray, 3, dataSize, MEDIAN)];

            //Free the pointers
            free(nintherSubArray);
            free(nintherSubIdx);
            break;
    }
    return pivot;
}

static void* partition(void* array, unsigned int length, size_t dataSize, PivotSelect pivotMethod) {
    //If the array is less than 2 elements, we have finished the recursion
    if (length < 2) {
        return array;
    }

    //Get the pivot
    unsigned int pivot = getPivot(array, length, dataSize, pivotMethod);
    //printf("Pivot: %d\tLength: %d\t", pivot, length);
    void* pivotCursor = (char*)array + (dataSize * (pivot));

    //Designate the idx values of the left and right pointers
    unsigned int leftIdx = 0;
    unsigned int rightIdx = length - 1;

    //Check they are not equal to the pivot
    if ((leftIdx == pivot) && (leftIdx < (rightIdx - 1))){
        leftIdx++;
    }
    else if ((rightIdx == pivot) && (rightIdx > (leftIdx + 1))) {
        rightIdx--;
    }

    //Designate our left and right pointers
    void* leftCursor = (char*)array + (dataSize * leftIdx);
    void* rightCursor = (char*)array + (dataSize * rightIdx);

    //Designate the left and right flags
    //This will be used in the loop to determine if the values point to a value that needs to be swapped
    int leftSwap = 0;
    int rightSwap = 0;

    //Pre-Sort the array
    //While the left cursor is on the left side of the right cursor
    while (leftIdx < (rightIdx - 1)) {

        //If both cursors need to be swapped. Swap the values and reset the flags
        if (leftSwap && rightSwap) {
            swap(leftCursor, rightCursor, dataSize);
            leftSwap = 0;
            rightSwap = 0;
        }
        //If they are not to be swapped, check the current left and right pointers against the pivot
        else {
            //If left pointer does not need to be swapped
            if (!leftSwap) {
                leftSwap = !compareFunction(leftCursor, pivotCursor);
            }
            //If right pointer does not need to be swapped
            if (!rightSwap) {
                rightSwap = compareFunction(rightCursor, pivotCursor);
            }
        }

        //After the newest comparison, if they still can't be swapped, increment/decrement the pointer
        if (!leftSwap) {
            leftIdx++;
            leftCursor = (char*)leftCursor + dataSize;        
            //Check that the left pointer is not pointing to the pivot and that incrementing it won't point to the right idx
            if ((leftIdx == pivot) && (leftIdx < (rightIdx - 1))) {
                leftIdx++;
                leftCursor = (char*)leftCursor + dataSize;
            }
        }
        //If the two pointers are right beside each other, then do not change this one
        if ((!rightSwap) && (rightIdx > (leftIdx + 1))) {
            rightIdx --;
            rightCursor = (char*)rightCursor - dataSize; 
            if ((rightIdx == pivot) && (rightIdx > (leftIdx + 1))) {
                rightIdx--;
                rightCursor = (char*)rightCursor - dataSize;
            }
        }
 
    }
    
    //Do a last check to see if they need swapping.
    //If one pointer does need swapping, shift the pointers by one dataSize
    leftSwap = !compareFunction(leftCursor, pivotCursor);
    rightSwap = compareFunction(rightCursor, pivotCursor);
    if (leftSwap && rightSwap) {
        swap(leftCursor, rightCursor, dataSize);
    }
    else if ((leftSwap) && (leftIdx != pivot)) {
        if (leftIdx == 0) {
            swap(leftCursor, pivotCursor, dataSize);
        }
        else {
            leftIdx--;
            rightIdx--;
            leftCursor = (char*)leftCursor - dataSize;
            rightCursor = (char*)rightCursor - dataSize;
        }
    }
    else if ((rightSwap) && (rightIdx != pivot)) {
        if (rightIdx == length - 1) {
            swap(pivotCursor, rightCursor, dataSize);
        }
        else {
            leftIdx++;
            rightIdx++;
            leftCursor = (char*)leftCursor + dataSize;
            rightCursor = (char*)rightCursor + dataSize;
        }
    }
    //Once it has been pre-sorted, partition and recurse
    //Left
    partition(array, rightIdx, dataSize, pivotMethod);
    //Right
    partition(rightCursor, length - rightIdx, dataSize, pivotMethod);

    return array;
}

void* quicksort(void* array, unsigned int arrLength, size_t dataSize, int (*compFun)(void*, void*), PivotSelect pivotMethod) {
    if (arrLength < 2) {
        return NULL;
    }
    if (compFun == NULL) {
        return NULL;
    }

    compareFunction = compFun;
    partition(array, arrLength, dataSize, pivotMethod);

    return array;
}