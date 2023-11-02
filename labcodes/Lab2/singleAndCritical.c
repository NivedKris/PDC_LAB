#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
int main()
{
#pragma omp parallel num_threads(3)
    {
#pragma omp single
        printf("Single: NIVED KRISHNA 2021BCS0028\n");
#pragma omp critical
        printf("Critical: NIVED KRISHNA 2021BCS0028\n");
    }
    return 0;
}