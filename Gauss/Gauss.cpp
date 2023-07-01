/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Autores: Antonio Alberto de la Luz Pérez Rodriguez
	 Joel Ramirez Martinez
	 Jair Palos Hernandez
	 Brandon Donnet Godinez Luna
	 Jorge Alfredo
Proyecto 3: Realizar el método de Gauss para resolver matrices de hasta 50 x 50 numeros.
La compilacion del programa se realiza de la siguiente manera
Compilacion: g++ -std=c++17 -c -o func_omp.o func_omp.cpp
	     g++ -std=c++17 -o gauss1 Gauss.cpp func_omp.o -fopenmp
Ejecuacion: ./ejecutable archivo1 archivo2 tamaño de M tamaño N tamaño de las matrices
Ejemplo: (time ./gauss1 matriz20.txt vector20.txt 20 20 20)
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include "func_omp.h"

using namespace std;

void MetodoGauss(char *archivo1, char *archivo2, int n,int p, int c, int numHilos) {
    float** A;
    float* B;
    float* X;
    int i, j, k;

    omp_set_num_threads(numHilos);

    // Lectura de la matriz A y el vector B desde archivos
    A = lee_mat(archivo1, n, p);
    B = lee_vect(archivo2, c);

    // Eliminación gaussiana
    for (k = 0; k < n - 1; k++) {
        #pragma omp parallel for private(j) shared(A, B, k) schedule(static)
        for (i = k + 1; i < p; i++) {
            float factor = A[i][k] / A[k][k];

            #pragma omp critical
            {
                for (j = k; j < p; j++) {
                    A[i][j] -= factor * A[k][j];
                }
                B[i] -= factor * B[k];
            }
        }
    }

    //cout<<"Vector de resultados"<<endl;
    //muestra_vect(B,c);
    //cout<<"Matris de ecuaciones"<<endl;
    //muestra_mat(A,n,p);

    // Resolución del sistema triangular superior
    X = crea_vect(n);

    for (i = c - 1; i >= 0; i--) {
        float sum = 0.0;
        #pragma omp simd reduction(+:sum)
        for (j = i + 1; j < c; j++) {
            sum += A[i][j] * X[j];
        }

        X[i] = (B[i] - sum) / A[i][i];
    }

    // Mostrar solución
    cout << endl;
    cout << "Las soluciones que posee la matriz son:" << endl;
    muestra_vect(X, c);
}

int main(int argc, char *argv[]) {
    
    int numEcua = atoi(argv[3]);
    int numVari = atoi(argv[4]);
    int NumRes = atoi(argv[5]);

    int numHilos = 100;//omp_get_max_threads(); // Obtener el número máximo de hilos

    MetodoGauss(argv[1],argv[2],numEcua,numVari,NumRes,numHilos);

    return 0;
}
