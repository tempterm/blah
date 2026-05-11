#include <stdio.h>
#include <time.h>

int main() {
    int n, i, j;
    printf("Enter number of items: ");
    scanf("%d", &n);

    float weight[n], value[n], ratio[n];

    printf("Enter weight of each item:\n");
    for (i = 0; i < n; i++)
        scanf("%f", &weight[i]);

    printf("Enter value of each item:\n");
    for (i = 0; i < n; i++)
        scanf("%f", &value[i]);

    for (i = 0; i < n; i++)
        ratio[i] = value[i] / weight[i];

    // Sort by ratio descending (Bubble Sort)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (ratio[j] < ratio[j + 1]) {
                float temp;
                temp = ratio[j];   ratio[j] = ratio[j+1];   ratio[j+1] = temp;
                temp = value[j];   value[j] = value[j+1];   value[j+1] = temp;
                temp = weight[j];  weight[j] = weight[j+1]; weight[j+1] = temp;
            }
        }
    }

    float capacity, totalValue = 0;
    printf("Enter knapsack capacity: ");
    scanf("%f", &capacity);

    clock_t start = clock();

    for (i = 0; i < n; i++) {
        if (weight[i] <= capacity) {
            totalValue += value[i];
            capacity -= weight[i];
            printf("Took full item %d\n", i + 1);
        } else {
            totalValue += ratio[i] * capacity;
            printf("Took fraction of item %d\n", i + 1);
            break;
        }
    }

    clock_t end = clock();

    printf("Maximum value: %.2f\n", totalValue);
    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}