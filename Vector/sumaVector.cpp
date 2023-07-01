/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Mostrar 2 vectores a traves de archivos usando la libreria vector
(variacion del programa mostrarVect.cpp)
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>
#include <execution>
#include <thread>
//#include <system.h>
using namespace std;

void lee_th(char * arch, vector<int>, int r){
	ifstream f(arch);
	int i,x;
	for (i = 0; i < r; i++){
		f >> x;
		X.push_back(x);
		//cout<<X[i]<<";"
		f.close();
	}

}//lee_th

void imp_elm(vector<int> X, int r){
	int i;
	cout << X.size() << "Dimension" << endl; //mostramos el tamaño del arreglo
	for(i = 0; i < r; i++){
		cout << X.at(i) << ", " << endl; //.at se ubica en el espaciode i del vector
	}//for
}//imp_elm

void suma_vect(vector<int> X, vector<int> Y){
	int i

}//suma

int main(int argc, char *argv[]){
	int rn,i,x,y,it;
	rn = atoi(argv[3]);
	vector<int> V;
	vector<int> W;
	
	thread t1(&lee_th,argv[1],V,23);
	thread t2(&lee_th,argv[2],W,23);
	
	t1.join();
	t2.join();
	
	thread t3(&suma_vect,V,W);
	t3.join();
	return 0;
}//main
