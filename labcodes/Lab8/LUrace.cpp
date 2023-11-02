#include <iostream>
#include <fstream>
#include <ctime>
#include <omp.h>
using namespace std;
int main()
{
    ifstream inputFile("matrix2.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error: Cannot open input file." << endl;
        return 1;
    }
    int n, m;
    inputFile >> n;
    inputFile >> m;
    double **A = new double *[n];
    double *b = new double[n];
    double *y = new double[n]; // Store intermediate values of y
    for (int i = 0; i < n; i++)
    {
        A[i] = new double[n];
        for (int j = 0; j < n + 1; j++)
        {
            if (j == n)
            {
                inputFile >> b[i];
            }
            else
            {
                inputFile >> A[i][j];
            }
        }
    }
    inputFile.close();
    double start_time = omp_get_wtime();
    // Parallelized LU decomposition without pivot
    for (int k = 0; k < n; k++)
    {
#pragma omp parallel for
        for (int i = k + 1; i < n; i++)
        {
            double factor = A[i][k] / A[k][k];
#pragma omp critical
            {
            
                    A[i][k] = factor; // Store the factor in the lower triangular
                for (int j = k + 1; j < n; j++)
                {
                    A[i][j] -= factor * A[k][j];
                }
                b[i] -= factor * b[k];
            }
        }
    }
    // Initialize y
    for (int i = 0; i < n; i++)
    {
        y[i] = b[i];
    }
    double end_time = omp_get_wtime();
    // Print both the upper and lower triangular matrices
    cout << "Upper Triangular Matrix:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j >= i)
            {
                cout << A[i][j] << "\t";
            }
            else
            {
                cout << "0\t";
            }
        }
        cout << endl;
    }
    cout << "Lower Triangular Matrix:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                cout << "1\t"; // Diagonal elements of lower triangular matrix
            }
            else if (j < i)
            {
                cout << A[i][j] << "\t";
            }
            else
            {
                cout << "0\t";
            }
        }
        cout << endl;
    }
    // Print intermediate values of y
    cout << "Intermediate Values of y:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "y[" << i << "] = " << y[i] << endl;
    }
    // Backward substitution
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            y[i] -= A[i][j] * y[j];
        }
        y[i] /= A[i][i];
    }
    // Print the solution and execution time
    cout << "Solution x:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "] = " << y[i] << endl;
    }
    cout << "Execution Time: " << (end_time - start_time) << " seconds" << endl;
    // Free memory
    for (int i = 0; i < n; i++)
    {
        delete[] A[i];
    }
    delete[] A;
    delete[] b;
    delete[] y;
    return 0;
}