#include<mpi.h>
#include <bits/stdc++.h>
    using namespace std;
double f(double x)
{
    return 4 / (1 + x * x);
}
double Trap(double left_endpt, double right_endpt, int trap_count,
            double base_len)
{
    double estimate, x;
    int i;
    estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
    for (i = 1; i <= trap_count - 1; i++)
    {
        x = left_endpt + i * base_len;
        estimate += f(x);
    }
    estimate = estimate * base_len;
    return estimate;
}
int main(int argc, char **argv)
{
    int rank, size, n = 1024, local_n;
    double a = 0.0, b = 1.0, h, local_a, local_b;
    double local_int, total_int;
    int source;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    { 
            cout<< "NIVED KRISHNA 2021BCS0028" << endl;
    }
    h = (b - a) / n;
    local_n = n / size;
    local_a = a + rank * local_n * h;
    cout << "rank calculating local_a = " << rank << endl;
    local_b = local_a + local_n * h;
    cout << "rank calculating local_b = " << rank << endl;
    local_int = Trap(local_a, local_b, local_n, h);
    cout << "rank calculating local_int = " << rank << endl;
    if (rank != 0)
    {
        MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        total_int = local_int;
        for (source = 1; source < size; source++)
        {
            MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_int += local_int;
        }
    }
    if (rank == 0)
    {
        cout << "\n\nWith n = " << n << " trapezoids our estimate of the integral from " << a << " to " << b << " is " << total_int <<endl;
    }
    MPI_Finalize();
}