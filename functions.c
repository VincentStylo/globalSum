#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mpi.h>

#include "functions.h"

void global_sum(double *Result, int rank, int size, double my_value)
{
    *Result = my_value;
    double RECIEVER;
    for (int phase = 0; phase < size-1; phase++)
    {
        if (rank == 0 || rank % 2 == 0)
        {
            printf("Phase %d P %d recieving from %d, val %.1f \n",phase, rank, rank + 1, my_value);
            MPI_Recv(&RECIEVER, 1, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            *Result += RECIEVER;
            printf("Phase %d P %d sending   to   %d, val %.1f \n",phase, rank, rank + 1, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD);
        }
        else
        {
            printf("Phase %d P %d sending   to   %d, val %.1f \n",phase, rank, rank - 1, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD);
            printf("Phase %d P %d recieving from %d, val %.1f \n",phase,  rank, rank + 1, my_value);
            MPI_Recv(&RECIEVER, 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            *Result += RECIEVER;
        }
    }
}
