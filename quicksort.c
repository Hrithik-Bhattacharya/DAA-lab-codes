#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to handle the swapping logic and pivot placement
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Internal recursive quicksort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Required wrapper function
void sort(int arr[], int n) {
    quicksort(arr, 0, n - 1);
}

// Linear search for duplicates in a presorted array
int check(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) return 1;
    }
    return 0;
}

int main() {
    printf("%-10s | %-12s | %-12s\n", "Size", "Sort (s)", "Search (s)");
    printf("-----------------------------------------\n");

    for (int n = 1000; n <= 10000; n += 1000) {
        int *arr = malloc(n * sizeof(int));
        // Fill with random values
        for (int i = 0; i < n; i++) arr[i] = rand() % (n * 2);

        // Measure Sort Time
        clock_t start_s = clock();
        sort(arr, n);
        double time_sort = (double)(clock() - start_s) / CLOCKS_PER_SEC;

        // Measure Search Time (presorted)
        clock_t start_c = clock();
        check(arr, n);
        double time_search = (double)(clock() - start_c) / CLOCKS_PER_SEC;

        printf("%-10d | %-12.6f | %-12.6f\n", n, time_sort, time_search);
       
        free(arr);
    }
    return 0;
}
