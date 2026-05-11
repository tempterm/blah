#include <stdio.h>
#include <time.h>

int arr[100];
int subset[100];
int n, target;

void findSubsets(int index, int currentSum, int subsetSize) {
    int i;

    if (currentSum == target) {
        printf("Subset found: { ");
        for (i = 0; i < subsetSize; i++)
            printf("%d ", subset[i]);
        printf("}\n");
        return;
    }

    if (index == n || currentSum > target)
        return;

    subset[subsetSize] = arr[index];
    findSubsets(index + 1, currentSum + arr[index], subsetSize + 1);

    findSubsets(index + 1, currentSum, subsetSize);
}

int main() {
    int i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter target sum: ");
    scanf("%d", &target);

    clock_t start = clock();
    findSubsets(0, 0, 0);
    clock_t end = clock();

    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}