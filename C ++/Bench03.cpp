#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <cstring>
#include <math.h>
/*Definicion de constantes*/
struct timespec inicio,fin;

/*********************** Funciones *********************/
/*Inicio para medida de tiempo */

void SampleStart(){
    clock_gettime(CLOCK_MONOTONIC,&inicio);
}
/* Fin: medida de tiempo*/

void SampleEnd(){
    clock_gettime(CLOCK_MONOTONIC,&fin);
    /*  Se imprime el tiempo */
    double tiempoTotal;
    tiempoTotal = (fin.tv_sec - inicio.tv_sec)*1e9;
    tiempoTotal = (tiempoTotal + (fin.tv_nsec - inicio.tv_nsec))*1e-9;

    printf(" %f \n",tiempoTotal);

} 
/*  Se crea un doble precision aleatorio */
float randMM(){
    float min = 0.001, max = 9.999;
    static int first = -1;
    if((first = (first<0))){
        srand(time(NULL)+getpid());
    }
    if (min>max)
    {
        return errno=EDOM,NAN;
    }
    return min + (float)rand()/((float)RAND_MAX/(max-min));
    
}

/**********Funcion creacion matriz************/
double** crearMatriz(int tam){
	int i;
	double** matriz = new double* [tam];
	for (i=0;i<tam;i++){
		matriz[i] = new double [tam];
	}
	return matriz;
}

/****************IMprimir*****************/
void printMatrix(double** &matriz, int tam){
	int i,j;
	for (i=0;i<tam;i++){
		for(j=0;j<tam;j++){
			printf(" %f ", matriz[i][j]);
		}
		printf("\n");
		printf("\n");
		
	}
	printf("\n");
	printf("\n");
}

/****************Inicializacion de matrices**************************/

void InializacionMatrices(int tam, double** &matriz1,double** &matriz2, double** &matriz3 ){
	int i,j;
	for (i=0;i<tam;i++){
		for(j=0;j<tam;j++){
			matriz1[i][j] = randMM();
			matriz2[i][j] = randMM();
			matriz3[i][j] = 0;
		}
	}
}

/*************Destruir*****************/

void destruir(int tam, double** &matriz){
	if(matriz){
		int i,j;
		for (i=0;i<tam;i++){
			delete[] matriz[i];
			
		}	
		delete[] matriz;
		matriz = nullptr; 	
	}
}
	
//*******Algoritmo clasico*******************************/

double** Producto(int tam,double** &matriz1,double** &matriz2){
	int i, j, k;
	double** matriz = crearMatriz(tam);
	for (i=0;i<tam;i++){
		for(j=0;j<tam;j++){
			for(k=0;k<tam;k++){

				matriz[i][j]+= matriz1[i][k] * matriz2[k][j];
			}
		}
	}
	return matriz;
}



/****Funcion principal*****/
int main(int argc, char *argv[]){
	int i, j, k;
	int N = atoi(argv[1]);
	
	double** matA = crearMatriz(N);
	double** matB = crearMatriz(N);
	double** matC = crearMatriz(N);

	InializacionMatrices(N,matA,matB,matC);
	//printMatrix(matA, N);
	//printMatrix(matB, N);

	SampleStart();
	matC = Producto(N, matA,matB);
	SampleEnd();
	//printMatrix(matC,N);

	destruir(N,matA);
	destruir(N,matB);
	destruir(N,matC);

}