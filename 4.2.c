// uloha-4-2.c -- Nazar Meredov, 2025-03-19 14:15

// I was too lazy to write comments, but I asked Copilot to generate them for you to understand how my code works :D
// I know that its a big piece of shit :))

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Define constants for undefined character, maximum counts, and maximum length
#define UNDEF '?'
#define SAMOHL_COUNT 3
#define SPOLUHL_COUNT 5
#define MAX_LEN 51

// Enum to represent possible results of the dynamic programming check
typedef enum {
    UNKNOWN = -1,
    FALSE = 0,
    TRUE = 1,
    BOTH = 2
} Result;

// Memoization array for dynamic programming
Result memo[MAX_LEN][SAMOHL_COUNT+1][SPOLUHL_COUNT+1];

// Function to check if a character is a vowel
bool isSamohlaska(char c) {
    char samohlasky[] = {'A', 'E', 'I', 'O', 'U', 'Y'};
    for (int i = 0; i < 6; i++) {
        if (c == samohlasky[i]) return true;
    }
    return false;
}

// Function to check if a character is a consonant
bool isSpoluhlaska(char c) {
    char spoluhlasky[] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};
    for (int i = 0; i < 20; i++) {
        if (c == spoluhlasky[i]) return true;
    }
    return false;
}

// Function to process a line without undefined characters
bool processWithoutUndef(char* line, int len) {
    int count_samohl = 0, count_spoluhl = 0;
    for (int i = 0; i < len; i++) {
        if (isSamohlaska(line[i])) {
            count_samohl++;
            count_spoluhl = 0;
            if (count_samohl == SAMOHL_COUNT) {
                return true;
            }
        } else if (isSpoluhlaska(line[i])) {
            count_spoluhl++;
            count_samohl = 0;
            if (count_spoluhl == SPOLUHL_COUNT) {
                return true;
            }
        } else {
            // Reset counters for other characters
            count_samohl = 0;
            count_spoluhl = 0;
        }
    }
    return false;
}

// Dynamic programming function to check possible results with undefined characters
Result checkWithDP(char* line, int pos, int samohl_count, int spoluhl_count, int len) {
    // Base case: reached the end of the string
    if (pos == len) {
        // Check if the condition is met
        if (samohl_count == SAMOHL_COUNT || spoluhl_count == SPOLUHL_COUNT) {
            return TRUE;
        }
        return FALSE;
    }

    // Return the result if already computed
    if (memo[pos][samohl_count][spoluhl_count] != UNKNOWN) {
        return memo[pos][samohl_count][spoluhl_count];
    }

    Result vowelResult = UNKNOWN;
    Result consonantResult = UNKNOWN;

    // Current character is undefined
    if (line[pos] == UNDEF) {
        // Try placing a vowel
        int new_samohl = samohl_count + 1;
        int new_spoluhl = 0; // Reset consonant counter

        // Check if the condition is already met
        if (new_samohl == SAMOHL_COUNT) {
            vowelResult = TRUE;
        } else {
            vowelResult = checkWithDP(line, pos + 1, new_samohl, new_spoluhl, len);
        }

        // Try placing a consonant
        new_samohl = 0; // Reset vowel counter
        new_spoluhl = spoluhl_count + 1;

        // Check if the condition is already met
        if (new_spoluhl == SPOLUHL_COUNT) {
            consonantResult = TRUE;
        } else {
            consonantResult = checkWithDP(line, pos + 1, new_samohl, new_spoluhl, len);
        }

        // Determine the overall result
        if (vowelResult == TRUE && consonantResult == TRUE) {
            memo[pos][samohl_count][spoluhl_count] = TRUE;
        } else if (vowelResult == FALSE && consonantResult == FALSE) {
            memo[pos][samohl_count][spoluhl_count] = FALSE;
        } else if (vowelResult == BOTH || consonantResult == BOTH) {
            memo[pos][samohl_count][spoluhl_count] = BOTH;
        } else {
            memo[pos][samohl_count][spoluhl_count] = BOTH;
        }
    } else {
        // Current character is defined
        int new_samohl = samohl_count;
        int new_spoluhl = spoluhl_count;

        if (isSamohlaska(line[pos])) {
            new_samohl++;
            new_spoluhl = 0;
        } else if (isSpoluhlaska(line[pos])) {
            new_spoluhl++;
            new_samohl = 0;
        } else {
            // Other character, reset counters
            new_samohl = 0;
            new_spoluhl = 0;
        }

        // Check if the condition is already met
        if (new_samohl == SAMOHL_COUNT || new_spoluhl == SPOLUHL_COUNT) {
            memo[pos][samohl_count][spoluhl_count] = TRUE;
        } else {
            memo[pos][samohl_count][spoluhl_count] = checkWithDP(line, pos + 1, new_samohl, new_spoluhl, len);
        }
    }

    return memo[pos][samohl_count][spoluhl_count];
}

// Function to process a line with undefined characters
void processWithUndef(char* line, int len) {
    // Initialize memoization array
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= SAMOHL_COUNT; j++) {
            for (int k = 0; k <= SPOLUHL_COUNT; k++) {
                memo[i][j][k] = UNKNOWN;
            }
        }
    }

    Result result = checkWithDP(line, 0, 0, 0, len);

    if (result == TRUE) {
        printf("paci\n");
    } else if (result == FALSE) {
        printf("nepaci\n");
    } else {
        printf("neviem\n");
    }
}

int main() {
    char line[MAX_LEN];
    while (scanf("%50s", line) == 1) {
        int len = strlen(line);
        if (len < 1 || len > 50) {
            printf("%s\n", line);
            continue;
        } else if (len <= 2) {
            printf("nepaci\n");
            continue;
        }

        int undef_count = 0;
        for (int i = 0; i < len; i++) {
            if (line[i] == UNDEF) {
                undef_count++;
            }
        }

        if (undef_count == len) {
            printf("neviem\n");
        } else if (undef_count == 0) {
            if (processWithoutUndef(line, len)) {
                printf("paci\n");
            } else {
                printf("nepaci\n");
            }
        } else {
            processWithUndef(line, len);
        }
    }
    return 0;
}