#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int readFileToArray(int argc, char *argv[], int **array); 
void printArray(int array[], int size);

// Function to swap two elements in an array
void swap(int array[], int index1, int index2) {
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

// Function to find the index of the smallest element in a subarray
int findSmallestElementIndex(int subarray[], int size, int startIndex) {
    int smallestElement = subarray[startIndex];
    int smallestIndex = startIndex;
    
    // Iterate through the subarray to find the smallest element
    for (int i = startIndex; i < size; i++) {
        if (smallestElement > subarray[i]) {
            smallestElement = subarray[i];
            smallestIndex = i;
        }
    }
    return smallestIndex;
}

// Function to perform selection sort on an array
void selectionSort(int array[], int size) {
    int subarrayStartIndex, minIndex;
    
    // Iterate through the array and select the smallest element from the remaining unsorted subarray
    for (subarrayStartIndex = 0; subarrayStartIndex < size; subarrayStartIndex++) {
        // Find the index of the smallest element in the unsorted subarray
        minIndex = findSmallestElementIndex(array, size, subarrayStartIndex);
        
        // Swap the smallest element with the first element of the unsorted subarray
        swap(array, minIndex, subarrayStartIndex);
    }
}

int main(int argc, char *argv[]) {
    // int array[] = {15, 29, 37, 14, 7, 48, 22, 5, 12, 31, 9, 42, 18, 25, 2, 39, 33, 21, 11, 27, 36, 8, 16, 4, 19, 23, 35, 6, 17, 10};
    int *array = NULL;
    int size = readFileToArray(argc, argv, &array);
    
    // Sort the array using selection sort
    clock_t start, end;

    start = clock();
    selectionSort(array, size);
    end = clock();
    
    // Print the sorted array
    #ifdef PRINTARRAY
    printArray(array, size);
    #endif

    printf("Selection sort Tics : %lu", end-start);
}

// Function to print the elements of an array
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

int readFileToArray(int argc, char *argv[], int **array) {
    if (argv[1] == NULL) {
        printf("File must be provided on the command line...exiting\n");
        exit(0);
    }
    else {
        char *fileName = argv[1];
        int num;
        int count = 0;
        FILE *file = fopen(fileName, "r");
        char line[100];

        while (fgets(line, sizeof(line), file) != NULL) {
            count++;
        }

        fseek(file, 0, SEEK_SET);

        *array = malloc(count * sizeof(int));
        int i;
        for (i = 0; i < count; i++) {
            fgets(line, sizeof(line), file);
            num = atoi(line);
            (*array)[i] = num;
        }

        fclose(file);
        return count;
    }
}