#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include "func_omp.h"

using namespace std;
//float **M, *V, *W, Prod=0;

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

int muestra_vect(float *M, int sz){
	int i;
	for(i = 0; i < sz; i++){
		cout << setprecision(50)<< M[i] << ", " << endl;
	}
	return 0;
}

void productoVector(char *n_arch1, char *n_arch2, int n, int num_procs){
	int i=0;
	float *V, *W, Prod=0;
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

float** crea_mat(int m, int n){
	int j;
	float **M;
	M = new float*[m];
	for(j = 0; j < m; j++){
		M[j] = new float[n];
	}
	return M;
}

float** lee_mat(char *nom_arch, int m, int n){
	int i,j;
	float **MM, num;
	MM = crea_mat(m,n);
	fstream fd1;
	cout.precision(15);
	fd1.open(nom_arch,ios::in);
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			fd1>>num;
			MM[i][j] = num;
		}
	}
	fd1.close();
	cout <<"Matriz leida " << endl;
	return MM;
}

void muestra_mat(float **M, int m, int n){
	int i,j;
	for(i=0; i < m; i++){
		for(j = 0; j < m; j++){
			cout << M[i][j] << ",";
			//cout << fixed << setprecision(1) << *((*M + i) + j) << ", ";
		}
		cout << endl;
	}
}

float vecxvec(float* X,float* Y,int re){
	int i; 
	float prod=0;
	for(i=0; i <re; i++){
	#pragma omp critical
		prod +=X[i]*Y[i];
	}
	//cout << "El producto de los vectores es: ";
	//cout<<endl<<prod<<endl;
	return prod;
}

void matxVec(const float* A,const float* x, float* y, int re, int co) {
    #pragma omp parallel for
    for (int i = 0; i < re; ++i) {
        double sum = 0;
        for (int j = 0; j < co; ++j) {
            sum += A[i * co + j] * x[j];
        }
        y[i] = sum;
    }
}

void productoMatxVec(char *n_arch1, char *n_arch2, int re, int co, int num_procs){
	int i=0;
	float **M, *V, *W, Prod=0;
	omp_set_num_threads(num_procs);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
		M=crea_mat(re,co);
		M=lee_mat(n_arch1,re,co);
		muestra_mat(M,re,co);
		}

		#pragma omp section
		{
		V=crea_vect(co);
		V=lee_vect(n_arch2,co);
		//muestra_vect(V,co);
		}

		#pragma omp section
		{
		W=crea_vect(re);

		}

	}
	#pragma omp for private(i)
	for(i = 0; i<re;i++){
		#pragma omp critical
		W[i]=vecxvec(M[i],V,co);
	}	
	cout << "El producto de la matriz x vector es:" << endl;
	muestra_vect(W,co);

}

float ** mat_trans(float ** X,int r, int c){
	int i,j;
	float **Y;
	Y=crea_mat(c,r);
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			Y[j][i]= X[i][j];
		}
	}
	return Y;
}

float** MatrizxMatriz(char *n_arch1, char *n_arch2,int m, int n, int q,int numHilos){
	int i,j,k;
	float **M,**N,**O,**T;
	float t0,tf;
	t0=tf=0;

	omp_set_num_threads(numHilos);
	omp_set_nested(true);
	t0=omp_get_wtime();
	#pragma omp sections
	{
		#pragma omp section
		{
			M=crea_mat(m,n);
			M=lee_mat(n_arch1,m,n);
			muestra_mat(M,m,n);
		}
		#pragma omp section
		{
			N=crea_mat(n,q);
			N=lee_mat(n_arch2,n,q);
			muestra_mat(N,n,q);
		}
		#pragma omp section
		{
			O=crea_mat(m,q);
		}
	}
	#pragma omp sections
	{
		#pragma omp section
		{
			T=crea_mat(q,n);
			T=mat_trans(N,n,q);
		}
	}
	#pragma omp parallel for collapse(2)
	for (i=0;i<m;i++){
		for (j=0;j<q;j++){
			O[i][j]+=vecxvec(M[i],T[j],q);
		}
	}
	tf=omp_get_wtime();
	cout << endl;
	cout << "El resultado de matriz x matriz es: " << endl;
	muestra_mat(O,m,q);
	cout<<"Tiempo ejecucion: "<<tf-t0<<endl;

	return O;
}

float** MatrizxMatrizAnidado(char *n_arch1, char *n_arch2,int m, int n, int q,int numHilos){
	int i,j,k;
	float **M,**N,**O,**T;
	float t0,tf;
	t0=tf=0;

	omp_set_num_threads(numHilos);
	omp_set_nested(true);
	t0=omp_get_wtime();
	
	#pragma omp sections
	{
		#pragma omp section
		{
		M=crea_mat(m,n);
		M=lee_mat(n_arch1,m,n);
		muestra_mat(M,m,n);
		}
		#pragma omp section
		{
		N=crea_mat(n,q);
		N=lee_mat(n_arch2,n,q);
		muestra_mat(N,n,q);
		}
		#pragma omp section
		{
		O=crea_mat(m,q);
		}
	}

	#pragma omp parallel for
	for(i=0;i<m;i++){
	#pragma omp parallel for collapse(2)
		for(j=0;j<q;j++){
			for(k=0;k<n;k++){
				O[i][j]+= M[i][k]*N[k][j]; 
			}
		}
	}//for
	
	cout << endl;
	cout << "El resultado de matriz x matriz es: " << endl;
	tf=omp_get_wtime();
	muestra_mat(O,m,q);
	cout<<"Tiempo de computo: " <<tf-t0<<endl;
	return 0;
}

