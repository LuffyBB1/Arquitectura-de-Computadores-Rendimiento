#ifndef MODULE_C_H_INCLUDE
#define MODULE_C_H_INCLUDE
typedef struct argsThreads{
    int numThreads;
    int matrixSize;
    double **matrixA;
    double **matrixB;
    double **matrixR;
    int idThread;
} threadsArguments;


void sampleStart();
void sampleEnd();
double randNumber();
void MM1c(int size, double *Ma, double *Mb, double *Mr);
void MM1f(int size, double *Ma, double *Mb, double *Mr);
void *multMM(void *arg);
void MM1cOMP(int threads, int size, double *a, double *b, double *c);
void MM1fOMP(int threads, int size, double *a, double *b, double *c);
double ** memReserve (int size);
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr);
void printMatrix(int SZ, double *M);
void initMatrix_DoublePointers (double **MA, double **MB, double **MC, int size);
void printMatrix_DoublePointers (double **M, int size);
void printTransposed(int size, double *M);

#endif