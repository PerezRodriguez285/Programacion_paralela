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
Proyecto 2: Realizar la operacion de Kmeans para identificar los centroides y sus distancias
La compilacion del programa se realiza de la siguiente manera
Compilacion: g++ -std=c++17 -c -o func_omp.o func_omp.cpp
	     g++ -std=c++17 -o kmeans Kmeans.cpp func_omp.o -fopenmp
Una vez compilado el codigo c++ se generaran las coordenadas de los centroides y los puntos por lo que procederemos a ejecutar el codigo python para visualisarlo graficamente.
	     python grafica3.py
Ejecuacion: ./ejecutable archivo1 archivo2 vector N vector M Total de datos total de puntos centroides
Ejemplo: (./kmeans centroides.txt datos.txt 100 100 100 5)
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include "func_omp.h"
//suma de vectores
using namespace std;
float **X, **Y;
int i;
int main(int argc, char *argv[]){
	int i,fila,columna,numeCentriodes;
	float t0,tf;
	columna=atoi(argv[3]);
	fila=atoi(argv[4]);
	numeCentriodes=atoi(argv[6]);
	t0=omp_get_wtime(); 
	#pragma omp single nowait
	{
		#pragma omp task	
		{
		X=crea_mat(numeCentriodes,2);
		X=lee_mat(argv[1],numeCentriodes,2);
		//muestra_mat(X, numeCentriodes,fila);
		}
		#pragma omp task
		{
		Y=crea_mat(columna,fila);
		Y=lee_mat(argv[2],columna,fila);
		//muestra_mat(Y, columna, fila);
		}
	}
	
	distancia(X,Y,columna,numeCentriodes,fila, columna);
	
	tf=omp_get_wtime();
	cout << endl;
	cout<<"Tiempo de computo: " <<tf-t0<<endl;
	
	cout<<endl;
	cout<<endl;
		
	return 0;
}

