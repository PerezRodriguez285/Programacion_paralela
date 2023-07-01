/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Autores: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Directiva Simd
La compilacion del programa se realiza de la siguiente manera
Compilacion: g++ -std=c++17 -c -o func_omp.o func_omp.cpp
	      g++ -std=c++17 -o Dsimd DirectivaSimd.cpp func_omp.o -fopenmp
Ejecuacion: ./ejecutable archivo1 archivo2 tamaño de M tamaño N 
Ejemplo: (./Dsimd vector1.txt vector2.txt 4 2)
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
float *X, *Y, *Z;
int i;

#pragma omp declare simd
float saxpy(float *X, float*Y,int i, float SA){
	float tm;
	//Z=crea_vect(i);
	tm=SA*(X[i]+Y[i]);
	//cout << X[i] << endl;
	//Z[i]=tm;
	return tm;
}

int main(int argc, char *argv[]){
	int i,ren;
	float mt,t0,tf;
	ren=atoi(argv[3]);
	mt=atof(argv[4]);
	Z=crea_vect(ren);
	t0=omp_get_wtime(); 
	#pragma omp single nowait
	{
		#pragma omp task	
		{
		X=crea_vect(ren);
		X=lee_vect(argv[1],ren);
		//muestra_vect(ren);
		}
		#pragma omp task
		{
		Y=crea_vect(ren);
		Y=lee_vect(argv[2],ren);
		//muestra_vect(ren);
		}
	}
	
	/*int ren;
	int i, size=10000;
	ren=atoi(argv[3]);
	
	X=crea_vect(ren);
	Y=crea_vect(ren);
	
	X=lee_vect(argv[1],ren);
	Y=lee_vect(argv[2],ren);*/
	
	#pragma omp simd
	for(i=0; i<ren;i++){
		Z[i]=saxpy(X,Y,i,mt);
	}
	
	tf=omp_get_wtime();
	cout<<"Tiempo de computo: " <<tf-t0<<endl;
	muestra_vect(Z,ren);
	
	return 0;
}


