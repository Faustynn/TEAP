
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
} Array;

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

// find min segments with recursion
int minSegments(Array arr, int start, int end, MemoTable* table) {
    // we haave less than 3 elements
    if (end - start < 3) {
        return end - start;
    }

    // stop?
    if (table->calculated[start][end]) {
        return table->memo[start][end];
    }

    // start reslt. val
    int result = INT_MAX;

    for (int i = start+2; i <= end; i++) {
        for (int j = start; j < i - 1; j++) {
            // check that we can split arr.
            if (abs(arr.values[j] - arr.values[i - 1]) >= arr.k) {

                // split cost
                int leftSegments = (int)floor((j - start + 1) / 2.0);
                int rightSegments = (int)ceil((end - j - 1) / 2.0);
                int cost = leftSegments + rightSegments + 1;

                // its less then previos?
                if (cost < result) {
                    result = cost;
                }
            }
        }
    }

    // we cant split so we take end-start
    if (result == INT_MAX) {
        result = end - start;
    }

    // save reslt. in memo table
    table->memo[start][end] = result;
    table->calculated[start][end] = true;

    return result;
}

int main() {
    int n, k;

    while (scanf("%d %d", &n, &k) > 0) {
        Array arr;
        arr.size = n;
        arr.k = k;
        arr.values = (int*)calloc(n, sizeof(int));


        for (int i = 0; i < n; i++) {
            scanf("%d", &arr.values[i]);
        }


        if (n < 3) {
            printf("%d\n", n);
            free(arr.values);
            continue;
        }

        MemoTable table = initMemoTable(n);

        int result = minSegments(arr, 0, n, &table);
        printf("%d\n", result);


        // free memory
        freeMemoTable(table, n);
        free(arr.values);
    }

    return 0;
}