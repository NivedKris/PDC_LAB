#include "mpi.h"
#include <iostream>
using namespace std;
#define SIZE 4
main(int argc, char **argv)
{
    int num_tasks, rank, send_count, recv_count, source;
    int send_buf[SIZE][SIZE] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120},
        {130, 140, 150, 160}};
    int recv_buf[SIZE];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
    if (rank == 0)
    { cout<< "NIVED KRISHNA 2021BCS0028" << endl;
    }
    if (num_tasks == SIZE)
    {
        source = 1;
        send_count = SIZE;
        recv_count = SIZE;
        MPI_Scatter(send_buf, send_count, MPI_INT, recv_buf, recv_count,
                    MPI_INT, source, MPI_COMM_WORLD);
        cout << "rank = " << rank << " result: " << recv_buf[0] << " " << recv_buf[1] << " " << recv_buf[2] << " " << recv_buf[3] << endl;
    }
    else
    {
        cout << "No of processors must match to size " << SIZE << endl;
    }
    MPI_Finalize();
}