#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <mpi.h>

#include "functions.h"
bool exponentCheck (int size){
      if ((size != 0 && (size & (size - 1)) == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int phaseSum(int x)
{
    return log(x) / log(2);
}

void global_sum(double *Result, int rank, int size, double my_value)
{
    *Result = my_value;
    double RECIEVER;
    int BINARY;
    int phaseMax = phaseSum(size);
    for (int phase = 0; phase < phaseMax; phase++)
    {
        BINARY = (rank^(phase+1));
        if (rank % 2 == 0)
        {
            MPI_Recv(&RECIEVER, 1, MPI_DOUBLE, BINARY, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Phase %d P %d recieving from %d, val %.1f \n", phase, rank, BINARY, RECIEVER);
            printf("Phase %d P %d sending   to   %d, val %.1f \n",phase, rank, BINARY, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, BINARY, 1, MPI_COMM_WORLD);
            *Result += RECIEVER;
        }
        else
        {
            printf("Phase %d P %d sending   to   %d, val %.1f \n",phase ,rank, BINARY, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, BINARY, 1, MPI_COMM_WORLD);
            MPI_Recv(&RECIEVER, 1, MPI_DOUBLE, BINARY, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Phase %d P %d recieving from %d, val %.1f \n",phase ,rank, BINARY, RECIEVER);
            *Result += RECIEVER;
        }
        my_value = *Result;
        MPI_Barrier(MPI_COMM_WORLD);
    }
}
