#include <stdio.h>
#include <time.h>

#define MAX 25

int graph[MAX][MAX];
int inCover[MAX];
int n;

void vertexCover() {
    int i, j;

    for (i = 0; i < n; i++) inCover[i] = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (graph[i][j] == 1 && !inCover[i] && !inCover[j]) {
                inCover[i] = 1;
                inCover[j] = 1;
            }
        }
    }
}

int main() {
    int i, j, edges, count = 0;

    printf("Enter number of vertices (at least 20): ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");
    for (i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    clock_t start = clock();
    vertexCover();
    clock_t end = clock();

    printf("Vertex Cover: { ");
    for (i = 0; i < n; i++) {
        if (inCover[i]) {
            printf("%d ", i);
            count++;
        }
    }
    printf("}\n");

    printf("Total vertices in cover: %d\n", count);
    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}