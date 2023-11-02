#include <mpi.h>
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv)
{
    int rank, size;
    int arr[4] = {10, 85, 150, 42};
    int data;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    { 
         cout<< "NIVED KRISHNA 2021BCS0028" << endl;
    }
    MPI_Scatter(&arr, 1, MPI_INT, &data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    cout << "Scattered: " << data << " to process: " << rank << endl;
    MPI_Finalize();
}