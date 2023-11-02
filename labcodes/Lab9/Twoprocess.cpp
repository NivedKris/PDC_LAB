#include <mpi.h>
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv)
{
    int rank, size, sent_token = 100, recv_token;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    { 
        cout<< "NIVED KRISHNA 2021BCS0028" << endl;
    }
    if (size != 2)
    {
        cout << "Processes must be two" << endl;
        MPI_Finalize();
    }
    if (rank == 0)
    {
        MPI_Send(&sent_token, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        cout << "Token: " << sent_token << " sent from process: " << rank << endl;
    }
    if (rank == 1)
    {
        MPI_Recv(&recv_token, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        cout << "Token: " << recv_token << " received from process: " << rank
             << endl;
    }
    MPI_Finalize();
}