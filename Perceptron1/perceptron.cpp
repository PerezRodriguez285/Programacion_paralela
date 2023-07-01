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
Proyecto 1: Realizar el metodo del perceptron simple para el ejercicio de las frutas 
La compilacion del programa se realiza de la siguiente manera
Compilacion: g++ -std=c++17 -c -o func_omp.o func_omp.cpp
	     g++ -std=c++17 -o perce perceptron.cpp func_omp.o -fopenmp
Ejecuacion: ./ejecutable archivo1 archivo2 tamaño de M tamaño N 
Ejemplo: (./percep Frutas2.txt Pesos2.txt 10 6)
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <omp.h>
#include "func_omp.h"

using namespace std;
float **A, *Y, **W;
int *O;

int main(int argc, char * argv[]){
	cout << "=========Perceptron==========" << endl;
	cout << "========Salida -1, +1======= " << endl;
	int ren=atoi(argv[3]);
	int col=atoi(argv[4]);
	float wx,wy,T,I,tf,t0;
	int numth=4, i;
	omp_set_num_threads(numth);
	t0=omp_get_wtime();
	
	#pragma omp single nowait
	{
		#pragma omp task
		{
		A=crea_mat(ren,col);
		A=lee_mat(argv[1],ren,col);
		}
		#pragma omp task
		{
		W=crea_mat(ren,col);
		W=lee_mat(argv[2],ren,col);
		//muestra_vect(W,ren);
		}
		#pragma omp task
		{
			Y=crea_vect(ren);
		}
	}
	
	#pragma omp parallel for shared(A,W)
	for(i = 0; i <ren-1; i++){
		I = 0;
		int b;
	
		I = vecxvec(A[i],W[i],col);
		T = 0;
		if(I > T){
			Y[i]=1; b=1;
			wx=W[i][0]+ Y[i]*b*A[i][0];
			W[i+1][0]=wx;
			wy=W[i][1]+ Y[i]*b*A[i][1];
			W[i+1][1]=wy;
			wx=0; wy=0;}
		else{
			Y[i]=-1; b=-1;
			wx=W[i][0]-b*Y[i]* A[i][0];
			W[i+1][0]=wx;
			wy=W[i][1]-b*Y[i]* A[i][1];
			W[i+1][1]=wy;
			wx=0; wy=0;}
	}
	
	tf=omp_get_wtime();
	cout << "Tiempo de ejecucion: "<<tf-t0<<endl;
	muestra_vect(Y,ren);
	//muestra_mat(W,ren,col);
	return 0;
}
