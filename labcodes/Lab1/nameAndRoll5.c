#include <stdio.h>
#include <omp.h>
#include <time.h>
int main()
{
    int k;
    scanf("%d", &k);
    clock_t start_time_seq = clock();
    for (int i = 0; i < k; i++)
    {
        printf("Name: VENKATA RAHUL BABU MADALA\n");
        printf("RollNo: 2021BCS0060");

    }
    clock_t end_time_seq = clock();
    double seq_execution_time = ((double)(end_time_seq - start_time_seq)) /
                                CLOCKS_PER_SEC;
    // Parallel Execution
    clock_t start_time_par = clock();
#pragma omp parallel for
    for (int i = 0; i < k; i++)
    {
printf("Name: VENKATA RAHUL BABU MADALA\n");
printf("RollNo: 2021BCS0060\n");
    }
    clock_t end_time_par = clock();
    double par_execution_time = ((double)(end_time_par - start_time_par)) /
                                CLOCKS_PER_SEC;
    printf("Sequential Execution Time: %f seconds\n", seq_execution_time);
    printf("Parallel Execution Time: %f seconds\n", par_execution_time);
    return 0;
}