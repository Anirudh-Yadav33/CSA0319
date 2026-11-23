
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Linear Search
static int linear_search(const int *a, int n, int key) {
    for (int i = 0; i < n; i++) {
        if (a[i] == key)
            return i;
    }
    return -1;
}

// Binary Search
static int binary_search(const int *a, int n, int key) {
    int lo = 0, hi = n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (a[mid] == key)
            return mid;

        if (a[mid] < key)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return -1;
}

int main(void) {
    int sizes[] = {200, 2000, 80000};
    int repetitions = 10000;

    printf("LIBRARY SEARCH PERFORMANCE BENCHMARK\n");
    printf("--------------------------------------------\n");

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];

        int *a = malloc((size_t)n * sizeof(int));

        if (a == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        // Initialize sorted array
        for (int i = 0; i < n; i++) {
            a[i] = i * 2;
        }

        int key = (n - 1) * 2;
        volatile int sink = 0;

        // Linear Search timing
        clock_t t1 = clock();

        for (int r = 0; r < repetitions; r++) {
            sink += linear_search(a, n, key);
        }

        clock_t t2 = clock();

        // Binary Search timing
        for (int r = 0; r < repetitions; r++) {
            sink += binary_search(a, n, key);
        }

        clock_t t3 = clock();

        double linear_time =
            (double)(t2 - t1) / CLOCKS_PER_SEC;

        double binary_time =
            (double)(t3 - t2) / CLOCKS_PER_SEC;

        printf("\nNumber of records: %d\n", n);
        printf("Linear Search Time: %.6f seconds\n",
               linear_time);
        printf("Binary Search Time: %.6f seconds\n",
               binary_time);

        free(a);
    }

    printf("\nBenchmark completed successfully.\n");

    return 0;
}
