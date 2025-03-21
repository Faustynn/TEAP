// uloha-5-1.c -- Nazar Meredov, 2025-03-21 16:33

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

// structure to hold arr.
typedef struct {
    int* values;
    int size;
    int k;
} U_i_struct;

// memo table
typedef struct {
    int** memo;
    bool** calculated;
} MemoTable;

// init memo table with value INT_MAX at start
MemoTable initMemoTable(int n) {
    MemoTable table;

    table.memo = (int**)malloc((n + 1) * sizeof(int*));
    table.calculated = (bool**)malloc((n + 1) * sizeof(bool*));

    for (int i = 0; i <= n; i++) {
        table.memo[i] = (int*)malloc((n + 1) * sizeof(int));
        table.calculated[i] = (bool*)malloc((n + 1) * sizeof(bool));

        for (int j = 0; j <= n; j++) {
            table.memo[i][j] = INT_MAX;
            table.calculated[i][j] = false;
        }
    }

    return table;
}

// free memo table
void freeMemoTable(MemoTable table, int n) {
    for (int i = 0; i <= n; i++) {
        free(table.memo[i]);
        free(table.calculated[i]);
    }
    free(table.memo);
    free(table.calculated);
}

// Check if a segment can be divided
bool canDivide(U_i_struct arr, int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = i + 1; j < end; j++) {
            if (abs(arr.values[i] - arr.values[j]) >= arr.k) {
                return true;
            }
        }
    }
    return false;
}

// find min segments with recursion
int minSegments(U_i_struct arr, int start, int end, MemoTable* table) {
    // Base case: if segment length is less than 3
    if (end - start < 3) {
        return 1;  // Each segment of length 1 or 2 counts as one segment
    }

    // Check memo table
    if (table->calculated[start][end]) {
        return table->memo[start][end];
    }

    // Can't divide this segment further if no pair has difference >= K
    if (!canDivide(arr, start, end)) {
        table->memo[start][end] = 1;
        table->calculated[start][end] = true;
        return 1;
    }

    // Try all possible splits
    int min_result = INT_MAX;
    for (int i = start + 1; i < end; i++) {
        // For each pair of indices where values differ by at least K
        for (int j = start; j < i; j++) {
            for (int k = i; k < end; k++) {
                if (abs(arr.values[j] - arr.values[k]) >= arr.k) {
                    // Calculate minimum segments for left and right parts
                    int left_result = minSegments(arr, start, i, table);
                    int right_result = minSegments(arr, i, end, table);

                    // Update min_result if this split is better
                    int total = left_result + right_result;
                    if (total < min_result) {
                        min_result = total;
                    }
                }
            }
        }
    }

    // If we couldn't find a valid split, this segment counts as one
    if (min_result == INT_MAX) {
        min_result = 1;
    }

    // Save result in memo table
    table->memo[start][end] = min_result;
    table->calculated[start][end] = true;

    return min_result;
}

int main() {
    int N, K;

    while (scanf("%d %d", &N, &K) == 2) {
        if (N < 1 || N > 50 || K < 0 || K > 1000) {
            printf("Error\n");
            continue;
        }
        U_i_struct U_i;
        U_i.size = N;
        U_i.k = K;
        U_i.values = (int*)calloc(N, sizeof(int));

        bool valid = true;
        for (int i = 0; i < N; i++) {
            if (scanf("%d", &U_i.values[i]) != 1) {
                printf("Error\n");
                valid = false;
                break;
            }

            if (U_i.values[i] < 0 || U_i.values[i] > 1000) {
                printf("Error %d\n", U_i.values[i]);
                valid = false;
                break;
            }
        }
        if (!valid) {
            free(U_i.values);
            break;
        }

        if (N < 3) {
            printf("%d\n", 1);  // Changed to 1 since each segment counts as 1
            free(U_i.values);
            continue;
        }

        MemoTable table = initMemoTable(N);

        int result = minSegments(U_i, 0, N, &table);
        printf("%d\n", result);

        // free memory
        freeMemoTable(table, N);
        free(U_i.values);
    }
    return 0;
}