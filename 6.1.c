// Created by Nazar Meredov on 24/02/2025.

// uloha-6-1.c -- Nazar Meredov, 2025-03-20 16:23

#include <stdio.h>

void recursive_print(int size, int n, int start, int end, int* arr) {
    if (n == 0) { // stoper for recursion
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]); // print all arr.
        }
        printf("\n");
        return;
    }

    for (int i = start; i <= end; i++) {
        arr[size-n] = i;
        recursive_print(size, n-1, start, end, arr);
    }
}

// strat recursive call for printing
void print(int len, int start, int end) {
    int arr[len];
    recursive_print(len, len, start, end, arr);
}

int main() {
    int N, K;

    // scan input
    while (scanf("%d %d", &N, &K) == 2) {
        if (N == 0 && K == 0) {
            break;
        } else {
            print(N, 1, K);
        }
    }
    return 0;
}
