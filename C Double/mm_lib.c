/*************************************
*Fecha: 24 agosto 2022
*Autor: Brayan Bernal
*Materia: Parallel and Dsitributed computing
*Tema: Introduccion a la programacion en C
*Organizacion por funciones de la APP
*Topico: Diseño de Benchmark02
*Fase01: Multiplicacion de Matrices Clasico
**************************************/

#include "mm_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

struct timespec punto_inicio, punto_final;

/* se trabaja con matrices cuadradas*/
//funciones
void tiempo_inicial(){

    clock_gettime(CLOCK_MONOTONIC, &punto_inicio);

}

void tiempo_final(){
    
    double suma_tiempo;
    clock_gettime(CLOCK_MONOTONIC, &punto_final);
    suma_tiempo = (punto_final.tv_sec - punto_inicio.tv_sec)*1e9;
    suma_tiempo = (suma_tiempo + punto_final.tv_nsec - punto_inicio.tv_nsec)*1e-9;
    printf("%f \n", suma_tiempo);

}
/************* BENCHMARK 02 INT y aleatorios *******************/
//funcion generadora de numeros aleatorios 
//numeros entre 0 y 9 

double funcionRandom(){
         double min = 0.001, max = 9.999;
         static int flag = -1;
         if ((flag = (flag<0))){
                 //Se genera la semilla <al usar la función
                 srand(time(NULL) + getpid());
         }
         
         if (min > max)
                 return errno = EDOM, NAN;
         return min + (double)rand()/((double)RAND_MAX/(max-min));
}


/**********   Bench01 *******/
void inicializar_matrices(int N, double *matrizA, double *matrizB, double *matrizC){

    int i, j;

    for (i=0; i<N; i++){
	
		for (j=0; j<N;j++){
			matrizA[i+j*N]=3*(i+j);
			matrizB[i+j*N]=2*j+3*i;
			matrizC[i+j*N]=0;
		}
		
	
	}

}

void inicializar_matrices_rmd(int N, double *matrizA, double *matrizB, double *matrizC){

    int i, j;

    for (i=0; i<N; i++){
	
		for (j=0; j<N;j++){
			matrizA[i+j*N]=funcionRandom();
			matrizB[i+j*N]=funcionRandom();
			matrizC[i+j*N]=0;
		}
		
	
	}

}

void imprimir_matriz(int N, double *matrizA){

    int i, j;
    if(N<5){

    for (i=0; i<N; i++){
		
	
		for (j=0; j<N;j++){
			printf(" %f ",matrizA[j+i*N]);
			
			}
		printf("\n");
		}
		printf("\n");
	}
}

void multiplicacion_matrices(int N, double *matrizA, double *matrizB, double *matrizC){

    int i, j, k;
    double suma_parcial;

    for (i=0; i<N; i++){
		for (j=0; j<N;j++){
		
			suma_parcial =0;
			double *pA, *pB;
			pA = (matrizA + i*N);
			pB = (matrizB + j);
			for (k=0; k<N; k++, pA++, pB+=N){
			
				suma_parcial += (*pA * *pB);
			}	
	 		matrizC[j+i*N] = suma_parcial;
	 	}
	}
    
}


