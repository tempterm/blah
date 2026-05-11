#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4
#define INF 99999999

int goal[N][N] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9,  10, 11, 12},
    {13, 14, 15, 0}
};

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int found, moveCount;

int manhattan(int board[N][N]) {
    int i, j, dist = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int val = board[i][j];
            if (val != 0) {
                int targetRow = (val - 1) / N;
                int targetCol = (val - 1) % N;
                dist += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    return dist;
}

int isGoal(int board[N][N]) {
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (board[i][j] != goal[i][j]) return 0;
    return 1;
}

int search(int board[N][N], int g, int bound, int prevX, int prevY) {
    int i, j, h, f, nx, ny, t, minVal, zeroX, zeroY;

    h = manhattan(board);
    f = g + h;

    if (f > bound) return f;

    if (isGoal(board)) {
        found = 1;
        moveCount = g;
        return 0;
    }

    zeroX = -1; zeroY = -1;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (board[i][j] == 0) { zeroX = i; zeroY = j; }

    minVal = INF;

    for (i = 0; i < 4; i++) {
        nx = zeroX + dx[i];
        ny = zeroY + dy[i];

        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (nx == prevX && ny == prevY) continue;

        board[zeroX][zeroY] = board[nx][ny];
        board[nx][ny] = 0;

        t = search(board, g + 1, bound, zeroX, zeroY);
        if (found) return 0;
        if (t < minVal) minVal = t;

        board[nx][ny] = board[zeroX][zeroY];
        board[zeroX][zeroY] = 0;
    }
    return minVal;
}

int main() {
    int i, j, board[N][N], bound, t;

    printf("Enter 15-puzzle row by row (use 0 for blank):\n");
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            scanf("%d", &board[i][j]);

    found = 0;
    moveCount = 0;
    bound = manhattan(board);

    clock_t start = clock();

    while (!found) {
        t = search(board, 0, bound, -1, -1);
        if (found) break;
        if (t == INF) {
            printf("No solution exists!\n");
            break;
        }
        bound = t;
    }

    clock_t end = clock();

    if (found)
        printf("Solution found in %d moves!\n", moveCount);

    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}