#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926535f
#define HALF_PI 1.5707963f

// Macro booleans
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

// Returns a copy of an integer array from another
int* CopyIntArray(int* copying, int length) {
    int* copy = malloc(sizeof(int*) * length);

    for (int i = 0; i < length; i++) {
        *(copy + i) = *(copying + i); // Copying the individual values
    }

    return copy;
}

int* BubbleSort(int* toSort, int length) {
    int* returnedCopy = CopyIntArray(toSort, length);

    boolean isSorted = FALSE; // 1 = Sorted, 0 = Unsorted

    while (isSorted == FALSE) {
        isSorted = TRUE;

        for (int i = 0; i < length - 1; i++) { // Only check for swaps up to the second to last element
            if ( *(returnedCopy + i) <= *(returnedCopy + i + 1)) {
                continue; // Elements are sorted keep going
            }

            int temp = *(returnedCopy + i); // storing the value that will be overwritten
            *(returnedCopy + i) = *(returnedCopy + i + 1);
            *(returnedCopy + i + 1) = temp; // Swapping the two values to put then in order

            isSorted = FALSE;
        }
    }

    return returnedCopy;
}

void PrintIntArray(int* toPrint, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d \n", *(toPrint + i));
    }
}

int main() {
    int instance[4] = {4, 3, 2, 1};
    int length = sizeof(instance) / sizeof(instance[0]);

    int* sorted = BubbleSort(instance, length);
    PrintIntArray(sorted, length);

    getchar();

    free(sorted); // The allocated array needs to be freed
    sorted = NULL;

    return 0;
}