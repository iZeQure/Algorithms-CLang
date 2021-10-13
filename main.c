#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 20000
#define LEN 5
#define POPULATION_MAX_RANGE 1000000

void run_me(void);
void swap(int *x, int *y);
void createArray(int *array, int length);
void printArray(int *array, int length);
void printArrayRange(int *begin, int *end);
void quicksort(int *begin, int *end);

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

    populate_array((int **) numbers, ARRAY_LENGTH);
    clock_t t = clock();

    merge_sort_algorithm((int **) numbers, 0, ARRAY_LENGTH);

    t = clock() - t;
    double time = ((double)t) / CLOCKS_PER_SEC;
    printf("Finished in %f seconds.\n", time);

    clock_t t2 = clock();

    run_me();

    t = clock() - t;
    double time2 = ((double)t) / CLOCKS_PER_SEC;
    printf("Finished in %f seconds.\n", time2);

    return 0;
}

void run_me( void)
{
    int array[LEN];
    createArray(&array, LEN);
    printf("Array made\n");
    printArray(&array, LEN);
    int *begin, *end;
    begin = &array;
    end = begin + LEN - 1;
    quicksort(begin, end);
    printArray(array, LEN);
}

void quicksort(int *begin, int *end)
{
    printf("New call, array to sort:\n");
    printArrayRange(begin, end);
    if(begin >= end) return; //there is one or less to sort
    int *p1, *p2;
    p1 = begin;
    p2 = end;
    if((p2-p1)==1)
    {
        if(*p1>*p2)
        {
            swap(p1, p2);
            printArrayRange(begin, end);
        }
        return;
    }
    int *pivot;
    pivot = p1+((p2-p1)/2);
    int middle = *pivot;
    printf("middle: %d, starting sorting\n", *pivot);
    while(p1<p2)
    {
        if(*p1 < middle) p1++;
        else if(*p2 > middle) p2--;
        else
        {
            swap(p1, p2);
            p1++;
            printArrayRange(begin, end);
        }
    }
    if(*p1 >= middle) p1--;
    printArrayRange(begin, end);
    printf("done sorting\n");
    quicksort(begin, p1);
    p1++;
    quicksort(p1, end);
    return;
}


void swap(int *x, int *y) { // omskift int på plads x med int på plads y
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
void createArray(int *array, int length)
{
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0 ; i < length ; i++ )
    {
        array[i] = rand() % 50;
    }
}
void printArray(int *array, int length)
{
    int *ptr = array;
    for(int i = 0 ; i < length ; i++ )
    {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n");
}
void printArrayRange(int *begin, int *end)
{
    int *ptr = begin;
    while(ptr <= end)
    {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n");
}


