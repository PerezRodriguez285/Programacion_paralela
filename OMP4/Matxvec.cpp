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
Ejecuacion: ./ejecutable archivo1 archivo2 tamaño del vector tamaño de la matriz
Ejemplo: (./vecxvec matriz1.txt vector2.txt 5 5)
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include "func_omp.h"

using namespace std;
//float **M, *V, *W, Prod=0;

int main(int argc, char *argv[]) {
  int re,co,i,num_procs;
	re=atoi(argv[3]);
	co=atoi(argv[4]);
	num_procs=4;

	productoMatxVec(argv[1], argv[2],co,re,num_procs);

	return 0;
}


