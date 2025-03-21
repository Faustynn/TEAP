#include <stdio.h>
#include <stdbool.h>
#include <limits.h>


typedef struct {
    int path[20];
    int path_len;
    int use_power;
} Best_path;

// recursive backtracking method to try all possible ways
void findPath(int N, int arr[N][N], int current, bool visited[N], int effort, int path[N], int path_len, Best_path* best) {
    path[path_len] = current; // add curr. pos to path
    path_len++;

    // we visit all homes??
    bool all_visited = true;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            all_visited = false;
            break;
        }
    }

    // is visited all - is the best way?
    if (all_visited) {
        if (effort < best->use_power) {
            best->use_power = effort;
            best->path_len = path_len;
            for (int i = 0; i < path_len; i++) {
                best->path[i] = path[i];
            }
        }
        return;
    }

    // lets visit next unvisited home
    for (int next = 0; next < N; next++) {
        if (!visited[next]) {
            visited[next] = true;
            findPath(N, arr, next, visited, effort + arr[current][next],
                     path, path_len, best);
            visited[next] = false; // backtrack
        }
    }
}

// process input
void process(int N, int arr[N][N]) {
    bool visited[20] = {false}; // init visited arr as all unvisited
    int path[20]; // init path arr
    Best_path best; // init struct

    // define struct val.
    best.use_power = INT_MAX;
    best.path_len = 0;

    // start pos is 0
    visited[0] = true;
    findPath(N, arr, 0, visited, 0, path, 0, &best);

    // print reslt.
    printf("%d\n", best.use_power);
    for (int i = 0; i < best.path_len; i++) {
        printf("%d ", best.path[i]+1);
    }
    printf("\n");
}

int main() {
    int N;

    scanf("%d", &N);
    int arr[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    process(N, arr);

    return 0;
}