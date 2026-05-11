#include <stdio.h>
#include <time.h>

#define MAX 100
#define INF 99999999

int graph[MAX][MAX];
int parent[MAX];
int visited[MAX];
int n;

int bfs(int src, int sink) {
    int i;
    int queue[MAX], front = 0, rear = 0;

    for (i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    visited[src] = 1;
    queue[rear++] = src;

    while (front < rear) {
        int u = queue[front++];
        for (i = 0; i < n; i++) {
            if (!visited[i] && graph[u][i] > 0) {
                visited[i] = 1;
                parent[i] = u;
                queue[rear++] = i;
                if (i == sink) return 1;
            }
        }
    }
    return 0;
}

int fordFulkerson(int src, int sink) {
    int u, v;
    int maxFlow = 0;

    while (bfs(src, sink)) {
        int pathFlow = INF;

        v = sink;
        while (v != src) {
            u = parent[v];
            if (graph[u][v] < pathFlow)
                pathFlow = graph[u][v];
            v = parent[v];
        }

        v = sink;
        while (v != src) {
            u = parent[v];
            graph[u][v] -= pathFlow;
            graph[v][u] += pathFlow;
            v = parent[v];
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    int i, j, src, sink;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter capacity matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter source vertex (0-indexed): ");
    scanf("%d", &src);
    printf("Enter sink vertex (0-indexed): ");
    scanf("%d", &sink);

    clock_t start = clock();
    int result = fordFulkerson(src, sink);
    clock_t end = clock();

    printf("Maximum Flow: %d\n", result);
    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}