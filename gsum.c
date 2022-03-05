#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include "function.h"

int main(intargc, char **argv)
{
 int rank, size, value;
 double sum;

 MPI_INIT(&argc, &argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 MPI_ COMM_WORLD, &size);
 value = rank;
 global_sum(&sum, rank, size, value);
 
 printf("FINAL IN MAIN: %d has Sum = %f \n", rank, sum);

 MPI_Finalize();
 return 0;

}
