#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10000
int arr[SIZE];

int main() {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 100;

    // ---- Serial Execution ----
    double start = omp_get_wtime();
    long long serial_sum = 0;
    for (int i = 0; i < SIZE; i++)
        serial_sum += arr[i];
    double end = omp_get_wtime();

    double serial_time = end - start;
    if (serial_time == 0) serial_time = 0.000001;

    int thread_counts[] = {4, 5, 10};

    // ---- Parallel Execution for each thread count ----
    for (int t = 0; t < 3; t++) {
        int num_threads = thread_counts[t];
        long long sum_total = 0;

        start = omp_get_wtime();

        #pragma omp parallel for num_threads(num_threads) reduction(+:sum_total)
        for (int i = 0; i < SIZE; i++) {
            sum_total += arr[i];
        }

        end = omp_get_wtime();
        double parallel_time = end - start;
        if (parallel_time == 0) parallel_time = 0.000001;

        double speedup = serial_time / parallel_time;

        printf("Threads: %d\n", num_threads);
        printf("Parallel Sum: %lld\n", sum_total);
        printf("Parallel Time: %.3f ms\n", parallel_time * 1000);
        printf("Speedup: %.2fx\n\n", speedup);
    }

    return 0;
}