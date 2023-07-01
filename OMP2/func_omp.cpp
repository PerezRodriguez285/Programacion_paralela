#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include "func_omp.h"

using namespace std;
float *V, *W, Prod=0;

float * crea_vect(int sz){
	float *X;
	X = new float[sz];
	cout << "Vector creado" << endl;
	return X;
}

float * lee_vect(char *n_arch, int sz){
	float *X,y;
	X = crea_vect(sz);
	ifstream f(n_arch);
	int i=0;
	y = 0;
	cout << "Leyendo vector en el archivo: " << n_arch << endl;
	
	while(f >> y){
		X[i] = y;
		i++;
		y = 0;
	}
	cout << "Vector leido" << endl;
	f.close();
	
	return X;
}

void muestra_vect(float *X, int sz){
	int i;
	for(i = 0; i < sz; i++){
		cout << setprecision(50)<< X[i] << " , " << endl;
	}
}

void vectorxvector(float* X, float* Y, float* Z, int r, int n){
	float s = 0;
  
	for(int i=0 ; i<n ; i++){
		s += X[i]*Y[i];
	}
	Z[r] = s;
}

void productoVector(char *n_arch1, char *n_arch2, int n, int num_procs){
	int i=0;
	omp_set_num_threads(num_procs);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
		V=crea_vect(n);
		V=lee_vect(n_arch1,n);
		muestra_vect(V,n);
		}
		
		#pragma omp section
		{
		W=crea_vect(n);
		W=lee_vect(n_arch2,n);
		muestra_vect(W,n);
		}
	
	}
	#pragma omp for private(i) reduction(+:Prod)
	for(i=0; i <n; i++){
	
	#pragma omp critical
		Prod +=V[i]*W[i];
	}
	cout << "El producto de los 2 vectores es: ";
	cout<<endl<<Prod<<endl;

}
