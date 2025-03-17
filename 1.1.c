// uloha-1-1.c -- Nazar Meredov, 2025-03-15 00:10

//
// Created by Nazar Meredov on 15/03/2025.
//
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




int main(void) {
    int N,K,M;
    int* h;

    //  N K M h[i]
    //  1234 3 4 1000 200 4 30

    //scanf loop
    while(scanf("%d", &N) == 1) {
        scanf("%d %d", &K,&M);

        // lets check barriers
        if (N < 1 || N > 10000 || K < 1 || K > 10000 || M < 1 || M > 10000) {
            printf("Error\n");
            continue;
        }else{
            // alocate memory for cars witch will ride on the bridge
            h = (int*)malloc(M * sizeof(int));

            // put info into arr and check weight limits
            bool valid = true;
            for (int i = 0; i < M; i++) {
                if (scanf("%d", &h[i]) != 1) {
                    printf("Error\n");
                    valid = false;
                    break;
                }

                if (h[i] < 1 || h[i] > 1000) {
                    printf("Error %d\n", h[i]);
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                free(h);
                break;
            }

            // sort it
            mergeSort(h, 0, M-1);
            // Desc
            for(int i=0; i<M/2; i++) {
                int temp = h[i];
                h[i] = h[M-1-i];
                h[M-1-i] = temp;
            }

            // calculate total weight on a bridge
            int total_weight = 0;
            for(int j = 0; j < K && j < M; j++) {
                total_weight += h[j];
            }

            // print results
            if(total_weight<=N){printf("Ano\n");}else
            {printf("Nie\n");}

            free(h);
        }
    }
    return 0;
}