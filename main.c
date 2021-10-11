#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 20000
#define POPULATION_MAX_RANGE 1000000

void string_reverse(char *rawStr) {
    int len; char temp;
    len = strlen(rawStr);

    for (int i = 0; i < len / 2; ++i) {
        temp = rawStr[i];
        rawStr[i] = rawStr[len - i - 1];
        rawStr[len - i  - 1] = temp;
    }

    printf("Reverse: %s Address: %p", rawStr, &rawStr);
}

/*
 * Swaps two values.
 * param arr: Is the set array to swap certain values.
 * param posX: defines the first position in the array, to be swapped.
 * param posY: defines the second position in the array, to be swapped.*/
void swap_values(int *arr[], int posX, int posY) {
    int temp = arr[posX];
    arr[posX] = arr[posY];
    arr[posY] = temp;
}

void merge(int *arr[], int posX, int middle, int posY) {
    int pX, pY, i;
    int temp[ARRAY_LENGTH];

    for (pX = posX,
        pY = middle + 1,
        i = posX;
        pX <= middle && pY <= posY;
        i++) {
        if (arr[pX] <= arr[pY]) {
            temp[i] = (int) arr[pX++];
        }
        else {
            temp[i] = (int) arr[pY++];
        }
    }

    while (pX <= middle) {
        temp[i++] = (int) arr[pX++];
    }

    while (pY <= posY) {
        temp[i++] = (int) arr[pY++];
    }

    for (i = posX; i <= posY; i++) {
        arr[i] = (int *) temp[i];
    }
}

/*
 * Selection Sort Algorithm.
 * */
void selection_sort(int *arr[], int n) {
    for (int i = 0; i < n; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        swap_values(arr, i, min_index);
    }
}

/*
 * Insertion Sort Algorithm.
 * */
void insertion_sort(int *arr[], int n) {
    for (int i = 0; i < n; ++i) {
        int j = i;
        while (j > 0 && arr[j-1] > arr[j]) {
            swap_values(arr, j, j - 1);
            j = j -1;
        }
    }
}

/*
 * Merge Sort Algorithm.
 * */
void merge_sort_algorithm(int *arr[], int posX, int posY) {
    if (posY <= posX) {
        return;
    }

    int middle = (posX + posY) / 2;

    merge_sort_algorithm(arr, posX, middle);
    merge_sort_algorithm(arr, (middle + 1), posY);

    merge(arr, posX, middle, posY);
}

/*
 * Populates an array with integers.
 * param *arr[]: defines an empty array with type integer.
 * param n: defines the size of the array.
 * */
void populate_array(int *arr[], int n) {
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < n; ++i) {
        int r = rand() % POPULATION_MAX_RANGE; // NOLINT(cert-msc30-c, cert-msc50-cpp)
        arr[i] = (int *) r;
    }
}

int main(void) {
    int numbers[ARRAY_LENGTH];

    // Fill the array with random integers.
    populate_array((int **) numbers, ARRAY_LENGTH);
//    printf("Array is filled with data.\n");

//    printf("Starting benchmarks!\n");
    clock_t t = clock();
//    printf("Clock started.\n");

    // Sort array after the selection sort algorithm.
//    selection_sort((int **) numbers, ARRAY_LENGTH)
    merge_sort_algorithm((int **) numbers, 0, ARRAY_LENGTH);
//    printf("Array sorted with Selected Algorithm.\n");

    t = clock() - t;
    double time = ((double)t) / CLOCKS_PER_SEC;
    printf("Finished in %f seconds.\n", time);

//    printf("Sorted: \n");
//    for (int i = 0; i < ARRAY_LENGTH; ++i) {
//        printf(" %-4d ", numbers[i]);
//    }

    return 0;
}
