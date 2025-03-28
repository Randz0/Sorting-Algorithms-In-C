#include <stdio.h>
#include <stdlib.h>

// Macros for booleans. Exist purely for readability of code since TRUE is a lot more obvious than 1 or similarly how FALSE = 0
#define boolean unsigned char
#define TRUE 1
#define FALSE 0

const float InverseRand = 1.0f / RAND_MAX;

// Does not initialize the seed of the system rand function, must be done seperately
int GetRandomIntFromRange(int min, int max) {
    return (int)(rand() * InverseRand * (max - min) + min);
}

// Generates a pseudo-randomized array to use for testing purposes
// Returns a pointer to the first index
int* GetRandomizedArr(int length) {
    int* returnedArray = malloc(sizeof(int) * length);
    
    for (int i = 0; i < length; i++) {
        returnedArray[i] = GetRandomIntFromRange(0, 10000);
    }

    return returnedArray;
}

void PrintIntArray(int* toPrint, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d \n", toPrint[i]);
    }
}

void PrintBoolArray(boolean* toPrint, int length) {
    for (int i = 0; i < length; i++) { 
        printf("%d \n", toPrint[i]);
    }
}

// Returns a copy of an integer array from another
int* CopyIntArray(int* copying, int length) {
    int* copy = malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++) {
        copy[i] = copying[i]; // Copying the individual values
    }

    return copy;
}

// Sorts the given array using a bubble sort algorithm
int* BubbleSort(int* toSort, int length) {
    int* returnedCopy = CopyIntArray(toSort, length);

    boolean isSorted = FALSE;
    int temp; // Used when actually swapping

    while (isSorted == FALSE) {
        isSorted = TRUE;

        for (int i = length - 1; i >= 0; i--) { // Only check for swaps up to the second to last element since there's no +1 element to swap with the last one
            if (returnedCopy[i] <= returnedCopy[i + 1]) {
                continue; // Elements are sorted keep going
            }

            temp = returnedCopy[i]; // storing the value that will be overwritten
            returnedCopy[i] = returnedCopy[i + 1];
            returnedCopy[i + 1] = temp; // Swapping the two values to put then in order

            isSorted = FALSE;
        }
    }

    return returnedCopy;
}

// Similar to bubble sort but with some optimization to the algorithm
int* CocktailShakerSort(int* toSort, int length) {
    int* returnedCopy = CopyIntArray(toSort, length);

    boolean sorted = FALSE;
    int passes = 0;

    while (sorted == FALSE) {
        sorted = TRUE;
        
        for (int i = passes; i < length - passes - 1; i++) {
            if (returnedCopy[i] < returnedCopy[i + 1]) {
                continue;
            }

            sorted = FALSE;
            
            returnedCopy[i] = returnedCopy[i] ^ returnedCopy[i + 1]; // Swaps the values if they were out of order
            returnedCopy[i + 1] = returnedCopy[i] ^ returnedCopy[i + 1];
            returnedCopy[i] = returnedCopy[i] ^ returnedCopy[i + 1];

        } // Sorting up the array

        for (int i = length - 1 - passes; i > 0; i--) {
            if (returnedCopy[i] > returnedCopy[i - 1]) {
                continue;
            }

            sorted = FALSE;

            returnedCopy[i] = returnedCopy[i] ^ returnedCopy[i - 1]; // Swaps the values if they were out of order
            returnedCopy[i - 1] = returnedCopy[i] ^ returnedCopy[i - 1];
            returnedCopy[i] = returnedCopy[i] ^ returnedCopy[i - 1];
        
        } // Sorting down the array

        passes += 1;
    }

    return returnedCopy;
}

// Inserts and element from one array position into another, effectively pushing the values up the array
// Makes the assumption that the parameter from is > than where
// inserting : The array with elements being pushed through
void PushElement(int from, int where, int* inserting) {
    if (from == where) {
        return; // Nothing to insert
    }

    int pushNext = inserting[where];
    int temp;

    for (int pushingIndex = where; pushingIndex < from; pushingIndex++) {
        // Push the value into the next index
        temp = inserting[pushingIndex + 1]; // Store next value that will be pushed
        inserting[pushingIndex + 1] = pushNext; // Push the current value up

        pushNext = temp; // Swap the current value for the next value to be pushed
    }

    inserting[where] = pushNext;
}

