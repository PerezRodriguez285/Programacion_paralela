/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Realizar la operacion de matriz x vector de manera paralela usando las directivas de omp para su correcta funcion
Este trabajo se dividio en 3 codigos el principal, las funciones y la libreria creada por el usuario, ambas deben de estar dentro de la misma carpeta para evitar errores de compilacion
La compilacion del programa se realiza de la siguiente manera
Compilacion: g++ -std=c++17 -c -o func_omp.o func_omp.cpp
	     g++ -std=c++17 -o vecxvec vecxvec.cpp func_omp.o -fopenmp
Ejecuacion: ./ejecutable archivo1 archivo2 tamaño de M tamaño N tamaño de las matrices
Ejemplo: (./vecxvec matriz1.txt matriz2.txt 100 100 100)
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include "func_omp.h"

using namespace std;
float **M, **N, **O, **T;
int main(int argc, char *argv[]){
	int m,n,q;
	float** R;
	int numHilos=4;

	m=atoi(argv[3]);
	n=atoi(argv[4]);
	q=atoi(argv[5]);

	R=MatrizxMatriz(argv[1],argv[2],m,n,q,numHilos);
	R=MatrizxMatrizAnidado(argv[1],argv[2],m,n,q,numHilos);
	return 0;
}

