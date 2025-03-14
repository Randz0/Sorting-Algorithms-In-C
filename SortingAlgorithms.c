#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926535f
#define HALF_PI 1.5707963f

// Macros for booleans. Very convienient
#define boolean unsigned char
#define TRUE 1
#define FALSE 0

// Really fast and decently precise approximation of sine on the interval -pi /2 to pi / 2
float TaylorApprox(float value) {
    float sqrd = value * value;

    return value * (1 - 0.1666666f * sqrd * (1 - 0.05f * sqrd * (1 - 0.02381f * sqrd) ) );
}

// Does some value clamping before giving the value
float QuickSin(float value) {
    if (value < 0) {
        value *= -1;
    } // flip the value

    while (value > HALF_PI) {
        value -= PI;
    } // Essentially getting the value within bounds

    return TaylorApprox(value);
}

void PrintIntArray(int* toPrint, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d \n", *(toPrint + i));
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

// Handles the insertion part of the Insertion Sort Algorithm
void InsertElement(int from, int where, int* inserting) {
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

// Sorts the given array using an insertion sort algorithm
int* InsertionSort(int* toSort, int length) {
    int* returnedCopy = CopyIntArray(toSort, length);

    for (int i = 1; i < length; i++) { // i denotes which element is being inserted
        
        for (int j = 0; j < i; j++) { // Scrolling through the sorted portion

            if (returnedCopy[i] > returnedCopy[j]) {
                continue;
            }            

            // found the insertion index
            InsertElement(i, j, returnedCopy);

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

int main() {
    int instance[7] = {10, 7, 6, 3, 5, 4, 22};
    int length = sizeof(instance) / sizeof(instance[0]);

    int* sorted = SelectionSort(instance, length);

    PrintIntArray(sorted, length);

    getchar();

    free(sorted); // The allocated array needs to be freed
    sorted = NULL;

    return 0;
}
