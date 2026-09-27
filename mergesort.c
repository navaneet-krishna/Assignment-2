/*
 * MergeSort implementation for fixed-length ID sorting
 * Social media application - sorting 3-digit IDs
 * Records array contents after every merge (combine) step.
 */
#include <stdio.h>

int comparisons = 0;   // count of key comparisons
int mergeCalls = 0;    // count of merge (combine) operations

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[100], R[100];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }

    mergeCalls++;
    printf("Merge #%d  (indices %d..%d, mid=%d) -> subarray: ", mergeCalls, l, r, m);
    for (int p = l; p <= r; p++) printf("%d ", arr[p]);
    printf("\n");
}

void mergeSort(int arr[], int l, int r, int fullArr[], int n) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, fullArr, n);
        mergeSort(arr, m + 1, r, fullArr, n);
        merge(arr, l, m, r);
        printf("   --> Full array now: ");
        printArray(fullArr, n);
    }
}

int main() {
    int arr[] = {324, 125, 456, 218, 102, 389, 275, 147};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== MergeSort Execution Trace ===\n");
    printf("Initial array: ");
    printArray(arr, n);
    printf("\n");

    mergeSort(arr, 0, n - 1, arr, n);

    printf("\nFinal sorted array: ");
    printArray(arr, n);

    printf("\n--- Performance Metrics ---\n");
    printf("Total comparisons: %d\n", comparisons);
    printf("Total merge operations (passes): %d\n", mergeCalls);

    return 0;
}
