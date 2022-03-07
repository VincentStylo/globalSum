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
{
    *Result = my_value;
    double RECIEVER;
    int STEP;
    int phaseMax = phaseSum(size);
    for (int phase = 0; phase < phaseMax; phase++)
    {
        STEP = (int)pow(2,phase);
        if (rank == 0 || rank % 2 == 0)
        {
            
            printf("Phase %d P %d recieving from %d, val %.1f \n", phase, rank, rank + STEP, my_value);
            MPI_Recv(&RECIEVER, 1, MPI_DOUBLE, rank + STEP, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            *Result += RECIEVER;
            printf("Phase %d P %d sending   to   %d, val %.1f \n",phase, rank, rank + STEP, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, rank + STEP, 1, MPI_COMM_WORLD);
        }
        else
        {
            printf("Phase %d P %d sending   to   %d, val %.1f \n",phase ,rank, rank - STEP, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, rank - STEP, 1, MPI_COMM_WORLD);
            printf("Phase %d P %d recieving from %d, val %.1f \n",phase ,rank,  - STEP, my_value);
            MPI_Recv(&RECIEVER, 1, MPI_DOUBLE, rank - STEP, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            *Result += RECIEVER;
        }
    }
}
