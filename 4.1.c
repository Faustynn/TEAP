// uloha-4-1.c -- Nazar Meredov, 2025-03-18 15:55

#include <stdio.h>
#include <string.h>

#define DEL 100000007

void calculate(int wight, int height) {
    //two arrs. to track posbl states
    // accept[i][j] = number of ways to reach position j on layer i and TAKE more input
    // decline[i][j] = number of ways to reach position j on layer i and REJECT more input
    // we only need to remember the current and previous layers, so [2][height+2]
    long long take[2][height + 2], reject[2][height + 2];

    // set arrs. to 0
    memset(take, 0, sizeof(take));
    memset(reject, 0, sizeof(reject));

    // if height 1 we take and have 1 way
    if (height == 1) {
        take[0][1] = 1;
    } else {
        // else we start by declining at 1
        reject[0][1] = 1;
    }

    // i = current width pos.
    for (size_t i = 1; i < wight - 1; i++) {
        // j = height pos.
        for (size_t j = 1; j <= height; j++) {

            // if we top of the column
            if (j == height) {
                // at top, we can only accept go down or continue go at same level
                take[1][j] = take[0][j - 1] + take[0][j] + reject[0][j - 1];
                break;
            }

            // move to curr. pos. from down,above or same hight level
            take[1][j] = (take[0][j - 1] + take[0][j] + take[0][j + 1]) % DEL;   // for take, we count ways to reach this position

            // for reject, we count ways to reach this position and stop taking new one
            reject[1][j] = (reject[0][j - 1] + reject[0][j] + reject[0][j + 1]) % DEL;
        }

        // copy current step to previous in both arrs
        memcpy(take[0], take[1], sizeof(take[0]));
        memcpy(reject[0], reject[1], sizeof(reject[0]));
    }

    printf("%lld\n", take[1][1]); // print reslt.
}


int main() {
    int N, D, V;

    //scanf
    scanf("%d", &N);
    if (N < 1 || N > 20) {
        printf("Error\n");
        return -1;
    }

    // process weight and height
    while (N--) {
        scanf("%d %d", &D, &V);

        if (D < 2 || D > 5000 || V < 1 || V > 200) {
            printf("Error\n");
            continue;
        }

        calculate(D, V);
    }
    return 0;
}