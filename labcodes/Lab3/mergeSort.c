#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void merge(int arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] =
            L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] =
            R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                mergeSort(arr, left, middle);
            }
#pragma omp section
            {
                mergeSort(arr, middle + 1, right);
            }
        }
        merge(arr, left, middle, right);
    }
}
int main()
{
    printf("Name: NIVED KRISHNA ROLL NO: 2021BCS0028\n");
    int max_N = 1000000;
    int num_runs = 5;
    printf("N\tSerial Time\tParallel Time\n");
    for (int N = 100; N <= max_N; N *= 10)
    {
        double serial_time = 0.0;
        double parallel_time = 0.0;
        for (int run = 0; run < num_runs; run++)
        {
            int *arr = (int *)malloc(N * sizeof(int));
            for (int i = 0; i < N; i++)
                arr[i] = rand();
            double start_time = omp_get_wtime();
            mergeSort(arr, 0, N - 1);
            double end_time = omp_get_wtime();
            serial_time += end_time - start_time;
            free(arr);
            arr = (int *)malloc(N * sizeof(int));
            for (int i = 0; i < N; i++)
                arr[i] = rand();
            start_time = omp_get_wtime();
#pragma omp parallel
            {
#pragma omp single
                {
                    mergeSort(arr, 0, N - 1);
                }
            }
            end_time = omp_get_wtime();
            parallel_time += end_time - start_time;
            free(arr);
        }
        serial_time /= num_runs;
        parallel_time /= num_runs;
        printf("%d\t%.6f\t%.6f\n", N, serial_time, parallel_time);
    }
}