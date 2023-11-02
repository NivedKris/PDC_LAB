#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
    int n, token, rank, size;
    token = 100;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 4)
    {
        printf("the no.of process must be equal to 4");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    else
    {
        int patner_rank = (rank + 1) % 4;
        if (rank == 0)
        {
            MPI_Send(&token, 1, MPI_INT, patner_rank, 0, MPI_COMM_WORLD);
            printf("Name: NIVED KRISHNA 2021bcs0028\n");
            printf("Token = %d send from %d to %d\n", token, rank, patner_rank);
            MPI_Recv(&token, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else
        {
            MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&token, 1, MPI_INT, patner_rank, 0, MPI_COMM_WORLD);
            printf("Token = %d send from %d to %d\n", token, rank, patner_rank);
        }
    }
    MPI_Finalize();
}