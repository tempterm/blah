#include <stdio.h>
#include <time.h>

int board[8][8];
int solutions = 0;

int isSafe(int row, int col) {
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i]) return 0;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return 0;

    for (i = row, j = col; i < 8 && j >= 0; i++, j--)
        if (board[i][j]) return 0;

    return 1;
}

void solveQueens(int col) {
    int i, j;

    if (col == 8) {
        solutions++;
        printf("Solution %d:\n", solutions);
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++)
                printf("%s ", board[i][j] ? "Q" : ".");
            printf("\n");
        }
        printf("\n");
        return;
    }

    for (i = 0; i < 8; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            solveQueens(col + 1);
            board[i][col] = 0;
        }
    }
}

int main() {
    int i, j;

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            board[i][j] = 0;

    clock_t start = clock();
    solveQueens(0);
    clock_t end = clock();

    printf("Total solutions found: %d\n", solutions);
    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}