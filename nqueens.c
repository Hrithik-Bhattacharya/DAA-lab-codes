#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int solution_count = 0;

// Function to print the chessboard configuration
void printBoard(int **board, int n) {
    printf("\nSolution %d:\n", ++solution_count);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) {
                printf("Q ");
            } else {
                printf("_ ");
            }
        }
        printf("\n");
    }
}

// Function to check if a queen can be safely placed at board[row][col]
bool isSafe(int **board, int row, int col, int n) {
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++) {
        if (board[row][i] == 1) return false;
    }

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false;
    }

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < n; i++, j--) {
        if (board[i][j] == 1) return false;
    }

    return true;
}

// Recursive helper function to solve N Queens problem
void solveNQueensUtil(int **board, int col, int n) {
    // Base case: If all queens are placed, print the board
    if (col >= n) {
        printBoard(board, n);
        return;
    }

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            // Place this queen
            board[i][col] = 1;

            // Recur to place rest of the queens
            solveNQueensUtil(board, col + 1, n);

            // If placing queen in board[i][col] doesn't lead to a solution,
            // then remove the queen (Backtrack)
            board[i][col] = 0;
        }
    }
}

int main() {
    int n;

    printf("Enter the value of N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    // Dynamically allocate memory for the 2D chessboard array
    int **board = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        board[i] = (int *)calloc(n, sizeof(int)); // Initialize all elements to 0
    }

    // Start timing the execution
    clock_t start_time = clock();

    solveNQueensUtil(board, 0, n);

    // End timing the execution
    clock_t end_time = clock();

    // Calculate runtime in milliseconds
    double duration = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

    if (solution_count == 0) {
        printf("\nNo solution exists for N = %d\n", n);
    } else {
        printf("\nTotal configurations found: %d\n", solution_count);
    }

    printf("Runtime of the algorithm: %.2f ms\n", duration);

    // Free the dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}
