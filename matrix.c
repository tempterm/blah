#include <stdio.h>
#include <time.h>

#define INF 99999999

int main() {
    int n, i, j, k, L, q;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];
    printf("Enter dimensions (e.g. for 3 matrices A(2x3), B(3x4), C(4x2) enter: 2 3 4 2)\n");
    for (i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    int m[n + 1][n + 1];

    for (i = 1; i <= n; i++)
        m[i][i] = 0;

    clock_t start = clock();

    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INF;

            for (k = i; k < j; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    clock_t end = clock();

    printf("Minimum number of multiplications: %d\n", m[1][n]);
    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}