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
    const int num_intervals = 100;
    const double interval_width = 1.0 / num_intervals;
    double integral_serial = 0.0, integral_parallel = 0.0;
    double x;
    double pi = 0.0;
    double a = 0.0;
    double b = 1.0;
    // Integration Version
    double start_time_integration = omp_get_wtime();
    double integral = integrate(f, a, b, num_intervals);
    double end_time_integration = omp_get_wtime();
    printf("NAME: NIVED KRISHNA\n");
    printf("ROLL NO: 2021BCS0028\n\n");
    printf("Approximate value of pi using integration method: %lf\n",
           integral);
    // printf("Integration Execution Time: %lf seconds\n", end_time_integration- start_time_integration);
// Serial version
double start_time_serial = omp_get_wtime();
for (int i = 0; i <= num_intervals; ++i)
{
    x = i * interval_width;
    integral_serial += f(x);
}
pi = interval_width * (integral_serial - 0.5 * (f(0) + f(1)));
double end_time_serial = omp_get_wtime();
printf("Serial Pi: %lf\n", pi);
printf("Serial Execution Time: %lf seconds\n", end_time_serial -
                                                   start_time_serial);
// Parallel version using reduction clause
integral_parallel = 0.0;
double start_time_parallel = omp_get_wtime();
#pragma omp parallel for reduction(+ : integral_parallel)
for (int i = 0; i <= num_intervals; ++i)
{
    x = i * interval_width;
    integral_parallel += f(x);
}
pi = interval_width * (integral_parallel - 0.5 * (f(0) + f(1)));
double end_time_parallel = omp_get_wtime();
printf("Parallel Pi (with reduction): %lf\n", pi);
printf("Parallel Execution Time: %lf seconds\n", end_time_parallel -
                                                     start_time_parallel);
// Handling race condition using critical section
integral_parallel = 0.0;
double start_time_critical = omp_get_wtime();
#pragma omp parallel for
for (int i = 0; i <= num_intervals; ++i)
{
    x = i * interval_width;
#pragma omp critical
    integral_parallel += f(x);
}
pi = interval_width * (integral_parallel - 0.5 * (f(0) + f(1)));
double end_time_critical = omp_get_wtime();
printf("Parallel Pi (with critical section): %lf\n", pi);
printf("Critical Execution Time: %lf seconds\n", end_time_critical -
                                                     start_time_critical);
// Handling race condition using atomic
integral_parallel = 0.0;
double start_time_atomic = omp_get_wtime();
#pragma omp parallel for
for (int i = 0; i <= num_intervals; ++i)
{
    x = i * interval_width;
#pragma omp atomic
    integral_parallel += f(x);
}
pi = interval_width * (integral_parallel - 0.5 * (f(0) + f(1)));
double end_time_atomic = omp_get_wtime();
printf("Parallel Pi (with atomic): %lf\n", pi);
printf("Atomic Execution Time: %lf seconds\n", end_time_atomic -
                                                   start_time_atomic);
// Handling race condition using reduction clause
integral_parallel = 0.0;
double start_time_reduction = omp_get_wtime();
#pragma omp parallel for reduction(+ : integral_parallel)
for (int i = 0; i <= num_intervals; ++i)
{
    x = i * interval_width;
    integral_parallel += f(x);
}
pi = interval_width * (integral_parallel - 0.5 * (f(0) + f(1)));
double end_time_reduction = omp_get_wtime();
printf("Parallel Pi (with reduction): %lf\n", pi);
printf("Reduction Execution Time: %lf seconds\n", end_time_reduction -
                                                      start_time_reduction);
return 0;
}