//
// Created by Nazar Meredov on 24/02/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 300
#define MIN 101

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


int main(void) {
    int N;
    int* x;

    //scanf loop
    while(scanf("%d", &N) == 1) {

        // lets check barriers
        if (N < 1 || N > 50) {
            printf("Error\n");
            continue;
        }else{
            // alocate memory for cars witch will ride on the bridge
            x = (int*)malloc(N * sizeof(int));

            // put info into arr and check weight limits
            bool valid = true;
            for (int i = 0; i < N; i++) {
                if (scanf("%d", &x[i]) != 1) {
                    printf("Error\n");
                    valid = false;
                    break;
                }

                if (x[i] < MIN || x[i] > MAX) {
                    printf("Error %d\n", x[i]);
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                free(x);
                break;
            }

            // sort it
            mergeSort(x, 0, N-1);
            // Desc
            for(int i=0; i<N/2; i++) {
                int temp = x[i];
                x[i] = x[N-1-i];
                x[N-1-i] = temp;
            }

            int kamions = 0;
            // bool arr for checking that is used of not
            bool* is_taken = (bool*)calloc(N, sizeof(bool));

            for (int i = 0; i < N; i++) {
                if (is_taken[i]) continue; // this package witch we used
                for (int j = i+1; j < N; j++) {
                    if (is_taken[j]) continue; // this package witch we used

                    if (x[i] + x[j] <= MAX) { // check that sum is less then 300
                        kamions++;
                        is_taken[i] = true; // mark like used
                        is_taken[j] = true;
                        break;
                    }
                }
            }

            for (int i = 0; i < N; i++) { // we have unused packages??
                if (!is_taken[i]) kamions++;
            }

            // print reslts
            printf("%d\n", kamions);


            // free memory
            free(is_taken);
            free(x);
        }
    }
    return 0;
}