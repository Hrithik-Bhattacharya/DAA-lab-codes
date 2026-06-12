#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 999999
#define MAX_NODES 500

// Function to run Floyd-Warshall
void floydWarshall(int n, int graph[MAX_NODES][MAX_NODES]) {
    int i, j, k;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

// Function to initialize a random graph
void generateGraph(int n, int graph[MAX_NODES][MAX_NODES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) graph[i][j] = 0;
            else {
                int weight = rand() % 100 + 1;
                // Give it some sparsity: 30% chance of no direct edge
                graph[i][j] = (rand() % 10 > 7) ? INF : weight;
            }
        }
    }
}

int main() {
    int sizes[] = {50, 100, 200, 300, 400, 500};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    static int graph[MAX_NODES][MAX_NODES];

    printf("-------------------------------------------\n");
    printf("| Nodes (N) | Time Taken (Seconds)        |\n");
    printf("-------------------------------------------\n");

    for (int t = 0; t < num_tests; t++) {
        int n = sizes[t];
        generateGraph(n, graph);

        clock_t start = clock();
        floydWarshall(n, graph);
        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("| %-9d | %-26.4f |\n", n, time_spent);
    }

    printf("-------------------------------------------\n");
    return 0;
}
