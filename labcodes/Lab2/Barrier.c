#include <stdio.h>
#include <omp.h>
const int numThreads = 3;
const int numIterations = 4;
int main()
{
    int counter = 0;
    printf("NIVED KRISHNA\n");
    printf("2021BCS0028\n\n");
    printf("Without Barrier:\n");
#pragma omp parallel num_threads(numThreads)
    {
        for (int i = 0; i < numIterations; ++i)
        {
#pragma omp critical
            {
                counter++;
                printf("Thread %d: Counter = %d\n", omp_get_thread_num(),
                       counter);
            }
        }
    }
    counter = 0;
    printf("\nWith Barrier:\n");
#pragma omp parallel num_threads(numThreads)
    {
        for (int i = 0; i < numIterations; ++i)
        {
#pragma omp critical
            {
                counter++;
                printf("Thread %d: Counter = %d\n", omp_get_thread_num(),
                       counter);
            }
#pragma omp barrier
        }
    }
    return 0;
}