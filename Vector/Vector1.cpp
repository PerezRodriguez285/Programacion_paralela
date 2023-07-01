/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Mostrar 2 vectores a traves de archivos usando la libreria vector
Compilacion: g++ -std=c++ 17 -o vector1 Vector1.cpp -pthread
Ejecución: ./ejecutable archivo1 archivo2 tamaño del vector 
Ejemplo: ./mostrarvect1 clase1.txt clase2.txt 23 (ambos vectores deben tener el mismo tamaño)
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <thread>
using namespace std;

void imp_elm(vector<int> X, int r){
	int i;
	cout << X.size() << "Dimension" << endl; //mostramos el tamaño del arreglo
	for(i = 0; i < r; i++){
		cout << X.at(i) << ", " << endl; //.at se ubica en el espaciode i del vector
	}//for
}//imp_elm


int main(int argc, char *argv[]){
	int rn,i,x,y,it;
	rn = atoi(argv[3]);
	vector<int> V;
	vector<int> W;
	fstream f1,f2;
	
	f1.open(argv[1],ios::in);
	f2.open(argv[2],ios::in);
	
	for(i = 0; i < rn; i++){
		f1 >> x; //lee la x y la agrega a la ultima posicion del arreglo
		V.push_back(x);
	}
	
	for(i = 0; i < rn; i++){
		f2 >> y;	
		W.push_back(y);	
	}
	
	thread t1(&imp_elm, V,23); // eltamaño del archivo
	thread t2(&imp_elm, W,23);
	
	t1.join();
	t2.join();
	
	return 0;
}// main

