/*************************************
*Fecha: 10 agosto 2022
*Autor: Brayan Bernal
*Materia: Parallel and Dsitributed computing
*Tema: Introduccion a la programacion en C
*Organizacion por funciones de la APP
*Topico: Diseño de Benchmark
*Fase01: Multiplicacion de Matrices Clasico
**************************************/
#ifndef MM_LIB_H_INCLUDED
#define MM_LIB_H_INCLUDED

#include "mm_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <omp.h>


/* se trabaja con matrices cuadradas*/
//funciones

void tiempo_inicial();
void tiempo_final();

/*Benchmark02: MM clásico con doubles y aleatorios*/
void inicializar_matrices_rmd(int N, double *matrizA, double *matrizB, double *matrizC);
void inicializar_matrices(int N, double *matrizA, double *matrizB, double *matrizC);
void imprimir_matriz(int N, double *matrizA);

/*Benchmark05: filas x columnas pthreads*/
void *mm_clasica_pthreads(void *argTH);

/*Benchmark06: OpenMP Columnas x filas */
void mm_c_omp(int N, int Num_hilos, double *matrizA, double *matrizB, double *matrizC);

/*Benchmark07: OpenMP filas x filas */
void mm_f_omp(int N, int Num_hilos, double *matrizA, double *matrizB, double *matrizC);

#endif
