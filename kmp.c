#include <stdio.h>
#include <time.h>
#include <string.h>

void computeLPS(char pattern[], int m, int lps[]) {
    int len = 0, i = 1;
    lps[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[m];
    int i = 0, j = 0;

    computeLPS(pattern, m, lps);

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
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
    KMPSearch(text, pattern);
    clock_t end = clock();

    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}