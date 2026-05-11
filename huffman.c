#include <stdio.h>
#include <time.h>

#define MAX 100

int freq[MAX], parent[MAX], left[MAX], right[MAX];
char codes[MAX][MAX];
int n, top;

int findMin(int exclude1, int exclude2) {
    int min = -1, i;
    for (i = 0; i < top; i++) {
        if (i == exclude1 || i == exclude2) continue;
        if (parent[i] != -1) continue;
        if (min == -1 || freq[i] < freq[min])
            min = i;
    }
    return min;
}

void generateCodes(int node, char code[], int depth) {
    if (left[node] == -1 && right[node] == -1) {
        code[depth] = '\0';
        int i;
        for (i = 0; i < depth; i++)
            codes[node][i] = code[i];
        codes[node][depth] = '\0';
        return;
    }
    if (left[node] != -1) {
        code[depth] = '0';
        generateCodes(left[node], code, depth + 1);
    }
    if (right[node] != -1) {
        code[depth] = '1';
        generateCodes(right[node], code, depth + 1);
    }
}

int main() {
    int i;
    char chars[MAX];

    printf("Enter number of characters: ");
    scanf("%d", &n);

    printf("Enter characters and their frequencies:\n");
    for (i = 0; i < n; i++) {
        printf("Char %d: ", i + 1);
        scanf(" %c %d", &chars[i], &freq[i]);
        parent[i] = -1;
        left[i] = -1;
        right[i] = -1;
    }

    top = n;

    clock_t start = clock();

    while (1) {
        int x = findMin(-1, -1);
        int y = findMin(-1, x);
        if (y == -1) break;

        freq[top] = freq[x] + freq[y];
        left[top] = x;
        right[top] = y;
        parent[top] = -1;
        parent[x] = top;
        parent[y] = top;
        top++;
    }

    char code[MAX];
    generateCodes(top - 1, code, 0);

    clock_t end = clock();

    printf("\nHuffman Codes:\n");
    for (i = 0; i < n; i++)
        printf("  %c : %s\n", chars[i], codes[i]);

    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}