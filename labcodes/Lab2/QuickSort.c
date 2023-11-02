#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
void quickSort(int arr[], int left, int right)
{
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j)
    {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}
void parallelQuickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int i = left, j = right;
        int pivot = arr[(left + right) / 2];
        while (i <= j)
        {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i <= j)
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }
#pragma omp parallel sections
        {
#pragma omp section
            parallelQuickSort(arr, left, j);
#pragma omp section
            parallelQuickSort(arr, i, right);
        }
    }
}
int main()
{
    srand(time(NULL));
    printf("NIVED KRISHNA\n");
    printf("2021BCS0028\n");
    int N[] = {10000, 100000, 1000000}; // Different values of N
    int num_N = sizeof(N) / sizeof(N[0]);
    for (int k = 0; k < num_N; k++)
    {
        int *arr = (int *)malloc(N[k] * sizeof(int));
        int *arrParallel = (int *)malloc(N[k] * sizeof(int));
        for (int i = 0; i < N[k]; i++)
        {
            arr[i] = rand() % 10000;
            arrParallel[i] = arr[i];
        }
        double startTime = omp_get_wtime();
        quickSort(arr, 0, N[k] - 1);
        double serialTime = omp_get_wtime() - startTime;
        startTime = omp_get_wtime();
#pragma omp parallel
        {
#pragma omp single nowait
            parallelQuickSort(arrParallel, 0, N[k] - 1);
        }
        double parallelTime = omp_get_wtime() - startTime;
        printf("N = %d:\n", N[k]);
        printf("Serial QuickSort Time: %f seconds\n", serialTime);
        printf("Parallel QuickSort Time: %f seconds\n", parallelTime);
        free(arr);
        free(arrParallel);
    }
    return 0;
}