// Exact same functionality except for boolean arrays
void PushElementBool(int from, int where, boolean* inserting) {
    if (from == where) {
        return; // Nothing to insert
    }

    boolean pushNext = inserting[where];
    boolean temp;

    for (int pushingIndex = where; pushingIndex < from; pushingIndex++) {
        // Push the value into the next index
        temp = inserting[pushingIndex + 1]; // Store next value that will be pushed
        inserting[pushingIndex + 1] = pushNext; // Push the current value up

        pushNext = temp; // Swap the current value for the next value to be pushed
    }

    inserting[where] = pushNext;
}

// Sorts the given array using an insertion sort algorithm
int* InsertionSort(int* toSort, int length) {
    int* returnedCopy = CopyIntArray(toSort, length);

    for (int i = 1; i < length; i++) { // i denotes which element is being inserted
        
        for (int j = 0; j < i; j++) { // Scrolling through the sorted portion

            if (returnedCopy[i] > returnedCopy[j]) {
                continue;
            }            

            // found the insertion index
            PushElement(i, j, returnedCopy);

            break;
        }
    }

    return returnedCopy;
}

// Sorts the given array using selection sort, sorting by minimums
int* SelectionSort(int* toSort, int length) {
    int* returnedCopy = CopyIntArray(toSort, length);

    int foundMinimum; // Index of the minimum found value
    int temp;

    for (int i = 0; i < length; i++) { // i denotes which element is to be filled next
        foundMinimum = i;

        for (int j = i + 1; j < length; j++) { // Finding the min from the rest of the array
            if (returnedCopy[foundMinimum] > returnedCopy[j]) {
                foundMinimum = j;
            }
        }

        temp = returnedCopy[i];

        returnedCopy[i] = returnedCopy[foundMinimum];
        returnedCopy[foundMinimum] = temp;
    }

    return returnedCopy;
}

// Creates an array labeled partitions used by some of the algorithms to store the status of elements in the array
boolean* GetInitialPartitions(int length) {
    boolean* partitions = malloc(sizeof(boolean) * length);

    for(int i = 0; i < length; i++) {
        partitions[i] = TRUE; // Set all the values initially to be partitions
    }
    
    return partitions;
}

// Returns the index of the 2nd Array in the next pair
// Also sets the index automatically to the first index in what will be merged next
void GetNextMergePair(boolean* partitions, int length, int* nextIndex, int* currentIndex) {
    (*currentIndex)++;
    
    while (*currentIndex < length) {
        if (partitions[*currentIndex] == FALSE) { 
            (*currentIndex)++;
            continue;
        }

        // Found next partition

        partitions[*currentIndex] = FALSE; // Will be merged so don't flag it as a partition
        *nextIndex = *currentIndex; // Setting the 2nd index parameter

        while (*currentIndex < length) {
            if (partitions[*currentIndex] == TRUE) {
                return; // current index has been properly set
            }

            (*currentIndex)++;
        }

        (*currentIndex) = 0;

        return;
    }

    // Tldr, no pair exist to merge with
    (*currentIndex) = 0;
}

// Returns if the merge sort operation is complete
boolean CheckMergeSorted(boolean* partitions, int length) {
    for (int i = 1; i < length; i++) { // only the first index should be a partition once sorted
        if (partitions[i] == TRUE) {
            return FALSE;
        }
    }

    return TRUE;
}

void MergeNextPair(int firstStartIndex, int secondStartIndex, int secondLength, int* mergingArr) {
    int inserted = 0;
    
    int insertingWhereIndex = firstStartIndex;
    int insertingFromIndex = 0;

    while (inserted < secondLength && insertingWhereIndex < (secondStartIndex + secondLength) ) {
        insertingFromIndex = secondStartIndex + inserted;

        if (mergingArr[insertingWhereIndex] > mergingArr[insertingFromIndex]) {
            PushElement(insertingFromIndex, insertingWhereIndex, mergingArr);

            inserted++;
        }

        insertingWhereIndex++;
    }
}

int* MergeSort(int* toSort, int length) {
    int* returnedCopy = CopyIntArray(toSort, length);
    boolean* partitions = GetInitialPartitions(length);    
    
    int currentIndex = 0;

    int firstIndex = currentIndex; 
    int* secondIndex = malloc(sizeof(int));
    
    while (!CheckMergeSorted(partitions, length)) {
        while (TRUE) {
            GetNextMergePair(partitions, length, secondIndex, &currentIndex);

            if (currentIndex == 0) { // Merge the Last Grouping, Needs to determine if there is an uneven merge at the end or if the element is solo
                if ( firstIndex <= *secondIndex) { // The program knows that a group exist
                    MergeNextPair(firstIndex, *secondIndex, length - *secondIndex, returnedCopy);
                }

                firstIndex = currentIndex;

                break;
            }

            MergeNextPair(firstIndex, *secondIndex, currentIndex - *secondIndex, returnedCopy);

            firstIndex = currentIndex;
        }
    }

    free(partitions);
    free(secondIndex);
    
    partitions = NULL;
    secondIndex = NULL;

    return returnedCopy;
}

