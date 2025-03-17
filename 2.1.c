//
// Created by Nazar Meredov on 24/02/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    int N,A,B;
    int* T_i;

    //scanf loop
    while(scanf("%d", &N) == 1) {
        // lets check barriers
        if (N < 1 || N > 50) {
            printf("Error\n");
            continue;
        }else{
            // alocate memory for cars witch will ride on the bridge
            T_i = (int*)malloc(N * sizeof(int));

            // put info into arr and check weight limits
            bool valid = true;
            for (int i = 0; i < N; i++) {
                if (scanf("%d", &T_i[i]) != 1) {
                    printf("Error\n");
                    valid = false;
                    break;
                }

                if (T_i[i] < 1 || T_i[i] > 100) {
                    printf("Error %d\n", T_i[i]);
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                free(T_i);
                break;
            }

            // get numbers
            scanf("%d %d", &A, &B);
            if(B < 1 || B > 100000 || A < 1 || A > B) {
                printf("Error\n");
                free(T_i);
                continue;
            }


            bool* win = malloc((B + 1) * sizeof(bool));

            win[0] = false;  // if we cant make move we lose

            // dynamic programming
            for (int i = 1; i <= B; i++) { // main alg to find win pos.
                win[i] = false;  // make all moves false by def.
                for (int j = 0; j < N; j++) { // check all pos. moves
                    if (T_i[j] <= i && !win[i - T_i[j]]) { // we can take j pencils from i? and we make opponent lose?
                        win[i] = true; // its win for us
                        break;
                    }
                }
            }


            // Count wins pos. in range from A - B
            int count = 0;
            for (int i = A; i <= B; i++) {
                if (win[i]) count++;
            }

            //print results
            printf("%d\n", count);

            // free memory
            free(win);
            free(T_i);
        }
    }
    return 0;
}