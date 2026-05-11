#include <stdio.h>
#include <time.h>

#define MAX 100

int graph[MAX][MAX];
int matchL[MAX], matchR[MAX];
int visited[MAX];
int n, m;

int dfs(int u) {
    int v;
    for (v = 0; v < m; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = 1;
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchL[u] = v;
                matchR[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int i, j, result = 0;

    printf("Enter number of vertices on left side: ");
    scanf("%d", &n);
    printf("Enter number of vertices on right side: ");
    scanf("%d", &m);

    printf("Enter adjacency matrix (1 if edge, 0 if not):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &graph[i][j]);

    for (i = 0; i < n; i++) matchL[i] = -1;
    for (i = 0; i < m; i++) matchR[i] = -1;

    clock_t start = clock();

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) visited[j] = 0;
        if (dfs(i)) result++;
    }

    clock_t end = clock();

    printf("Maximum Matching: %d\n", result);
    printf("Matched pairs:\n");
    for (i = 0; i < n; i++)
        if (matchL[i] != -1)
            printf("  Left %d -- Right %d\n", i, matchL[i]);

    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}