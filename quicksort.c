/*
 * QuickSort implementation for fixed-length ID sorting
 * Social media application - sorting 3-digit IDs
 * Uses last element as pivot (Lomuto partition scheme).
 * Records partition results and final sorted sequence.
 */
#include <stdio.h>

int comparisons = 0;
int partitionCalls = 0;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

int partition(int arr[], int low, int high, int n) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    partitionCalls++;
    printf("Partition #%d (low=%d, high=%d, pivot=%d) -> pivot placed at index %d\n",
           partitionCalls, low, high, pivot, i + 1);
    printf("   Array after partition: ");
    printArray(arr, n);

    return i + 1;
}

void quickSort(int arr[], int low, int high, int n) {
    if (low < high) {
        int pi = partition(arr, low, high, n);
        quickSort(arr, low, pi - 1, n);
        quickSort(arr, pi + 1, high, n);
    }
}

int main() {
    int arr[] = {324, 125, 456, 218, 102, 389, 275, 147};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== QuickSort Execution Trace ===\n");
    printf("Initial array: ");
    printArray(arr, n);
    printf("\n");

    quickSort(arr, 0, n - 1, n);

    printf("\nFinal sorted sequence: ");
    printArray(arr, n);

    printf("\n--- Performance Metrics ---\n");
    printf("Total comparisons: %d\n", comparisons);
    printf("Total partition operations: %d\n", partitionCalls);

    return 0;
}
