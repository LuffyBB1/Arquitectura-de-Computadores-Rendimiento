#include "module.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <omp.h>
#include <pthread.h>
/*CONSTANTS*/
struct timespec inicio, fin;

/* -------------------------------------Funciones ------------------------------------*/
/**
 * @brief Function that starts the time measure
 *
 */
void sampleStart()
{
	clock_gettime(CLOCK_MONOTONIC, &inicio);
}
/**
 * @brief Function that ends the time measure
 *
 */
void sampleEnd()
{
	double totalTime;
	clock_gettime(CLOCK_MONOTONIC, &fin);
	totalTime = (fin.tv_sec - inicio.tv_sec) * 1e9;
	totalTime = (totalTime + (fin.tv_nsec - inicio.tv_nsec)) * 1e-9;
	printf("%f\n", totalTime);
}

/**
 * @brief Function that will be sent to each thread, that makes the matrix multiplication.
 * The matrix A divides in slices, in function with the dimension and the number of threads that requires the
 * user.
 *
 * Note: the function will be void, and this returns a potential warning. Think in it to improve it
 * @param arg that has the thread struct with the needed info for the thread
 */
void *multMM(void *arg)
{
	int i, j, k, idTh, N, Nthreads, portionSize, initRow, endRow;
	double **Ma, **Mb, **Mr, sum;
	idTh = ((threadsArguments *)arg)->idThread;
	Ma = ((threadsArguments *)arg)->matrixA;
	Mb = ((threadsArguments *)arg)->matrixB;
	Mr = ((threadsArguments *)arg)->matrixR;
	N = ((threadsArguments *)arg)->matrixSize;
	Nthreads = ((threadsArguments *)arg)->numThreads;
	portionSize = N / Nthreads;		   /*It is determined the portion of matrix A to send to each thread*/
	initRow = idTh * portionSize;	   /*It is passed the beggining of the row*/
	endRow = (idTh + 1) * portionSize; /*It is passed the end of the row*/
	for (i = initRow; i < endRow; i++)
	{
		for (j = 0; j < N; ++j)
		{
			sum = 0;
			for (k = 0; k < N; k++)
			{
				sum += Ma[i][k] * Mb[k][j];
			}
			Mr[i][j] = sum;
		}
	}
	return arg;
}

/**
 * @brief Function that generates a truly random number using getpid() function
 *
 * @return: Random number between 0.001 and 9.999 with double precision
 */
double randNumber()
{
	float min = 0.001, max = 9.999;
	static int first = -1;
	if (first == (first < 0))
	{
		srand(time(NULL) + getpid());
	}
	if (min >= max)
	{
		const int NAN = -1e9;
		return errno = EDOM, NAN;
	}
	return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

/**
 * @brief Gives values for each space of a matrix
 *
 * @param SZ Size of the matrix
 * @param Ma That is the matrix A to initialize
 * @param Mb That is the matrix B to initialize
 * @param Mr That is the resultant matrix to initialize
 */
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr)
{
	int i, j;
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			Ma[j + i * SZ] = 3.2 * (i + j);
			Mb[j + i * SZ] = 2.4 * (i - j);
			/* Ma[j+i*SZ] = randNumber();*/
			/*Mb[j+i*SZ] = randNumber(); */
			Mr[j + i * SZ] = 0.0;
		}
	}
}
/**
 * @brief Function that allows
 *
 * @param SZ
 * @param M
 */
void printTransposed(int SZ, double *M)
{
	if (SZ<5)
	{
		int i, j;
		for (i = 0; i < SZ; ++i)
		{
			for (j = 0; j < SZ; ++j)
			{
				printf("  %f  ", M[j * SZ + i]);
			}
			printf("\n");
		}
		printf("----------------------------");
		printf("\n");
	}
}
/**
 * @brief Print a matrix
 *
 * @param SZ  that is the matrix size
 * @param M that is the matrix to print
 */
void printMatrix(int SZ, double *M)
{
	int i, j;
	if (SZ < 5)
	{
		for (i = 0; i < SZ; ++i)
		{
			for (j = 0; j < SZ; ++j)
			{
				printf("  %f  ", M[j + i * SZ]);
			}
			printf("\n");
		}
		printf("----------------------------");
		printf("\n");
	}
}

