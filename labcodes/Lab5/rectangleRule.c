#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
double f(double x)
{
    return 4.0 / (1.0 + x * x);
}
double integrate(double (*func)(double), double a, double b, int num_intervals)
{
    double interval_width = (b - a) / num_intervals;
    double sum = 0.0;
    for (int i = 0; i < num_intervals; ++i)
    {
        double x1 = a + i * interval_width;
        double x2 = a + (i + 1) * interval_width;
        sum += 0.5 * (func(x1) + func(x2)) * interval_width;
    }
    return sum;
}
int main()
{
    printf("NAME: NIVED KRISHNA \n");
    printf("ROLL NUMBER: 2021BCS0028\n");
    int num_intervals;
    printf("Enter the number of intervals: ");
    scanf("%d", &num_intervals);
    const double interval_width = 1.0 / num_intervals;
    double integral_serial = 0.0, integral_parallel = 0.0;
    double x;
    int num_threads;
    double pi = 0.0;
    double a = 0.0;
    double b = 1.0;
    // Integration Version
    double start_time_integration = omp_get_wtime();
    double integral = integrate(f, a, b, num_intervals);
    double end_time_integration = omp_get_wtime();
    printf("Classical Pi (Integration Method): %lf\n", integral);
    printf("Integration Execution Time: %lf seconds\n", end_time_integration -
                                                            start_time_integration);
    printf("\n");
    // a) Serial version
    double start_time_serial = omp_get_wtime();
    for (int i = 0; i < num_intervals; ++i)
    {
        x = (i + 0.5) * interval_width;
        integral_serial += f(x);
    }
    pi = interval_width * integral_serial;
    double end_time_serial = omp_get_wtime();
    printf("Serial Pi: %lf\n", pi);
    printf("Serial Execution Time: %lf seconds\n", end_time_serial -
                                                       start_time_serial);
    printf("Absolute Difference (Serial vs. Classical): %lf\n", fabs(pi -
                                                                     integral));
    printf("\n");
    // b) Parallel version using reduction clause
    integral_parallel = 0.0;
    double start_time_parallel = omp_get_wtime();
#pragma omp parallel
    {
        num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        double local_sum = 0.0;
        int chunk_size = num_intervals / num_threads;
        int start = thread_id * chunk_size;
        int end = (thread_id == num_threads - 1) ? num_intervals : (thread_id + 1) * chunk_size;
        for (int i = start; i < end; ++i)
        {
            x = (i + 0.5) * interval_width;
            local_sum += f(x);
        }
#pragma omp atomic
        integral_parallel += local_sum;
    }
    pi = interval_width * integral_parallel;
    double end_time_parallel = omp_get_wtime();
    printf("Parallel Pi (with reduction): %lf\n", pi);
    printf("Number of Threads Involved: %d\n", num_threads);
    printf("Parallel Execution Time: %lf seconds\n", end_time_parallel -
                                                         start_time_parallel);
    printf("Absolute Difference (Parallel vs. Classical): %lf\n", fabs(pi -
                                                                       integral));
    printf("\n");
    printf("Area Calculated by Each Thread:\n");
    for (int i = 0; i < num_threads; ++i)
    {
        int start = i * (num_intervals / num_threads);
        int end = (i == num_threads - 1) ? num_intervals : (i + 1) * (num_intervals / num_threads);
        printf("Thread %d calculated the area from step %d to %d\n", i, start,
               end);
    }
    printf("\n");
    // c) Handling race condition using critical section
    integral_parallel = 0.0;

    double start_time_critical = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < num_intervals; ++i)
    {
        x = (i + 0.5) * interval_width;
#pragma omp critical
        integral_parallel += f(x);
    }
    pi = interval_width * integral_parallel;
    double end_time_critical = omp_get_wtime();
    printf("Parallel Pi (with critical section): %lf\n", pi);
    printf("Critical Execution Time: %lf seconds\n", end_time_critical -
                                                         start_time_critical);
    printf("\n");
    // Handling race condition using atomic
    integral_parallel = 0.0;
    double start_time_atomic = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < num_intervals; ++i)
    {
        x = (i + 0.5) * interval_width;
#pragma omp atomic
        integral_parallel += f(x);
    }
    pi = interval_width * integral_parallel;
    double end_time_atomic = omp_get_wtime();
    printf("Parallel Pi (with atomic): %lf\n", pi);
    printf("Atomic Execution Time: %lf seconds\n", end_time_atomic -
                                                       start_time_atomic);
    printf("\n");
    // Handling race condition using reduction clause
    integral_parallel = 0.0;
    double start_time_reduction = omp_get_wtime();
#pragma omp parallel for reduction(+ : integral_parallel)
    for (int i = 0; i < num_intervals; ++i)
    {
        x = (i + 0.5) * interval_width;
        integral_parallel += f(x);
    }
    pi = interval_width * integral_parallel;
    double end_time_reduction = omp_get_wtime();
    printf("Parallel Pi (with reduction): %lf\n", pi);
    printf("Reduction Execution Time: %lf seconds\n", end_time_reduction -
                                                          start_time_reduction);
    printf("\n");
    return 0;
}