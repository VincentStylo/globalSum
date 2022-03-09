#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <mpi.h>
#include "functions.h"

bool exponentCheck(int size)
{
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
    double TEMP;
    int PAIR;
    int phaseMax = phaseSum(size);
    unsigned bitmask = 1;
    for (int phase = 0; phase < phaseMax; phase++)
    {
        // Partner is Chosen
        PAIR = (rank ^ bitmask);
        if (rank < PAIR)
        {
            // Sending
            printf("Phase %d P %d sending   to   %d, val %.1f \n", phase, rank, PAIR, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, PAIR, 0, MPI_COMM_WORLD);

            // Recieving
            MPI_Recv(&TEMP, 1, MPI_DOUBLE, PAIR, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Phase %d P %d recieving from %d, val %.1f \n", phase, rank, PAIR, TEMP);

            // Sending to result
            *Result += TEMP;
        }
        else
        {

            // Recieving
            MPI_Recv(&TEMP, 1, MPI_DOUBLE, PAIR, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Phase %d P %d recieving from %d, val %.1f \n", phase, rank, PAIR, TEMP);

            // Sending to Result
            *Result += TEMP;

            // Sending
            printf("Phase %d P %d sending   to   %d, val %.1f \n", phase, rank, PAIR, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, PAIR, 0, MPI_COMM_WORLD);
        }

        // Sends Value to Result
        bitmask <<= 1;
        my_value = *Result;
        MPI_Barrier(MPI_COMM_WORLD);
    }
}
