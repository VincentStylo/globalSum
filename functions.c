#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mpi.h>

#include "functions.h"

void global_sum(double *Result, int rank, int size, double my_value)
{   
    printf("\n\nINSIDE FUNCTION DOUBLE SUM\n");
    printf("Welcome, %d: Your value is: %f, your result is: %f \n", rank, my_value, *Result);
    *Result = my_value;
}
