#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <omp.h>

using namespace std;

// Serial Gaussian elimination with row pivoting
void serialGaussianElimination(vector<vector<double>> &A, vector<double> &b, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Find pivot row and swap if necessary
        int pivotRow = i;
        for (int j = i + 1; j < n; j++)
        {
            if (abs(A[j][i]) > abs(A[pivotRow][i]))
            {
                pivotRow = j;
            }
        }
        if (pivotRow != i)
        {
            swap(A[i], A[pivotRow]);
            swap(b[i], b[pivotRow]);
        }

        // Eliminate lower triangular elements
        for (int j = i + 1; j < n; j++)
        {
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k] -= ratio * A[i][k];
            }
            b[j] -= ratio * b[i];
        }
    }
}

// Serial backward substitution
void serialBackwardSubstitution(vector<vector<double>> &A, vector<double> &b, vector<double> &x, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
        {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

// Parallel Gaussian elimination with row pivoting
void parallelGaussianElimination(vector<vector<double>> &A, vector<double> &b, int n)
{
    for (int i = 0; i < n; i++)
    {
        int pivotRow = i;

#pragma omp parallel for
        for (int j = i + 1; j < n; j++)
        {
            int tid = omp_get_thread_num();
            if (abs(A[j][i]) > abs(A[pivotRow][i]))
            {
                pivotRow = j;
            }
#pragma omp critical
            {
                cout << "Thread " << tid << " is checking row " << j << endl;
            }
        }

        if (pivotRow != i)
        {
#pragma omp parallel for
            for (int k = i; k < n; k++)
            {
                int tid = omp_get_thread_num();
                swap(A[i][k], A[pivotRow][k]);
#pragma omp critical
                {
                    cout << "Thread " << tid << " is swapping columns " << i << " and " << k << endl;
                }
            }
            swap(b[i], b[pivotRow]);
        }

#pragma omp parallel for
        for (int j = i + 1; j < n; j++)
        {
            int tid = omp_get_thread_num();
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k] -= ratio * A[i][k];
            }
            b[j] -= ratio * b[i];
#pragma omp critical
            {
                cout << "Thread " << tid << " is eliminating row " << j << endl;
            }
        }
    }
}

// Parallel and safe
void parallelGaussianEliminationCritical(vector<vector<double>> &A, vector<double> &b, int n)
{
    for (int i = 0; i < n; i++)
    {
        int pivotRow = i;

#pragma omp parallel for
        for (int j = i + 1; j < n; j++)
        {
            int tid = omp_get_thread_num();
            if (abs(A[j][i]) > abs(A[pivotRow][i]))
            {
#pragma omp critical
                {
                    pivotRow = j;
                }
            }
#pragma omp critical
            {
                cout << "Thread " << tid << " is checking row " << j << endl;
            }
        }

        if (pivotRow != i)
        {
#pragma omp parallel for
            for (int k = i; k < n; k++)
            {
                int tid = omp_get_thread_num();
                swap(A[i][k], A[pivotRow][k]);
#pragma omp critical
                {
                    cout << "Thread " << tid << " is swapping columns " << i << " and " << k << endl;
                }
            }
            swap(b[i], b[pivotRow]);
        }

#pragma omp parallel for
        for (int j = i + 1; j < n; j++)
        {
            int tid = omp_get_thread_num();
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k] -= ratio * A[i][k];
            }
            b[j] -= ratio * b[i];
#pragma omp critical
            {
                cout << "Thread " << tid << " is eliminating row " << j << endl;
            }
        }
    }
}

int main()
{
    cout << "NIVED KRISHNA" << endl;
    cout << "2021BCS0028" << endl;

    int n, _;
    ifstream input("Matrix.txt"); // Change this to your input file name
    input >> n;
    input >> _;

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);

    // Read A and b from the input file
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            input >> A[i][j];
        }
        input >> b[i];
    }

    input.close();

    // Serial version
    vector<double> x_serial(n);
    double start_time = omp_get_wtime();
    serialGaussianElimination(A, b, n);
    serialBackwardSubstitution(A, b, x_serial, n);
    double end_time = omp_get_wtime();
    double serial_time = end_time - start_time;

    cout << "Serial solution:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "] = " << x_serial[i] << endl;
    }
    cout << "Serial execution time: " << serial_time << " seconds" << endl;

    // Parallel version
    vector<vector<double>> A_parallel = A;
    vector<double> b_parallel = b;
    vector<double> x_parallel(n);

    start_time = omp_get_wtime();
    parallelGaussianElimination(A_parallel, b_parallel, n);
    serialBackwardSubstitution(A_parallel, b_parallel, x_parallel, n);
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;

    cout << "Parallel solution:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "] = " << x_parallel[i] << endl;
    }
    cout << "Parallel execution time: " << parallel_time << " seconds" << endl;

    // Parallel and safe version
    vector<vector<double>> A_parallel_critical = A;
    vector<double> b_parallel_critical = b;
    vector<double> x_parallel_critical(n);

    start_time = omp_get_wtime();
    parallelGaussianEliminationCritical(A_parallel_critical, b_parallel_critical, n);
    serialBackwardSubstitution(A_parallel_critical, b_parallel_critical, x_parallel_critical, n);
    end_time = omp_get_wtime();
    double parallel_critical_time = end_time - start_time;

    cout << "Parallel and safe solution:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "] = " << x_parallel_critical[i] << endl;
    }
    cout << "Parallel and safe execution time: " << parallel_critical_time << " seconds" << endl;

    return 0;
}
