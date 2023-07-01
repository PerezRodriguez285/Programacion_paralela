/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Leer vectores a traves de archivos
Compilacion: g++ -o misArchivos Archivo.cpp -pthread
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <pthread.h>
#include <string>
#include <sstream>

using namespace std;
//vector global

struct vec{
	string ruta = "clase1.txt";
};
vector<int> vectores;

void *leer_vector(void *arg){

	ifstream archivo("vector.txt");
	//este if permite leer un archivo
	if (archivo.is_open()) {
   		 string numeros;
  		 getline(archivo, numeros); // Leemos la primera línea del archivo
    		 stringstream ss(numeros); 

    	while (getline(ss, numeros, ',')) { 
      		int num = stoi(numeros); // Convertimos la cadena a entero
      		vectores.push_back(num); // Agregamos el número al vector
    	}

    	archivo.close(); // Cerramos el archivo
	}

	//mostramos el vector del archivo
	for (int num : vectores) {
    		cout << num << " " ;
  	}
  	cout << endl;
  	
  	//creamos un nuevo archivo con texto adentro
	ofstream outfile ("Archivo creado.txt");
	outfile << "Texto del archivo"<< endl;
	
	outfile.close();
}//archivo

void* leer_archivos(void* parametros){

	struct vec* p = (struct vec*) parametros;
	string filename=p->ruta;
    	ifstream archivo(filename); 
    	if (!archivo.is_open()) { // Verifica que el archivo se haya abierto 
    		 string numeros;
    		 getline(archivo, numeros); // Leemos la primera línea del archivo
        cout << "No se pudo abrir el archivo" << endl;
        
    	}///if
   	string linea;
    	while (getline(archivo, linea)) { // Lee cada línea del archivo
    		int num = stoi(numeros); // Convertimos la cadena a entero
    		vectores.push_back(num);
        	cout <<"El mensaje es este "<< linea << endl;
   	 }

    	archivo.close(); // Cierra el archivo
  
	return NULL;

}	

int main(int argc, char *argv[]){
	f1.open(argv[1],ios::in);

	pthread_t hilo1_id;
	pthread_t hilo2_id;
	struct vec hilos_arg;
	pthread_create(&hilo1_id, NULL, leer_vector, NULL);
	pthread_create(&hilo2_id, NULL, leer_archivos, &hilos_arg);
	pthread_join (hilo1_id, NULL);
	pthread_join (hilo2_id, NULL);
	pthread_exit(NULL);
	return 0;
}
