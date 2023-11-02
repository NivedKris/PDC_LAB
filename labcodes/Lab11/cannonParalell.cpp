#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <mpi.h>

using namespace std;
void generateMatrix(int N, double *matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i * N + j] = static_cast<double>(rand() % 10);
        }
    }
}
// Function to perform matrix multiplication
void matrixMultiplication(int N, double *A, double *B, double *C)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i * N + j] = 0.0;
            for (int k = 0; k < N; k++)
            {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // Define an array of matrix dimensions (N)
    int dimensions[] = {3, 10, 100, 500, 1000}; 
        // Output table header
        if (rank == 0)
    {
        //type ./Test.sh after saving this program in your folder.
        
    }
    double t[sizeof(dimensions) / sizeof(dimensions[0])];
    for (int i = 0; i < sizeof(dimensions) / sizeof(dimensions[0]); i++)
    {
        int N = dimensions[i];
        double *A = new double[N * N];
        double *B = new double[N * N];
        double *C = new double[N * N];
        if (rank == 0)
        {
            generateMatrix(N, A);
            generateMatrix(N, B);
        }
        MPI_Bcast(A, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        clock_t start_time = clock();
        matrixMultiplication(N, A, B, C);
        clock_t end_time = clock();
        double execution_time = static_cast<double>(end_time - start_time) /CLOCKS_PER_SEC;
        if (rank == 0)
        {
            t[i] = execution_time;
        }
        delete[] A;
        delete[] B;
        delete[] C;
    }
    if (rank == 0)
    {
        printf(" \t\t\t\tN=3\tN=10\tN=100\tN=500\tN=1000\n");
        cout << "np=" << size << "\t\t\t\t" << fixed << setprecision(4) << t[0] << "\t" << fixed << setprecision(4) << t[1] << "\t" << fixed << setprecision(4) << t[2] << "\t" << fixed << setprecision(4) << t[3] << "\t" << fixed << setprecision(4) << t[4] << "\t\n";
    }
    MPI_Finalize();
    return 0;
}