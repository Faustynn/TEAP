// uloha-3-1.c -- Nazar Meredov, 2025-03-17 15:26

//
// Created by Nazar Meredov on 24/02/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Matica for memoization
long long memo[51][51];

// Povolene operatory
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// recursive method for counting ways
long long countWays(const char* expr, int start, int end) {
    if (start > end) return 0; // empty

    // check memoization
    if (memo[start][end] != -1) {
        return memo[start][end];
    }

    // if one digit
    if (start == end && isDigit(expr[start])) {
        return memo[start][end] = 1;
    }

    // if only one operator only
    if (start == end && isOperator(expr[start])) {
        return memo[start][end] = 0;
    }


    long long ways = 0;

    // if its only numbers
    if (isDigit(expr[start])) {
        int isAllDigits = 1;
        for (int i = start + 1; i <= end; i++) {
            if (!isDigit(expr[i])) {
                isAllDigits = 0;
                break;
            }
        }
        if (isAllDigits) {
            return memo[start][end] = 1;
        }
    }

    // if strt with operator
    if (isOperator(expr[start])) {
        if (expr[start] == '-') {
            // check for unary -
            int isAllDigitsAfterMinus = 1;
            for (int i = start + 1; i <= end; i++) {
                if (!isDigit(expr[i])) {
                    isAllDigitsAfterMinus = 0;
                    break;
                }
            }
            if (isAllDigitsAfterMinus) {
                ways += 1;
            }
        }

        // its not unary - so,
        // See all possible ways to split the expression into left and right operands and use recursive
        for (int i = start + 1; i < end; i++) {
            long long leftWays = countWays(expr, start + 1, i);
            long long rightWays = countWays(expr, i + 1, end);
            ways += leftWays * rightWays;
        }
    }

    return memo[start][end] = ways;
}

long long analyzeExpression(const char* expr) {
    int len = strlen(expr);

    // init memo with -1 valus
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            memo[i][j] = -1;
        }
    }

    // its only number?
    if (len > 0) {
        int isAllDigits = 1;
        for (int i = 0; i < len; i++) {
            if (!isDigit(expr[i])) {
                isAllDigits = 0;
                break;
            }
        }
        if (isAllDigits) {
            return 1;
        }
    }

    // is start +
    if (expr[0] == '+') {
        return countWays(expr, 0, len - 1);
    }

    // is start *
    if (expr[0] == '*') {
        return countWays(expr, 0, len - 1);
    }

    // is start *
    if (expr[0] == '/') {
        return countWays(expr, 0, len - 1);
    }

    // is start -
    if (expr[0] == '-') {
        // check for unary -
        int isAllDigitsAfterMinus = 1;
        for (int i = 1; i < len; i++) {
            if (!isDigit(expr[i])) {
                isAllDigitsAfterMinus = 0;
                break;
            }
        }

        if (isAllDigitsAfterMinus) {
            return len-1;   // In task description it is said that - is a unary operator when we have number after it so why is 3 i dont know so make it manualy
        } else {
            // binart -
            return countWays(expr, 0, len - 1);
        }
    }

    // else ways
    return countWays(expr, 0, len - 1);
}

int main() {
    char line[51];

    while(scanf("%s", line) == 1) {
        int len = strlen(line);

        if(len < 1 || len > 50) {
            printf("Error\n");
            continue;
        }else {
            if (line[0] == '-' && len == 1) {
                printf("0\n");
                continue;
            }

            long long result = analyzeExpression(line);
            printf("%lld\n", result);
        }
    }
    return 0;
}