boolean CheckQuickSorted(boolean* partitions, int length) {
    for (int i = 0; i < length; i++) {
        if (partitions[i]) { // True indicates that the element has not been chosen as a pivot yet
            return FALSE;
        }
    }

    return TRUE;
}

// Similar to the merge sort implementation however in quicksort we
// simply search for the next uninterupted sequence with no pivot
// startIndex : out pointer that stores the starting index of the found sequence
// endIndex : out pointer that stores the ending index of the found sequence
// When starting the process of extracting the sub array's, the start index need not be reassigned, only that end index = -2 (indicates that the next sequenece starts at 0)
void GetNextQuicksortSubArray(boolean* partitions, int length, int* startIndex, int* endIndex) {
    *startIndex = *endIndex + 1; // Initially the next sequenece starts right after where the last left off, after the pivot the comes after the end index
    
    for (int i = *startIndex; i < length; i++) {
        if (!partitions[i]) { // The index is a pivot, should not be made a starting index
            continue;
        }

        // start index located
        
        *startIndex = i; // Sub array continues right up until before it

        goto foundStartIndex;
    }

    *startIndex = -1;
    return; // Couldn't find a starting index, starting index not indicates to move to the next loop over

    foundStartIndex:

    for (int i = *startIndex; i < length; i++) {
        if (partitions[i]) { // Index is not a pivot, should not mark the end
            continue;
        }

        *endIndex = i - 1; // choose the index right before the pivot

        return;
    }

    // reached the end of the array without meeting another pivot
    *endIndex = length - 1;
}

int GetFirstNonPivotedIndex(boolean* partitions, int length) {
    for (int i = 0; i < length; i++) {
        if (partitions[i]) {
            return i;
        }
    }
}

// Given a sub array of the main array, performs an iteration of quick sort
// Choses a pivot and sorts elements in the sub array around the pivot
void IterateQuicksortOnSubArray(int* toSort, int startingIndex, int endingIndex, int pivotIndex, boolean* partitions) {
    if (startingIndex == endingIndex) {
        partitions[startingIndex] = FALSE;
        return;
    }
    
    int temp = toSort[startingIndex];

    toSort[startingIndex] = toSort[pivotIndex];
    toSort[pivotIndex] = temp;
    // Doing this to make the pushing function works since it can only move elements down the array

    int debugPivotValue = toSort[startingIndex];

    int sortedUnderPivot = 0; // Tells where the system needs to insert elements
    for (int sortingIndex = startingIndex + 1; sortingIndex <= endingIndex; sortingIndex++) { // Going down the array
        if (toSort[sortingIndex] < toSort[startingIndex + sortedUnderPivot]) {
            PushElement(sortingIndex, startingIndex, toSort); // Push the element to the start
            PushElementBool(sortingIndex, startingIndex, partitions); // Do the same for the partitions

            sortedUnderPivot++;
        }
        else {
            PushElement(sortingIndex, startingIndex + sortedUnderPivot + 1, toSort); // Push the value one ahead of the pivot
            PushElementBool(sortingIndex, startingIndex + sortedUnderPivot + 1, partitions);
        }
    }

    partitions[startingIndex + sortedUnderPivot] = FALSE; // No longer un-pivoted
}

int* QuickSort(int* toSort, int length) {
    int* returnedCopy = CopyIntArray(toSort, length);
    boolean* partitions = GetInitialPartitions(length); // True indicates the value has not been chosen as a pivot yet

    int startingIndex;
    int endingIndex;

    while (!CheckQuickSorted(partitions, length)) {
        startingIndex = 0;
        endingIndex = -1;

        while (TRUE) {
            GetNextQuicksortSubArray(partitions, length, &startingIndex, &endingIndex);

            if (startingIndex == -1) { // Found all possible sub-arrays
                break;
            }

            IterateQuicksortOnSubArray(returnedCopy, startingIndex, endingIndex, (startingIndex + endingIndex) * 0.5f, partitions);
        }
    }

    free(partitions);
    return returnedCopy;
}

const int randArrLength = 1000;

int main() {
    int* instance = GetRandomizedArr(randArrLength);

    int* sorted = QuickSort(instance, randArrLength);
    PrintIntArray(sorted, randArrLength);

    getchar();

    free(sorted); // The allocated array needs to be freed
    
    sorted = NULL;

    return 0;
}
