
/*Interfaces*/
#include "module.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <omp.h>

/*Varaible of high value to reserve memory*/
#define DATA_SZ (1024*1024*64*3)

/*Memory space acordin reserve memory value*/
static double MEM_CHUNK[DATA_SZ];
/**
 * @brief Main function
 *
 * @param argc That is the arguments count
 * @param argv That is the arguments values
 * @return 0 if everything is ok or another number in error case
 */
int main(int argc, char *argv[])
{
    double *Ma, *Mb, *Mc;
    int N, Nthreads;
    
    if (argc != 3)
    {
        printf("./MMPosix <matrix size> <# of threads>\n");
        return -1;
    }

    /*Init of global variables*/
    N = atof(argv[1]);        /* Matrix's size.*/
    Nthreads = atof(argv[2]); /* Number of threads.*/
    if (Nthreads > omp_get_max_threads())
    {
        printf("El número de hilos debe ser menor o igual a %d\n", omp_get_max_threads());
        return -1;
    }

    /*Memory creation and reserce for each matrix*/
    Ma = MEM_CHUNK;
	Mb = Ma + N*N;
	Mc = Mb + N*N;
    initMatrix(N,Ma, Mb, Mc);

    printMatrix(N,Ma);
    printMatrix(N,Mb);
    sampleStart();
    MM1cOMP(Nthreads, N, Ma, Mb, Mc);
    sampleEnd();
    /* free(Ma);
    // free(Mb);
    // free(Mc);*/
    printMatrix(N,Mc);
    return EXIT_SUCCESS;
}