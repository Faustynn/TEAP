// uloha-8-1.c -- Nazar Meredov, 2025-03-21 12:06

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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


bool canSeatFriends(int friends[], int N, int tables[], int M) {
    // sort arrs in desc.
    mergeSort(friends, 0, N-1);
    mergeSort(tables, 0, M-1);

    // if people more than tables
    if (friends[N-1] > M) {
        return false;
    }


    int totalFriends = 0;
    int totalSeats = 0;

    for (int i = 0; i < N; i++) {
        totalFriends += friends[i];
    }

    for (int i = 0; i < M; i++) {
        totalSeats += tables[i];
    }

    if (totalFriends > totalSeats) {
        return false;
    }

    // lets place friends starting from the largest groups
    // For each group take Ni with the largest number where free seat
    for (int i = N-1; i >= 0; i--) {
        mergeSort(tables, 0, M-1); // sort tables in asc.
        // Reverse tables to make it desc.
        for (int j = 0; j < M/2; j++) {
            int temp = tables[j];
            tables[j] = tables[M-1-j];
            tables[M-1-j] = temp;
        }

        // can we place all friends from this group?
        for (int j = 0; j < friends[i]; j++) {
            if (j >= M || tables[j] <= 0) {
                return false;
            }
            tables[j]--;
        }
    }

    return true;
}

int main() {
    int N, M;
    int* friends = NULL;
    int* tables = NULL;

    while (scanf("%d %d", &N, &M) == 2) {
        if (N < 1 || N > 100 || M < 1 || M > 100) {
            printf("Error N a M\n");
            continue;
        }

        friends = (int*)malloc(N * sizeof(int));
        tables = (int*)malloc(M * sizeof(int));

        if (friends == NULL || tables == NULL) {
            printf("Memory allocation failed\n");
            free(friends);
            free(tables);
            continue;
        }

        bool valid = true;
        for (int i = 0; i < N; i++) {
            if (scanf("%d", &friends[i]) != 1 || friends[i] < 1 || friends[i] > 100) {
                printf("Error Ni\n");
                valid = false;
                break;
            }
        }

        if (!valid) {
            free(friends);
            free(tables);
            continue;
        }


        for (int i = 0; i < M; i++) {
            if (scanf("%d", &tables[i]) != 1 || tables[i] < 2 || tables[i] > 100) {
                printf("Error Mi\n");
                valid = false;
                break;
            }
        }

        if (!valid) {
            free(friends);
            free(tables);
            continue;
        }

        printf("%d\n", canSeatFriends(friends, N, tables, M) ? 1 : 0);

        free(friends);
        free(tables);
    }

    return 0;
}