/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Mostrar 2 vectores a traves de archivos usando la libreria vector
(variacion del programa Vector1.cpp)
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <pthread.h>

using namespace std;
//mandamos una funcion que lea un vector desde el principio
vector<int> ifstream_lines(ifstream& fs){
	vector<int> out;
	int temp, i;
	
	while(fs >> temp){ //
		out.push_back(temp); //imprime los valores de forma aleatoria del archivo que tiene el vector
	}
	return out;
}


int main(int argc, char *argv[]){
	pthread_t hilo1_id;
	
	vector<int> V;
	ifstream fs(argv[1]);
	V=ifstream_lines(fs);
	int i;
	
	for(i = 0; i<V.size();++i){
		cout<<V[i]<<","<<endl; //se muestran los datos del vector
	}
	
	//pthread_create(&hilo1_id, NULL, , NULL);
	
	//pthread_join (hilo1_id, NULL);
	//pthread_exit(NULL);
	
	return 0;
}
