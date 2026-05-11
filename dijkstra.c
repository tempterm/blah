#include <stdio.h>
#include <time.h>

#define MAX 100
#define INF 99999999

int dist[MAX], visited[MAX];
int graph[MAX][MAX];
int n;

int findMin() {
    int min = INF, minIndex = -1, i;
    for (i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int src) {
    int i, j, u;

    for (i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (i = 0; i < n - 1; i++) {
        u = findMin();
        if (u == -1) break;
        visited[u] = 1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && graph[u][j] != 0) {
                if (dist[u] + graph[u][j] < dist[j]) {
                    dist[j] = dist[u] + graph[u][j];
                }
            }
        }
    }
}

int main() {
    int i, j, src;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 if no edge):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter source vertex (0-indexed): ");
    scanf("%d", &src);

    clock_t start = clock();
    dijkstra(src);
    clock_t end = clock();

    printf("\nShortest distances from vertex %d:\n", src);
    for (i = 0; i < n; i++) {
        if (dist[i] == INF)
            printf("  Vertex %d : No path\n", i);
        else
            printf("  Vertex %d : %d\n", i, dist[i]);
    }

    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}