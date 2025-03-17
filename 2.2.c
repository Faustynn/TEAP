// uloha-2-2.c -- Nazar Meredov, 2025-03-17 00:49

//
// Created by Nazar Meredov on 24/02/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define IMP "IMPOSSIBLE\n"

int calculate(char* line, int len, int sum);

int main(void) {
    char* line = NULL;
    int sum;

    line = (char*)malloc(11 * sizeof(char));

    //scanf loop
    while(scanf("%s %d", line, &sum) == 2) {
        int len = strlen(line);

        if(len < 1 || len > 10) {
            printf("Error\n");
            continue;
        }else{
            int sum_numb = calculate(line, len,sum);

            if(sum_numb != -1) {
                printf("%d\n", sum_numb);
            } else {
                printf(IMP);
            }
        }
    }
    free(line);
    return 0;
}

int calculate(char* line, int len, int sum) {
    int dp[11][1000];

    // init dp with -1 value
    for (int i = 0; i <= len; i++) {
        for (int j = 0; j <= sum; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[0][0] = 0; // 0 sum with 0 numbrs

    // main alg, with dynamic programming and Claude stability implementation
    for (int i = 1; i <= len; i++) { // from 1 to len
        for (int j = 1; j <= i; j++) {
            char substring[11];
            strncpy(substring, &line[i - j], j);
            substring[j] = '\0';
            long long numb = strtoll(substring, NULL, 10);

            if (numb > sum) continue; //if number is too large for sum

            if (i == j) {
                dp[i][numb] = 0; // first number = sum 0
            }

            for (int k = 0; k <= sum - numb; k++) {
                if (dp[i - j][k] != INT_MAX) {
                    if (dp[i][k + numb] < dp[i - j][k] + (i - j > 0 ? 1 : 0)) {
                        dp[i][k + numb] = dp[i][k + numb];
                    } else {
                        dp[i][k + numb] = dp[i - j][k] + (i - j > 0 ? 1 : 0);
                    }                }
            }
        }
    }

    if(dp[len][sum] == INT_MAX) {
        return -1;
    }else{
        return dp[len][sum];
    }
}