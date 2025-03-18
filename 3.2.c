#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool is_dividedFive(char* str, int start, int end) {
    if (str[start] == '0' && end > start) //skip 0
        return false;

    long long value = 0;
    for (int i = start; i <= end; i++) { // convert bin. to dec.
        value = value * 2 + (str[i] - '0');
    }

    if (value == 0) return false; // if 0 false

    while (value > 0 && value % 5 == 0) { // if we can divide 5
        value /= 5;
    }

    return (value == true); // true
}
int calculate(char* binary_num, int len) {
    if (len == 1 && binary_num[0] == '0')
        return -1; // if 0 its not power for 5

    // lets store minimum splits for suberate line
    int* arr = (int*)malloc((len + 1) * sizeof(int));

    for (int i = 0; i <= len; i++) {
        arr[i] = INT_MAX; // init with start value INT_MAX
    }

    arr[0] = 0;

    for (int i = 1; i <= len; i++) { // string pointer
        for (int j = 0; j < i; j++) { // sub string pointer for arr
            if (arr[j] != INT_MAX && is_dividedFive(binary_num, j, i - 1)) { // its not -1 and div. by 5??
                arr[i] = arr[i] < arr[j] + 1 ? arr[i] : arr[j] + 1; // if less then ++
            }
        }
    }

    int reslt = (arr[len] == INT_MAX) ? -1 : arr[len];


    free(arr);
    return reslt;
}

int main(void) {
    char* line = NULL;
    line = (char*)malloc(51 * sizeof(char));

    // scanf loop
    while(scanf("%s", line) == 1) {
        int len = strlen(line);

        if(len < 1 || len > 50) {
            printf("Error\n");
            continue;
        } else {
            int reslt = calculate(line,len);
            printf("%d\n", reslt);
        }
    }
    free(line);
    return 0;
}