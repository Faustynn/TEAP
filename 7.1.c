// uloha-7-1.c -- Nazar Meredov, 2025-03-20 20:31

#include <stdio.h>
#include <stdlib.h>

// struct for state saving
typedef struct {
    int mask;
    int count;
    long long ways;
} State;

// struct for state table
typedef struct {
    State* states;
    int capacity;
    int size;
} StateTable;

// init state table
StateTable* createStateTable(int capacity) {
    StateTable* table = (StateTable*)malloc(sizeof(StateTable));
    table->capacity = capacity;
    table->size = 0;
    table->states = (State*)malloc(sizeof(State) * capacity);
    return table;
}

// clear and dealocate state table
void clearStateTable(StateTable* table) {
    table->size = 0;
}
void freeStateTable(StateTable* table) {
    free(table->states);
    free(table);
}

// update state in table
void updateState(StateTable* table, int mask, int count, long long ways) {
    // we have this state? if yes,upd. ways
    for (int i = 0; i < table->size; i++) {
        if (table->states[i].mask == mask && table->states[i].count == count) {
            table->states[i].ways += ways;
            return;
        }
    }

    // else add new statee
    if (table->size >= table->capacity) {
        table->capacity *= 2;
        table->states = (State*)realloc(table->states, sizeof(State) * table->capacity);
    }

    table->states[table->size].mask = mask;
    table->states[table->size].count = count;
    table->states[table->size].ways = ways;
    table->size++;
}

int main() {
    int k, n, m;
    char arr[11][11];

    while (scanf("%d", &k) == 1) {
        if (k < 1 || k > 10) {
            printf("Error\n");
            continue;
        }

        scanf("%d %d", &n, &m);
        if (n < 1 || n > 10 || m < 1 || m > 10) {
            printf("Error\n");
            continue;
        }

        for (int i = 0; i < n; i++) {
            scanf("%10s", arr[i]);
        }

        // Create tables with current and next layer of states
        StateTable* current = createStateTable(100);
        StateTable* next = createStateTable(100);

        // init start states
        updateState(current, 0, 0, 1);

        // go throu all rows
        for (int row = 0; row < n; row++) {
            clearStateTable(next); // clear

            // go trouw all states
            for (int i = 0; i < current->size; i++) {
                int mask = current->states[i].mask;
                int count = current->states[i].count;
                long long ways = current->states[i].ways;

                updateState(next, mask, count, ways); // update states in next layer

                if (count < k) { // if we take less then k we can continue
                    for (int col = 0; col < m; col++) { // next go throw columns
                        if (((mask >> col) & 1) == 0 && arr[row][col] == 'Y') { // its free in and can we take it in arr
                            int new_mask = mask | (1 << col); // if yes we create new mask
                            updateState(next, new_mask, count + 1, ways); // update state
                        }
                    }
                }
            }

            // swap layers
            StateTable* temp = current;
            current = next;
            next = temp;
        }


        // calc. res. with taking K from arr
        long long result = 0;
        for (int i = 0; i < current->size; i++) {
            if (current->states[i].count == k) {
                result += current->states[i].ways;
            }
        }

        // print res.
        printf("%lld\n", result);


        // free tables
        freeStateTable(current);
        freeStateTable(next);
    }
    return 0;
}