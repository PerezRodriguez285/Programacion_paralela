/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Realizar la operacion de matriz x vector de manera paralela usando las directivas de omp para su correcta funcion usando OmpTask
Este trabajo se dividio en 3 codigos el principal, las funciones y la libreria creada por el usuario, ambas deben de estar dentro de la misma carpeta para evitar errores de compilacion
La compilacion del programa se realiza de la siguiente manera
Compilacion: g++ -std=c++17 -c -o func_omp.o func_omp.cpp
	     g++ -std=c++17 -o matcmat MatxMatTask.cpp func_omp.o -fopenmp
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
#define NUM 4
using namespace std;
float **M, **N, **O, **T;
int main(int argc, char *argv[]){
	cout<<"=========================================="<<endl;
	cout<<"Multiplicacion de matriz x matrix con task"<<endl;
	cout<<"=========================================="<<endl;
	int i,j,k,m,n,q;
	float t0,tf;
	t0=tf=0;
	m=atoi(argv[3]);
	n=atoi(argv[4]);
	q=atoi(argv[5]);

	omp_set_num_threads(4);
	
	float t1,t2;
	omp_set_num_threads(NUM);
	t1=omp_get_wtime();
	
	#pragma omp parallel
	{
	//cada tarea puede hacerse cuando quiera sin depender de las demas 
		#pragma omp single nowait
		{
			#pragma omp task	
			{
			M=crea_mat(m,n);
			M=lee_mat(argv[1],m,n);
			//muestra_mat(M,m,n);
			}
			#pragma omp task
			{
			N=crea_mat(n,q);
			N=lee_mat(argv[2],n,q);
			//muestra_mat(N,n,q);
			}
			#pragma omp task
			{
			O=crea_mat(m,q);
			}
			#pragma omp taskwait
			{
			T=crea_mat(q,n);
			T=mat_trans(N,n,q);
			}
	
		}
	}
	
	#pragma omp parallel for shared(M,T,O,i,j) collapse(2)
	for(i=0;i<m;i++){
		for(j=0;j<q;j++){			
				O[i][j]+= vecxvec(M[i],T[j],q); 
		}
	}//for
	t2=omp_get_wtime();
	muestra_mat(O,m,q);
	cout<<"Tiempo de computo: " <<t2-t1<<endl;

	return 0;
}
