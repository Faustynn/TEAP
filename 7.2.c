// Created by Nazar Meredov on 24/02/2025.

// uloha-7-2.c -- Nazar Meredov, 2025-03-20 21:29

#include <stdio.h>
#include <string.h>

// for comments i use Copilot to generate them in hard to understanding parts

typedef struct {
    int modulus;                // M
    int num_digits;             // N
    long long dp_table[10][1000]; // DP table for reslts.
} PalindromeCounter;

typedef struct {
    int level;         // Current level in the palindrome calculation (position within the digits).
    int mid_point;     // Middle position in the palindrome (used for even or odd length).
    int half_point;    // Halfway point of the palindrome (used to split the palindrome).
} PositionInfo;

PositionInfo initialize_position(int digit_count) {
    PositionInfo pos;
    pos.mid_point = digit_count / 2;             // If even, it's the middle; if odd, the middle is slightly offset.
    pos.half_point = (digit_count - 1) / 2;      // The halfway point of the digits.
    pos.level = 0;                               // Start at level 0.
    return pos;
}

// Calculate power of 10 for expresion
unsigned long long power_of_ten(int exp) {
    unsigned long long base = 1;
    for (int i = 0; i < exp; i++) {
        base *= 10;
    }
    return base;
}

typedef struct {
    int left_contribution;    // Contribution of the digit to the left side of the palindrome.
    int right_contribution;   // Contribution of the digit to the right side.
    int total_impact;         // Total impact on the palindrome (modulus applied).
} DigitImpact;

// impact of adding a digit at both ends
DigitImpact calculate_digit_impact(PositionInfo pos, int digit, int modulus) {
    DigitImpact impact;

    // calc. left contribution
    impact.left_contribution = (power_of_ten(pos.half_point - pos.level) * digit) % modulus;

    // calc. right contribution
    impact.right_contribution = (power_of_ten(pos.mid_point + pos.level) * digit) % modulus;

    // Total impact calc.
    impact.total_impact = (impact.left_contribution + impact.right_contribution) % modulus;

    return impact;
}

// for implement alg. i use top-down approach alg. with Copilot helping

// Fill DP table throw top-down approach
void build_palindrome_counts(PalindromeCounter *counter, PositionInfo pos) {
    // Base case checking
    if (pos.level > pos.half_point) {
        return;
    }

    // Determine starting digit (1 for middle position, 0 otherwise)
    int start_digit = (pos.level == pos.half_point) ? 1 : 0;

    // Process each possible digit
    for (int digit = start_digit; digit <= 9; digit++) {
        // Calculate impact of placing this digit at current position
        DigitImpact impact = calculate_digit_impact(pos, digit, counter->modulus);

        // Update counts for all possible remainders
        for (int prev_rem = 0; prev_rem < counter->modulus; prev_rem++) {
            int new_rem = (impact.total_impact + prev_rem) % counter->modulus;
            counter->dp_table[pos.level][new_rem] += counter->dp_table[pos.level-1][prev_rem];
        }
    }

    // Process next position recursively
    pos.level += 1;
    build_palindrome_counts(counter, pos);
}

// Initialize the base case for DP
void setup_initial_state(PalindromeCounter *counter, PositionInfo pos) {
    int is_middle = (0 == pos.half_point);    // Check if the first position is the middle.
    int start = is_middle ? 1 : 0;

    for (int digit = start; digit <= 9; digit++) {
        // First digit contribution
        unsigned long long first_pos = power_of_ten(pos.mid_point) * digit;

        // Last digit contribution (for even length palindromes)
        unsigned long long last_pos = 0;
        if (counter->num_digits % 2 == 0) {
            last_pos = power_of_ten(pos.mid_point - 1) * digit;
        }

        // Calculate remainder and update initial state
        int remainder = (first_pos + last_pos) % counter->modulus;
        counter->dp_table[0][remainder] += 1;
    }
}

int main() {
    int n;
    scanf("%d", &n);  // Read number of test cases.

    for (int t = 0; t < n; t++) {
        PalindromeCounter counter;
        memset(&counter, 0, sizeof(PalindromeCounter));  // init counter struct.

        scanf("%d %d", &counter.modulus, &counter.num_digits);

        // Setup pos. tracking
        PositionInfo pos = initialize_position(counter.num_digits);

        // init. start states
        setup_initial_state(&counter, pos);

        // recursive calc from level 1
        pos.level = 1;
        build_palindrome_counts(&counter, pos);

        printf("%lld\n", counter.dp_table[pos.half_point][0]);  // Output the final result for this test case.
    }

    return 0;
}
