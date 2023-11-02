#include <time.h>
#include <stdio.h>
#include <omp.h> // Header file for OpenMP. It is already part of GCC
void main()
{
#pragma omp parallel
    {
        printf("Name: NIVED KRISHNA\n");
        printf("RollNo: 2021BCS0028");
    }
}