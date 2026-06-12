#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define INF 999999 // Representing infinity for unreachable vertices

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[], int n) {
    int min = INF, min_index;

    for (int v = 0; v < n; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra's algorithm for a single source vertex
void dijkstra(int **graph, int src, int n) {
    int dist[n];
    bool sptSet[n];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the calculated shortest distances from the current source
    for (int i = 0; i < n; i++) {
        // Converting index 0, 1, 2... to A, B, C...
        char srcChar = 'A' + src;
        char destChar = 'A' + i;

        if (dist[i] == INF) {
            printf("shortest path from %c to %c = INF\n", srcChar, destChar);
        } else {
            printf("shortest path from %c to %c = %d\n", srcChar, destChar, dist[i]);
        }
    }
}

int main() {
    int n;

    printf("Enter the number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    // Dynamically allocating memory for the 2D cost adjacency matrix
    int **C = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        C[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter the cost adjacency matrix (%d x %d):\n", n, n);
    printf("(Use 0 for self-loops and 999999 for no direct edge)\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &C[i][j]);
        }
    }

    printf("\n--- Shortest Paths ---\n");

    // Start clock timing
    clock_t start_time = clock();

    // Run Dijkstra's algorithm treating every vertex as a source
    for (int i = 0; i < n; i++) {
        dijkstra(C, i, n);
    }

    // End clock timing
    clock_t end_time = clock();

    // Calculate runtime in milliseconds
    double duration = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

    printf("\n----------------------\n");
    printf("Runtime of the algorithm: %.2f ms\n", duration);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(C[i]);
    }
    free(C);

    return 0;
}
