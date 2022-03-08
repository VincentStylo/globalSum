#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mpi.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char **argv)
{
    int rank, size, value;
    double sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1 || exponentCheck(size) == false){
        printf("%d is incompatible\n", size);
        exit(0);
    }
    value = rank;
    global_sum(&sum, rank, size, value);
    printf("FINAL IN MAIN: %d has Sum = %f \n", rank, sum);
    MPI_Finalize();
    return 0;
}
