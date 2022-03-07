#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mpi.h>

#include "functions.h"

int phaseSum(int x)
{
    return log(x) / log(2);
}

void global_sum(double *Result, int rank, int size, double my_value)
{   printf("This is my_value: %f\n", my_value);
    if (rank == 0)
    {
        MPI_Send(&my_value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&my_value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received number %f from process 0 \n", my_value);
    }
}
