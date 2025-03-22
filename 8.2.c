// uloha-8-2.c -- Nazar Meredov, 2025-03-21 16:42

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int num_fav_dishes;
    int num_fav_drinks;
    int fav_dishes[100];
    int fav_drinks[100];
} Child;

//bipartite graph:
//One lobe: children N
//Second share: meals F or
//drinks D (analyze separately)
typedef struct {
    int num_children;
    int num_dishes;
    int num_drinks;
    bool child_dish_edges[100][100]; //matrix for child->dish
    bool child_drink_edges[100][100]; // matrix for child->drink
    int dish_to_child[100];   // which child got which dish
    int drink_to_child[100];  // .||. drink
} BipartiteGraph;
void init_graph(BipartiteGraph *graph, int N, int F, int D, Child children[]) {
    graph->num_children = N;
    graph->num_dishes = F;
    graph->num_drinks = D;

    // set starting values
    memset(graph->child_dish_edges, false, sizeof(graph->child_dish_edges));
    memset(graph->child_drink_edges, false, sizeof(graph->child_drink_edges));
    memset(graph->dish_to_child, -1, sizeof(int) * F);
    memset(graph->drink_to_child, -1, sizeof(int) * D);

    // init graph from children arr
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < children[i].num_fav_dishes; j++) {
            int dish = children[i].fav_dishes[j] - 1;
            graph->child_dish_edges[i][dish] = true;
        }

        for (int j = 0; j < children[i].num_fav_drinks; j++) {
            int drink = children[i].fav_drinks[j] - 1;
            graph->child_drink_edges[i][drink] = true;
        }
    }
}

// Ford-Fulkerson alg.
// code taken from https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/ and rewriting
int ford_fulkerson(int capacity[302][302], int num_vertices, int source, int sink) {
    int max_flow = 0;
    bool visited[302];
    int parent[302];

    while (true) {
        memset(visited, false, sizeof(visited));
        memset(parent, -1, sizeof(parent));

        // BFS to find augmenting path
        int queue[302], front = 0, rear = 0;

        queue[rear++] = source;
        visited[source] = true;

        bool path_found = false;

        while (front < rear && !path_found) {
            int u = queue[front++];

            for (int v = 0; v < num_vertices; v++) {
                if (!visited[v] && capacity[u][v] > 0) {
                    parent[v] = u;
                    visited[v] = true;
                    queue[rear++] = v;

                    if (v == sink) {
                        path_found = true;
                        break;
                    }
                }
            }
        }

        if (!path_found) break;

        // Augment the flow
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            capacity[u][v]--;
            capacity[v][u]++;
        }

        max_flow++;
    }

    return max_flow;
}

void process_children(int N, int F, int D, Child children[]) {
    BipartiteGraph graph; // create graph
    init_graph(&graph, N, F, D, children); // init it

    int happy_childrens = 0;

    // Create a network flow graph for matching
    int num_vertices = N + F + 2;
    int source = num_vertices - 2;
    int sink = num_vertices - 1;
    int capacity_dishes[302][302] = {0}; // Max size: N + F + 2

    // Edges from source to children with 1
    for (int i = 0; i < N; i++) {
        capacity_dishes[source][i] = 1;
    }

    // Edges from children to dishes
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < children[i].num_fav_dishes; j++) {
            int dish = children[i].fav_dishes[j] - 1;
            capacity_dishes[i][N + dish] = 1;
        }
    }

    // Edges from dishes to sink with capacity 1
    for (int i = 0; i < F; i++) {
        capacity_dishes[N + i][sink] = 1;
    }

    // Find maximum flow using Ford-Fulkerson alg. for dishes
    int max_dish_matches = ford_fulkerson(capacity_dishes, num_vertices, source, sink);


    // start calc. for drinks

    // Reset for drinks
    num_vertices = N + D + 2;
    source = num_vertices - 2;
    sink = num_vertices - 1;
    int capacity_drinks[302][302] = {0}; // Max size: N + D + 2

    for (int i = 0; i < N; i++) {
        capacity_drinks[source][i] = 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < children[i].num_fav_drinks; j++) {
            int drink = children[i].fav_drinks[j] - 1;
            capacity_drinks[i][N + drink] = 1;
        }
    }

    for (int i = 0; i < D; i++) {
        capacity_drinks[N + i][sink] = 1;
    }

    // Ford-Fulkerson alg. for drinks
    int max_drink_matches = ford_fulkerson(capacity_drinks, num_vertices, source, sink);


    // Find minimum of two matches
    happy_childrens = (max_dish_matches < max_drink_matches) ? max_dish_matches : max_drink_matches;
    printf("%d\n", happy_childrens);
}

int main() {
    int N, F, D;
    // children, dishes, drinks
    Child children[100];

    while (scanf("%d %d %d", &N, &F, &D) == 3) {
        if (N < 1 || N > 100 || F < 1 || F > 100 || D < 1 || D > 100) {
            printf("Error N a M or D\n");
            continue;
        }

        for (int i = 0; i < N; i++) {
            scanf("%d %d", &children[i].num_fav_dishes, &children[i].num_fav_drinks);

            for (int j = 0; j < children[i].num_fav_dishes; j++) {
                scanf("%d", &children[i].fav_dishes[j]);
            }

            for (int j = 0; j < children[i].num_fav_drinks; j++) {
                scanf("%d", &children[i].fav_drinks[j]);
            }
        }

        process_children(N, F, D, children);
    }
    return 0;
}