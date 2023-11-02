#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <omp.h>
using namespace std;
void gaussianElimination(vector<vector<double>> &A, vector<double> &b)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
#pragma omp parallel for num_threads(omp_get_num_threads())
        for (int j = i + 1; j < n; j++)
        {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
            {
                cout << "Thread " << omp_get_thread_num() << " - Augumented matrix after iteration " << i + j << " : " << endl;
                                                             for (int r = 0; r < n; r++)
                {
                    for (int c = 0; c < n; c++)
                    {
                        cout << A[r][c] << "\t";
                    }
                    cout << b[r] << endl;
                }
                cout << endl;
            }
        }
    }
}
vector<double> backwardSubstitution(const vector<vector<double>> &A, const vector<double> &b)
{
    int n = A.size();
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
        {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    return x;
}
int main()
{
    printf("NIVED KRISHNA\n");
    printf("2021BCS0028\n");

    int n, m, num_threads;
    ifstream input("matrix.txt");
    if (!input.is_open())
    {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }
    input >> n;
    input >> m;
    vector<vector<double>> A(n, vector<double>(n, 0.0));
    vector<double> b(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            input >> A[i][j];
        }
        input >> b[i];
    }
    input.close();
    omp_set_num_threads(4);
    double start_time = omp_get_wtime();
    gaussianElimination(A, b);
    vector<double> x = backwardSubstitution(A, b);
    double end_time = omp_get_wtime();
    cout << "Solutions of variable matrix X is:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "] = " << x[i] << endl;
    }
    double execution_time = end_time - start_time;
    cout << "Execution time: " << execution_time << " seconds" << endl;
    return 0;
}