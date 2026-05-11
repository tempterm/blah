#include <stdio.h>
#include <time.h>
#include <string.h>

#define d 256
#define q 101

void rabinKarp(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int p_hash = 0, t_hash = 0, h = 1;

    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < m; i++) {
        p_hash = (d * p_hash + pattern[i]) % q;
        t_hash = (d * t_hash + text[i]) % q;
    }

    for (i = 0; i <= n - m; i++) {
        if (p_hash == t_hash) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                printf("Pattern found at index %d\n", i);
        }

        if (i < n - m) {
            t_hash = (d * (t_hash - text[i] * h) + text[i + m]) % q;
            if (t_hash < 0)
                t_hash += q;
        }
    }
}

int main() {
    char text[1000], pattern[100];

    printf("Enter text: ");
    scanf("%s", text);

    printf("Enter pattern to search: ");
    scanf("%s", pattern);

    clock_t start = clock();
    rabinKarp(text, pattern);
    clock_t end = clock();

    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}