#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    int rank, nprocs;
    int a = 6, b = 4, c;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        cout << "NIVED KRISHNA 2021BCS0028" << endl;
        
                                                         c = a + b;
        cout << "rank : " << rank << " result = " << c << endl;
    }
    else if (rank == 1)
    {
        c = a - b;
        cout << "rank : " << rank << " result = " << c << endl;
    }
    else
    {
        c = a * b;
        cout << "rank : " << rank << " result = " << c << endl;
    }
    MPI_Finalize();
    return 0;
}