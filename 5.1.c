#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

// From https://www.geeksforgeeks.org/c-program-for-merge-sort/
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// The subarray to be sorted is in the index range [left-right]
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int greedy_upgr(int* U_i, int N, int K);

int main(void) {
    int N, K;
    int* U_i;

    while (scanf("%d %d", &N, &K) == 2) {
        if (N < 1 || N > 50 || K < 0 || K > 1000) {
            printf("Error\n");
            continue;
        }

        U_i = (int*)malloc(N * sizeof(int));
        bool valid = true;
        for (int i = 0; i < N; i++) {
            if (scanf("%d", &U_i[i]) != 1) {
                printf("Error\n");
                valid = false;
                break;
            }

            if (U_i[i] < 1 || U_i[i] > 1000) {
                printf("Error %d\n", U_i[i]);
                valid = false;
                break;
            }
        }
        if (!valid) {
            free(U_i);
            break;
        }

        printf("%d\n", greedy_upgr(U_i, N, K));

        free(U_i);
    }
    return 0;
}

int greedy_upgr(int* arr, int n, int k) {
    if (n < 3) {
        return n;
    }
    mergeSort(arr, 0, n - 1);

    int best = INT_MAX;
    bool found = false;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i - 1; j++) {
            if (abs(arr[j] - arr[i - 1]) >= k) {
                int position = j + 1;

                int left_operations = (int)ceil((position - 1) / 2.0);
                int right_operations = (int)ceil((i - position) / 2.0);
                int operations = left_operations + right_operations + 1;

                if (operations < best) {
                    best = operations;
                    found = true;
                }
            }
        }
        if (found) {
            break;
        }
    }

    if (best == INT_MAX) {
        return n;
    } else {
        return best;
    }
}