/**
 * @brief Function that makes the matrix multiplication between two matrixes and the result is saved in another matrix
 *
 * @param size  Matrix size
 * @param Ma Matrix A
 * @param Mb Matrix B
 * @param Mr Result matrix
 */
void MM1c(int size, double *Ma, double *Mb, double *Mr)
{
	int i, j, k;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			/*Necesita puteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + j;
			for (k = 0; k < size; ++k, pA++, pB += size)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}

/**
 * @brief Function that makes the matrix multiplication between two matrixes and the result is saved in another matrix. This uses Open MP
 *
 * @param threads Threads number
 * @param size  Matrix size
 * @param a Matrix A
 * @param b Matrix B
 * @param c Result matrix
 */
void MM1cOMP(int threads, int size, double *a, double *b, double *c)
{
	omp_set_num_threads(threads);
#pragma omp parallel
	{
		int i, j, k;
#pragma omp for
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				/*Necesita puteros auxiliares*/
				double *pA, *pB;
				double auxiliarSum = 0.0;
				pA = a + (i * size);
				pB = b + j;
				for (k = 0; k < size; ++k, pA++, pB += size)
				{
					auxiliarSum += (*pA * *pB);
				}
				c[i * size + j] = auxiliarSum;
			}
		}
	}
}

/**
 * @brief Function that makes the matrix multiplication between two matrixes and the result is saved in another matrix
 * This multiplication is implemented making the product with Mb trasposed
 *
 * @param size  Matrix size
 * @param Ma Matrix A
 * @param Mb Matrix B
 * @param Mr Result matrix
 */
void MM1f(int size, double *Ma, double *Mb, double *Mr)
{
	int i, j, k;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			/*Necesita puteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + (j * size);
			for (k = 0; k < size; ++k, pA++, pB++)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}
/**
 * @brief Function that makes the matrix multiplication between two matrixes and the result is saved in another matrix. This uses Open MP
 *
 * @param threads Threads number
 * @param size  Matrix size
 * @param a Matrix A
 * @param b Matrix B transposed
 * @param c Result matrix
 */
void MM1fOMP(int threads, int size, double *a, double *b, double *c)
{
	omp_set_num_threads(threads);
#pragma omp parallel
	{
		int i, j, k;
#pragma omp for
		
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				/*Necesita puteros auxiliares*/
				double *pA, *pB;
				double sumaAuxiliar = 0.0;
				pA = a + (i * size);
				pB = b + (j * size);
				for (k = 0; k < size; ++k, pA++, pB++)
				{
					sumaAuxiliar += (*pA * *pB);
				}
				c[i * size + j] = sumaAuxiliar;
			}
		}
	}
}
/****************** Functions for posix (program using threads)**************************/

/**
 * @brief Function that makes a memory reservation for a matrix
 *
 * @param size that is the matrix size that is needed to reserved
 * @return double**
 */
double **memReserve(int size)
{
	/* Memory reserve of dimenion NxN double*/
	double *val = (double *)malloc(size * size * sizeof(double));

	int i;

	/* Doble pointer Vector reserve of dimenion size*/
	double **ptr = (double **)malloc(size * size * sizeof(double *));
	/* Iteration with the purpose that each pointer position itself in the memory reserve*/
	for (i = 0; i < size; ++i)
	{
		ptr[i] = &val[i * size];
	}
	return ptr;
}

/**
 * @brief Gives values for each space of a matrix
 *
 * @param MA Matrix A
 * @param MB Matrix B
 * @param MC Matrix C
 * @param size Matrix size
 */

void initMatrix_DoublePointers(double **MA, double **MB, double **MC, int size)
{
	int i, j; /*Indices*/
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			MA[i][j] = 3.9 * (i - j);
			MB[i][j] = 2.0 * (j + i);
			MC[i][j] = 0.0;
		}
	}
}
/**
 * @brief Function that prints a matrix as a double pointer
 *
 * @param M that is the matrix to print
 * @param size that is the matrix size (N*N)
 */
void printMatrix_DoublePointers(double **M, int size)
{
	if (size < 5)
	{
		int i, j; /*Indices*/
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				printf("%f ", M[i][j]);
			}
			printf("\n");
		}
		printf("-----------------------------\n");
	}
}