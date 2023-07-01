#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

//declaracion de funciones;
float* crea_vect(int);
float* lee_vect(char *, int);
void muestra_vect(float*, int);
//float* producto(char *, int);
static float *W;
static float *V;

int main(int argc, char *argv[]){
	int i, tm;
	tm = atoi(argv[3]);
	cout << tm << endl;
	//creamos el vector V
	V = crea_vect(tm);
	V = lee_vect(argv[1],tm);
	muestra_vect(V,tm);
	
	W = crea_vect(tm);
	W = lee_vect(argv[2],tm);
	muestra_vect(W,tm);
	
	delete(V);
	delete(W);
	//producto(V,W);
	return 0;
}//main

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
		cout << setprecision(5)<< X[i] << " , " << endl;
	}
}





