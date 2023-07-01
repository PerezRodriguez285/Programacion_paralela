/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Producto Dot de 2 vectores
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <pthread.h>

using namespace std;

void *Producto_DOT(void* parameters){
	vector<int> vectora={9,8,6,10,5};
  	vector<int> vectorb={3,56,1,69,2};
	int resultado = 0;
	for(int i=0 ; i < vectora.size(); i++){ //se recorre el vectora
    		resultado+=vectora[i]*vectorb[i]; //se hace el producto de cada componente y se guarda en res
  }

  cout<<"El producto escalar de 2 vectores es: "<< endl; 
  cout<< resultado << endl;

}//producto
	
int main(int argc, char *argv[]){
	pthread_t hilo1_id;

	pthread_create(&hilo1_id, NULL, Producto_DOT, NULL);
	pthread_join (hilo1_id, NULL);
	pthread_exit(NULL);
	return 0;
}
