#include <stdio.h>
#include <time.h>

#define MAX 100
#define INF 99999999

int src_node[MAX], dest_node[MAX], weight_edge[MAX];
int dist[MAX];
int n, edges;

void bellmanFord(int src) {
    int i, j;

    for (i = 0; i < n; i++)
        dist[i] = INF;

    dist[src] = 0;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < edges; j++) {
            int u = src_node[j];
            int v = dest_node[j];
            int w = weight_edge[j];

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative weight cycle
    for (j = 0; j < edges; j++) {
        int u = src_node[j];
        int v = dest_node[j];
        int w = weight_edge[j];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }
}

int main() {
    int i, src;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge as: source destination weight\n");
    for (i = 0; i < edges; i++)
        scanf("%d %d %d", &src_node[i], &dest_node[i], &weight_edge[i]);

    printf("Enter source vertex (0-indexed): ");
    scanf("%d", &src);

    clock_t start = clock();
    bellmanFord(src);
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